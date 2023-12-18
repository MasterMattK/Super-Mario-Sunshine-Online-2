from PySide6.QtCore import *
from time import sleep
from threading import Thread, Lock
import json
import enet

from Server.ServerData import FlagSync, Player
from Misc.Network import NetworkServer
from Misc.DataTypes import ClientRcvDataTypes, ServerRcvDataTypes, DisconnectSource, ConsoleTypes, GamemodeTypes, TagStatus, ManhuntStatus
from Misc.LevelData import LevelData

class Server(QObject):
    console_msg = Signal(str, ConsoleTypes)
    server_started = Signal()
    server_stopped = Signal()
    usernames_updated = Signal(list)
    username_changed = Signal(tuple)
    gamemode_change = Signal(GamemodeTypes)
    tag_started = Signal()
    tag_stopped = Signal()
    set_hider = Signal(str)
    set_tagger = Signal(str)
    manhunt_started = Signal()
    manhunt_stopped = Signal()
    set_runner = Signal(str)
    set_hunter = Signal(str)

    def __init__(self, ip: str, port: int, player_num: int, sync_flags: bool, disable_refills: bool, version: str) -> None:
        super().__init__()

        self.version = version

        self.running = True
        self.ip = ip
        self.port = port
        self.player_num = player_num
        self.network = NetworkServer(ip, port, max_conns=player_num)
        self.flag_data = FlagSync()
        self.flag_lock = Lock()
        self.sync_flags = sync_flags
        self.disable_refills = disable_refills
        self.receive_threads = [Thread(target=self.server_receive) for i in range(player_num)]    # moving to another thread allows for signals to be processed
        self.level_data = LevelData()
        self.gamemode = GamemodeTypes.DEFAULT.value
        self.tag_running = False
        self.allow_tps = False
        self.allow_level_changes = False
        self.manhunt_running = False

        # this is essentially used like a switch statement
        self.receive_opts = {
            ServerRcvDataTypes.CONNECT.value: self.on_connect,
            ServerRcvDataTypes.CLI_DATA.value: self.on_cli_data,
            ServerRcvDataTypes.FLG_DATA.value: self.on_flg_data,
            ServerRcvDataTypes.USERNAME.value: self.on_username,
            ServerRcvDataTypes.CHAT_MSG.value: self.on_chat_msg,
            ServerRcvDataTypes.MODEL.value: self.on_model,
            ServerRcvDataTypes.TP_INFO.value: self.on_tp_info,
            ServerRcvDataTypes.TP_REQUEST.value: self.on_tp_request,
            ServerRcvDataTypes.CHANGE_LEVEL.value: self.on_change_level,
            ServerRcvDataTypes.TAG_STATUS.value: self.on_tag_status,
            ServerRcvDataTypes.FLAGS_PAUSED.value: self.on_flags_paused,
            ServerRcvDataTypes.MANHUNT_STATUS.value: self.on_manhunt_status,
            ServerRcvDataTypes.MANHUNT_DMG.value: self.on_manhunt_damage
        }

        # each object represents a player.
        self.player_data = [Player(i) for i in range(player_num)]

    # due to the mix of c++ bindings with PySide6 and PyEnet, python's native garbage collector 
    # doesn't seem to do the complete job for us, so we have to manually delete everything.
    # I'm not 100% sure that all deletions are necessary, but better safe than sorry
    def cleanup(self) -> None:
        # looping through every attribute (a copy is necessary because vars(self) changes as we delete attributes)
        for attr in vars(self).copy():
            # We don't want to include attributes from the class we've derived from (QObject), and we don't want to delete our Signals
            if not hasattr(QObject, attr) and not attr.startswith('__') and not isinstance(getattr(self, attr), Signal):
                delattr(self, attr)

    def start_server(self) -> None:
        self.server_started.emit()
        for thread in self.receive_threads:
            thread.start()

    def stop_server(self) -> None:
        self.running = False

        for thread in self.receive_threads:
            thread.join()

        self.usernames_updated.emit([])
        self.network.cleanup()
        self.cleanup()

        self.server_stopped.emit()
        self.deleteLater()

    def chat_message(self, message: str) -> None:
        self.console_msg.emit(f"<b>[<i>YOU</i>]</b> {message}", ConsoleTypes.DEFAULT)
        data = {'dataType': ClientRcvDataTypes.CHAT_MSG.value, 'username': "SERVER", 'msg': message}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(data), peer)

    def start_tag(self) -> None:
        connected_players = [player for player in self.player_data if player.connected]

        if not connected_players:
            self.tag_stopped.emit()
            self.console_msg.emit("You can't start tag without any players connected!", ConsoleTypes.ERROR)
            return

        if not TagStatus.HIDER in [player.tag_status for player in connected_players]:
            self.tag_stopped.emit()
            self.console_msg.emit("You can't start tag without any hiders!", ConsoleTypes.ERROR)
            return

        if not TagStatus.TAGGER in [player.tag_status for player in connected_players]:
            self.tag_stopped.emit()
            self.console_msg.emit("You can't start tag without any taggers!", ConsoleTypes.ERROR)
            return
        
        data = {'dataType': ClientRcvDataTypes.START_TAG.value, 'start': True}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(data), peer)

        self.tag_running = True
        self.console_msg.emit("Tag started!", ConsoleTypes.INFO)
        self.tag_started.emit()

    def stop_tag(self) -> None:
        data = {'dataType': ClientRcvDataTypes.START_TAG.value, 'start': False}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(data), peer)

        self.tag_running = False
        self.console_msg.emit("Tag stopped!", ConsoleTypes.INFO)
        self.tag_stopped.emit()

    def start_manhunt(self) -> None:
        connected_players = [player for player in self.player_data if player.connected]

        if not connected_players:
            self.manhunt_stopped.emit()
            self.console_msg.emit("You can't start manhunt without any players connected!", ConsoleTypes.ERROR)
            return

        if not ManhuntStatus.RUNNER in [player.manhunt_status for player in connected_players]:
            self.manhunt_stopped.emit()
            self.console_msg.emit("You can't start manhunt without a runner!", ConsoleTypes.ERROR)
            return

        if not ManhuntStatus.HUNTER in [player.manhunt_status for player in connected_players]:
            self.manhunt_stopped.emit()
            self.console_msg.emit("You can't start manhunt without any hunters!", ConsoleTypes.ERROR)
            return
        
        data = {'dataType': ClientRcvDataTypes.START_MANHUNT.value, 'start': True}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(data), peer)

        self.manhunt_running = True
        self.console_msg.emit("Manhunt started!", ConsoleTypes.INFO)
        self.manhunt_started.emit()

    def stop_manhunt(self) -> None:
        data = {'dataType': ClientRcvDataTypes.START_MANHUNT.value, 'start': False}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(data), peer)

        self.manhunt_running = False
        self.console_msg.emit("Manhunt stopped!", ConsoleTypes.INFO)
        self.manhunt_stopped.emit()

    def server_receive(self) -> None:
        while self.running:
            sleep(1/1920)
            event = self.network.receive()

            if event.type == enet.EVENT_TYPE_NONE:
                continue

            # connection is handled below in EVENT_TYPE_RECEIVE so that data can be sent with it
            elif event.type == enet.EVENT_TYPE_CONNECT:
                continue

            elif event.type == enet.EVENT_TYPE_DISCONNECT:
                if event.data == DisconnectSource.DEFAULT.value:
                    self.console_msg.emit(f"{self.player_data[event.peer.incomingPeerID].username} has disconnected from the server!", ConsoleTypes.DISCONNECT)
                elif event.data == DisconnectSource.VERSION.value:
                    self.console_msg.emit("The client's SMSO version is not compatible with yours!", ConsoleTypes.DISCONNECT)
                else:
                    self.console_msg.emit(f"{self.player_data[event.peer.incomingPeerID].username} has disconnected from the server!", ConsoleTypes.DISCONNECT)

                self.player_data[event.peer.incomingPeerID] = Player(event.peer.incomingPeerID)

                disconnect_data = {'dataType': ClientRcvDataTypes.DISCONNECT.value, 'incoming_peer_id': event.peer.incomingPeerID}
                other_peers = self.network.get_other_peers(event.peer.incomingPeerID)
                for peer in other_peers:
                    self.network.send(json.dumps(disconnect_data), peer)

                self.usernames_updated.emit([player.username for player in self.player_data if player.connected])

                # these two rely on all connected players meeting a condition, so when someone disconnects we need to check this
                if self.gamemode == GamemodeTypes.DEFAULT.value:
                    self.check_flag_reset_status()
                elif self.gamemode == GamemodeTypes.TAG.value:
                    self.check_tag_end()

                continue

            elif event.type == enet.EVENT_TYPE_RECEIVE:
                data = self.network.decode_data(event.packet.data)
                # this line accesses the function specified by the dataType within self.receive_opts, which is created in __init__(). if the
                # data type isn't found, it calls self.on_unknown() instead
                self.receive_opts.get(data.dataType, self.on_unknown)(data, event)
        
    # Connection information received from client
    def on_connect(self, data: dict, event: enet.Event) -> None:

        # 2.0 doesn't check for version, so a chat message is the only way to inform the client easily
        if 'version' not in data:
            chat_data = {'dataType': ClientRcvDataTypes.CHAT_MSG.value, 'username': 'SERVER', 'msg': f"Your version of SMSO is not compatible with the server! ({self.version})"}
            self.network.send(json.dumps(chat_data), event.peer, reliable=True)
            event.peer.disconnect_later(data=DisconnectSource.VERSION.value)
            self.console_msg.emit(f"A user tried to connect, but their version is not compatible with yours!", ConsoleTypes.ERROR)
            return
        elif data.version != self.version:
            event.peer.disconnect_now(data=DisconnectSource.VERSION.value)
            self.console_msg.emit(f"A user tried to connect, but their version is not compatible with yours!", ConsoleTypes.ERROR)
            return

        # send data about all of the other clients to the currently connecting client
        connect_data = {'dataType': ClientRcvDataTypes.SELF_CONNECT.value, 'self_peer_id': event.peer.incomingPeerID, 'player_num': self.player_num, 
                        'disable_refills': self.disable_refills, 'gamemode': self.gamemode, 'allow_tps': self.allow_tps, 'allow_level_changes': self.allow_level_changes,
                        'version': self.version}
        for player in self.player_data:
            if player.connected == True:
                connect_data[player.username] = {'incoming_peer_id': player.peer_id, 'model': player.model}
        self.network.send(json.dumps(connect_data), event.peer, reliable=True)

        p = event.peer.incomingPeerID
        self.player_data[p].peer_id = event.peer.incomingPeerID
        self.player_data[p].connected = True
        self.player_data[p].address = event.peer.address
        self.player_data[p].username = self.check_username(data.username)
        self.player_data[p].model = data.model
        self.console_msg.emit(f"{self.player_data[p].username} has connected!", ConsoleTypes.CONNECT)

        self.usernames_updated.emit([player.username for player in self.player_data if player.connected])

        # if the user's username has been changed due to duplicates, it sends an update to the client
        if data.username != self.player_data[p].username:
            username_data = {'dataType': ClientRcvDataTypes.USERNAME.value, 'new_username': self.player_data[p].username, 'old_username': data.username}
            self.network.send(json.dumps(username_data), event.peer)

        # send connection to all other connected clients
        other_peers = self.network.get_other_peers(p)
        connect_data = {'dataType': ClientRcvDataTypes.CONNECT.value, 'incoming_peer_id': event.peer.incomingPeerID, 'username': self.player_data[p].username, 'model': data.model}
        for peer in other_peers:
            self.network.send(json.dumps(connect_data), peer)

    # Client data received from client
    def on_cli_data(self, data: dict, event: enet.Event) -> None:
        other_peers = self.network.get_other_peers(event.peer.incomingPeerID)
        data.incoming_peer_id = event.peer.incomingPeerID
        data.dataType = ClientRcvDataTypes.CLI_DATA.value
        for peer in other_peers:
            self.network.send(self.network.encode_data(data), peer)

    # Flag information received from client
    def on_flg_data(self, data: dict, event: enet.Event) -> None:
        if self.sync_flags == False or self.gamemode != GamemodeTypes.DEFAULT.value:
            return
        self.flag_lock.acquire()
        try:
            send_destination, send_data = self.flag_data.sync(data)
            if send_destination == "sync_current_peer":
                self.network.send(send_data, event.peer)
            elif send_destination == "sync_other_peers":
                other_peers = self.network.get_other_peers(event.peer.incomingPeerID)
                for peer in other_peers:
                    self.network.send(send_data, peer)
        finally:
            self.flag_lock.release()

    # Username information received from client
    def on_username(self, data: dict, event: enet.Event) -> None:
        p = event.peer.incomingPeerID

        old_username = self.player_data[p].username
        if old_username == data.username:
            return
        self.player_data[p].username = self.check_username(data.username)
        self.console_msg.emit(f"{old_username} has changed their name to {self.player_data[p].username}!", ConsoleTypes.INFO)
        self.username_changed.emit((old_username, self.player_data[p].username))

        if self.player_data[p].username != data.username:
            username_data = {'dataType': ClientRcvDataTypes.USERNAME.value, 'new_username': self.player_data[p].username, 'old_username': data.username}
            self.network.send(json.dumps(username_data), event.peer)

    def on_chat_msg(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"<b>[{self.player_data[event.peer.incomingPeerID].username}]</b> {data.msg}", ConsoleTypes.DEFAULT)

        other_peers = self.network.get_other_peers(event.peer.incomingPeerID)
        data = {'dataType': ClientRcvDataTypes.CHAT_MSG.value, 'username': self.player_data[event.peer.incomingPeerID].username, 'msg': data.msg}
        for peer in other_peers:
            self.network.send(json.dumps(data), peer)

    def on_model(self, data: dict, event: enet.Event) -> None:
        other_peers = self.network.get_other_peers(event.peer.incomingPeerID)
        model_data = {'dataType': ClientRcvDataTypes.MODEL.value, 'incoming_peer_id': event.peer.incomingPeerID, 'model': data.model}
        for peer in other_peers:
            self.network.send(json.dumps(model_data), peer)

    def on_tp_info(self, data: dict, event: enet.Event) -> None:
        tp_user_data = None
        for player in self.player_data:
            if player.connected and player.username.lower() == data.tp_user.lower():
                tp_user_data = player

        # this should only happen if a user disconnects while a tp is about to happen
        if tp_user_data == None:
            self.console_msg.emit(f"The teleport for {data.tp_user} could not be fulfilled!", ConsoleTypes.ERROR)
            return

        tp_data = {'dataType': ClientRcvDataTypes.TP.value, 'lvl_id': data.lvl_id, 'tp_dest': data.tp_dest}
        peer = self.network.get_peer(tp_user_data.peer_id)
        self.network.send(json.dumps(tp_data), peer)

    def on_tp_request(self, data: dict, event: enet.Event) -> None:
        self.on_teleport_sig(data.tp_user, data.tp_dest)

    def on_change_level(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"{self.player_data[event.peer.incomingPeerID].username} has set their level to '{data.level}'!", ConsoleTypes.INFO)

    def on_tag_status(self, data: dict, event: enet.Event) -> None:
        self.player_data[event.peer.incomingPeerID].tag_status = TagStatus.TAGGER

        # check to see if this is the last hider to be found
        if not self.check_tag_end():
            self.set_tagger.emit(self.player_data[event.peer.incomingPeerID].username)
            tag_status_data = {'dataType': ClientRcvDataTypes.TAG_STATUS.value, 'tag_status': TagStatus.TAGGER.value}
            self.network.send(json.dumps(tag_status_data), event.peer)

    # PROBABLY DELETE THIS
    def on_manhunt_status(self, data: dict, event: enet.Event) -> None:
        self.player_data[event.peer.incomingPeerID].manhunt_status = ManhuntStatus.HUNTER

        # check to see if this is the last hider to be found
        if not self.check_manhunt_end():
            self.set_hunter.emit(self.player_data[event.peer.incomingPeerID].username)
            manhunt_status_data = {'dataType': ClientRcvDataTypes.MANHUNT_STATUS.value, 'manhunt_status': ManhuntStatus.HUNTER.value}
            self.network.send(json.dumps(manhunt_status_data), event.peer)

    # once all clients confirm their flags are paused, we're free to reset them all
    def on_flags_paused(self, data: dict, event: enet.Event) -> None:
        self.player_data[event.peer.incomingPeerID].flags_paused = True
        self.check_flag_reset_status()

    # when a manhunt runner takes damage, this function will send an indication to all the other clients
    def on_manhunt_damage(self, data: dict, event: enet.Event) -> None:
        other_peers = self.network.get_other_peers(event.peer.incomingPeerID)
        for peer in other_peers:
            data = {'dataType': ClientRcvDataTypes.MANHUNT_DMG.value}
            for peer in other_peers:
                self.network.send(json.dumps(data), peer)

    # in case of some packet corruption or some huge bug where a packet's dataType value is unknown, this function is called instead
    def on_unknown(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"Unknown packet type received from {self.player_data[event.peer.incomingPeerID].username}: {data.dataType}", ConsoleTypes.ERROR)

    def on_sync_flags_sig(self, toggle: bool) -> None:
        self.sync_flags = toggle

    def on_reset_flags_sig(self) -> None:
        if self.sync_flags:
            pause_flags_data = {'dataType': ClientRcvDataTypes.PAUSE_FLAGS.value}
            for peer in self.network.host.peers:
                self.network.send(json.dumps(pause_flags_data), peer, reliable=True)
        else:
            self.flag_data.reset_self()

    def on_change_level_sig(self, id: int, user: str) -> None:
        if user == "all":
            world, episode = self.level_data.get_name(id)
            if world == None:
                self.console_msg.emit("That level could not be found!", ConsoleTypes.ERROR)
                return

            self.console_msg.emit(f"Loading all users into '{world} -> {episode}'", ConsoleTypes.INFO)
            change_level_data = {'dataType': ClientRcvDataTypes.CHANGE_LEVEL.value, 'id': id}
            for peer in self.network.host.peers:
                self.network.send(json.dumps(change_level_data), peer)
        elif user.lower() in [player.username.lower() for player in self.player_data if player.connected == True]:
            world, episode = self.level_data.get_name(id)
            if world == None:
                self.console_msg.emit("That level could not be found!", ConsoleTypes.ERROR)
                return
                
            self.console_msg.emit(f"Loading {user} into '{world} -> {episode}'", ConsoleTypes.INFO)
            change_level_data = {'dataType': ClientRcvDataTypes.CHANGE_LEVEL.value, 'id': id}
            for player in self.player_data:
                if player.connected == True and player.username.lower() == user.lower():
                    peer = self.network.get_peer(player.peer_id)
                    break
                
            self.network.send(json.dumps(change_level_data), peer)
        else:
            self.console_msg.emit(f"{user} was not found in the list of usernames! Unable to change the user's level!", ConsoleTypes.ERROR)

    def on_allow_tps_sig(self, toggle: bool) -> None:
        self.allow_tps = toggle

        allow_tps_data = {'dataType': ClientRcvDataTypes.ALLOW_TPS.value, 'toggle': toggle}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(allow_tps_data), peer)

    def on_allow_level_changes_sig(self, toggle: bool) -> None:
        self.allow_level_changes = toggle

        allow_level_changes_data = {'dataType': ClientRcvDataTypes.ALLOW_LVL_CHANGES.value, 'toggle': toggle}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(allow_level_changes_data), peer)

    def on_kick_sig(self, user: str) -> None:
        if user == "all":
            for peer in self.network.host.peers:
                peer.disconnect_now(data=DisconnectSource.SVR_KICK.value)
                self.player_data[peer.incomingPeerID] = Player(peer.incomingPeerID)
            self.usernames_updated.emit([player.username for player in self.player_data if player.connected])
            self.console_msg.emit("All connected users have been kicked!", ConsoleTypes.DISCONNECT)
        else:
            id = -1
            for player in self.player_data:
                if player.username.lower() == user.lower():
                    id = player.peer_id
                    break
            for peer in self.network.host.peers:
                if peer.incomingPeerID == id:
                    peer.disconnect_now(data=DisconnectSource.SVR_KICK.value)
                    self.player_data[peer.incomingPeerID] = Player(peer.incomingPeerID)
                    self.usernames_updated.emit([player.username for player in self.player_data if player.connected])
                    self.console_msg.emit(f"{user} was kicked!", ConsoleTypes.DISCONNECT)
                    break
            else:
                self.console_msg.emit(f"Kick failed! {user} was not found!", ConsoleTypes.DISCONNECT)

    def on_list_players_sig(self) -> None:
        player_list = []
        for player in self.player_data:
            if player.connected:
                player_list.append(player.username)
        if player_list == []:
            self.console_msg.emit("Players: None", ConsoleTypes.INFO)
        else:
            self.console_msg.emit("Players: " + str(player_list), ConsoleTypes.INFO)

    def on_teleport_sig(self, tp_user: str, tp_dest: str) -> None:
        tp_user_data= None
        tp_dest_data = None
        if tp_user == tp_dest:
            self.console_msg.emit("You can't teleport a user to themselves!", ConsoleTypes.ERROR)
            return
        for player in self.player_data:
            if player.connected and player.username.lower() == tp_user.lower():
                tp_user_data = player
            elif player.connected and player.username.lower() == tp_dest.lower():
                tp_dest_data = player

        if tp_user_data == None:
            self.console_msg.emit(f"{tp_user} is not a recognized username!", ConsoleTypes.ERROR)
            return
        if tp_dest_data == None:
            self.console_msg.emit(f"{tp_dest} is not a recognized username!", ConsoleTypes.ERROR)
            return

        self.console_msg.emit(f"Teleporting {tp_user} to {tp_dest}!", ConsoleTypes.INFO)

        # tp_user and tp_dest are being sent just so that the names are saved for when the server fulfills the teleport later
        tp_info_request_data = {'dataType': ClientRcvDataTypes.TP_INFO_REQUEST.value, 'tp_user': tp_user, 'tp_dest': tp_dest}
        peer = self.network.get_peer(tp_dest_data.peer_id)
        self.network.send(json.dumps(tp_info_request_data), peer)

    def on_change_gamemode_sig(self, gamemode: GamemodeTypes):
        self.gamemode = gamemode.value
        gamemode_change_data = {'dataType': ClientRcvDataTypes.GAMEMODE_CHANGE.value, 'gamemode': gamemode.value}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(gamemode_change_data), peer)
        self.console_msg.emit(f"The gamemode has been changed!", ConsoleTypes.INFO)
        self.gamemode_change.emit(gamemode)

    def on_new_tagger_sig(self, username: str):
        for player in self.player_data:
            if player.username.lower() == username.lower() and player.connected:
                player.tag_status = TagStatus.TAGGER

                if not self.check_tag_end():
                    peer = self.network.get_peer(player.peer_id)
                    data = {'dataType': ClientRcvDataTypes.TAG_STATUS.value, 'tag_status': TagStatus.TAGGER.value}
                    self.network.send(json.dumps(data), peer)
                    self.set_tagger.emit(player.username)
                    self.console_msg.emit(f"{player.username} has been added to the tagger team!", ConsoleTypes.INFO)

                return
        else:
            self.console_msg.emit(f"{username} is not a valid username!", ConsoleTypes.ERROR)

    def on_new_hider_sig(self, username: str):
        for player in self.player_data:
            if player.username.lower() == username.lower() and player.connected:
                player.tag_status = TagStatus.HIDER

                if not self.check_tag_end():
                    peer = self.network.get_peer(player.peer_id)
                    data = {'dataType': ClientRcvDataTypes.TAG_STATUS.value, 'tag_status': TagStatus.HIDER.value}
                    self.network.send(json.dumps(data), peer)
                    self.set_hider.emit(player.username)
                    self.console_msg.emit(f"{player.username} has been added to the hider team!", ConsoleTypes.INFO)

                return
        else:
            self.console_msg.emit(f"{username} is not a valid username!", ConsoleTypes.ERROR)

    def on_tag_reset_sig(self) -> None:
        reset_tag_data = {'dataType': ClientRcvDataTypes.RESET_TAG.value}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(reset_tag_data), peer)

        for player in self.player_data:
            if player.connected:
                player.tag_status = TagStatus.HIDER
                self.set_hider.emit(player.username)

        tag_status_data = {'dataType': ClientRcvDataTypes.TAG_STATUS.value, 'tag_status': TagStatus.HIDER.value}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(tag_status_data), peer)

        self.console_msg.emit("The current tag game has been reset!", ConsoleTypes.INFO)
        self.tag_stopped.emit()

    def on_tag_refills_sig(self, toggle: bool) -> None:
        self.disable_refills = toggle

        disable_refills_data = {'dataType': ClientRcvDataTypes.TOGGLE_REFILLS.value, 'disable': toggle}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(disable_refills_data), peer, reliable=True)

    # Manhunt related
    def on_new_hunter_sig(self, username: str):
        for player in self.player_data:
            if player.username.lower() == username.lower() and player.connected:
                player.manhunt_status = ManhuntStatus.HUNTER

                if not self.check_manhunt_end():
                    peer = self.network.get_peer(player.peer_id)
                    data = {'dataType': ClientRcvDataTypes.MANHUNT_STATUS.value, 'manhunt_status': ManhuntStatus.HUNTER.value}
                    self.network.send(json.dumps(data), peer)
                    self.set_hunter.emit(player.username)
                    self.console_msg.emit(f"{player.username} has been added to the hunter team! [PLACEHOLDER MSG]", ConsoleTypes.INFO)

                return
        else:
            self.console_msg.emit(f"{username} is not a valid username!", ConsoleTypes.ERROR)

    # Manhunt related
    def on_new_runner_sig(self, username: str):
        for player in self.player_data:
            if player.username.lower() == username.lower() and player.connected:
                player.manhunt_status = ManhuntStatus.RUNNER

                if not self.check_manhunt_end():
                    peer = self.network.get_peer(player.peer_id)
                    data = {'dataType': ClientRcvDataTypes.MANHUNT_STATUS.value, 'manhunt_status': ManhuntStatus.RUNNER.value}
                    self.network.send(json.dumps(data), peer)
                    self.set_runner.emit(player.username)
                    self.console_msg.emit(f"{player.username} has been added to the runner team! [PLACEHOLDER MSG]", ConsoleTypes.INFO)

                return
        else:
            self.console_msg.emit(f"{username} is not a valid username!", ConsoleTypes.ERROR)

    # Manhunt related
    def on_manhunt_reset_sig(self) -> None:
        reset_manhunt_data = {'dataType': ClientRcvDataTypes.RESET_MANHUNT.value}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(reset_manhunt_data), peer)

        for player in self.player_data:
            if player.connected:
                player.manhunt_status = ManhuntStatus.RUNNER
                self.set_runner.emit(player.username)

        manhunt_status_data = {'dataType': ClientRcvDataTypes.MANHUNT_STATUS.value, 'manhunt_status': ManhuntStatus.RUNNER.value}
        for peer in self.network.host.peers:
            self.network.send(json.dumps(manhunt_status_data), peer)

        self.console_msg.emit("The current manhunt game has been reset! [PLACEHOLDER MSG]", ConsoleTypes.INFO)
        self.manhunt_stopped.emit()

    # Validates that a username isn't duplicated
    def check_username(self, username: str) -> str:
        current_usernames_list = [player.username for player in self.player_data if player.connected == True]
        new_username = username
        i = 1
        while (new_username in current_usernames_list):
            new_username = f"{username}({i})"
            i += 1
        return new_username
    
    def check_flag_reset_status(self) -> None:
        if not False in [player.flags_paused for player in self.player_data if player.connected]:
            for player in self.player_data:
                player.flags_paused = False
            self.flag_data.reset_self()
            reset_flag_data = {'dataType': ClientRcvDataTypes.RESET_FLAGS.value}
            for peer in self.network.host.peers:
                self.network.send(json.dumps(reset_flag_data), peer, reliable=True)

    def check_tag_end(self) -> bool:
        if self.tag_running and ([player.tag_status for player in self.player_data if player.connected].count(TagStatus.HIDER) == 0 or
            [player.tag_status for player in self.player_data if player.connected].count(TagStatus.TAGGER) == 0):
            self.stop_tag()

            for player in self.player_data:
                if player.connected:
                    player.tag_status = TagStatus.HIDER
                    self.set_hider.emit(player.username)

            tag_status_data = {'dataType': ClientRcvDataTypes.TAG_STATUS.value, 'tag_status': TagStatus.HIDER.value}
            for peer in self.network.host.peers:
                self.network.send(json.dumps(tag_status_data), peer)
            
            return True
        else:
            return False
        
    def check_manhunt_end(self) -> bool:
        if self.manhunt_running and ([player.manhunt_status for player in self.player_data if player.connected].count(ManhuntStatus.RUNNER) == 0 or
            [player.manhunt_status for player in self.player_data if player.connected].count(ManhuntStatus.HUNTER) == 0):
            self.stop_manhunt()

            for player in self.player_data:
                if player.connected:
                    player.manhunt_status = ManhuntStatus.RUNNER
                    self.set_hider.emit(player.username)

            manhunt_status_data = {'dataType': ClientRcvDataTypes.MANHUNT_STATUS.value, 'manhunt_status': ManhuntStatus.RUNNER.value}
            for peer in self.network.host.peers:
                self.network.send(json.dumps(manhunt_status_data), peer)
            
            return True
        else:
            return False
        
