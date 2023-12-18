from PySide6.QtCore import *
from time import sleep
from threading import Thread, Timer
from queue import Queue
import json
import os
import enet
import psutil
import sys

from Client.DolphinMemoryLib import Dolphin
from Client.InGameVars import InGameVars
from Client.ClientData import Player, ClientData, ClientPointers, DummyPointers, FlagData
from Misc.Network import NetworkClient
from Misc.DataTypes import ClientRcvDataTypes, ServerRcvDataTypes, DisconnectSource, ConsoleTypes, GamemodeTypes, TagStatus, ManhuntStatus
from Misc.LevelData import LevelData

class Client(QObject):

    #######################
    ####### SIGNALS #######
    #######################

    console_msg = Signal(str, ConsoleTypes)
    client_started = Signal()
    client_stopped = Signal()
    connection_succeeded = Signal()
    connection_failed = Signal()
    disconnection_succeeded = Signal()
    username_changed = Signal(str)
    usernames_updated = Signal(list)
    allow_tps_sig = Signal(bool)
    allow_level_changes_sig = Signal(bool)




    ##########################
    #### GUI-CALLED FUNCS ####
    ##########################

    def __init__(self, username: str, model_list: list, model: str, version: str) -> None:
        super().__init__()

        self.directory = os.path.abspath(os.path.dirname(sys.argv[0]))
        self.version = version
        
        self.running = True
        self.username = username
        self.model_list = [model.lower() for model in model_list]
        self.model = model

        self.memory = Dolphin()
        self.memory.console_msg.connect(self.on_console_msg)

        self.client_data = ClientData(self.memory)
        self.flag_data = FlagData(self.memory)
        self.queued_flag_updates = Queue()
        self.pause_flags = False
        self.network = NetworkClient()
        self.is_connected = False
        self.player_num = 1
        self.peer_id = 0
        self.player_data = []
        self.level_data = LevelData()
        self.gamemode = GamemodeTypes.DEFAULT.value
        self.tag_status = TagStatus.HIDER.value
        self.manhunt_status = ManhuntStatus.RUNNER.value
        self.allow_tps = True
        self.allow_level_changes = True

        # this is essentially used like a switch statement
        self.receive_opts = {
            ClientRcvDataTypes.SELF_CONNECT.value: self.on_self_connect,
            ClientRcvDataTypes.CONNECT.value: self.on_connect,
            ClientRcvDataTypes.DISCONNECT.value: self.on_disconnect,
            ClientRcvDataTypes.CLI_DATA.value: self.on_cli_data,
            ClientRcvDataTypes.FLG_DATA.value: self.on_flg_data,
            ClientRcvDataTypes.CHAT_MSG.value: self.on_chat_msg,
            ClientRcvDataTypes.USERNAME.value: self.on_username,
            ClientRcvDataTypes.MODEL.value: self.on_model,
            ClientRcvDataTypes.CHANGE_LEVEL.value: self.on_change_level,
            ClientRcvDataTypes.TAG_STATUS.value: self.on_tag_status,
            ClientRcvDataTypes.TP.value: self.on_tp,
            ClientRcvDataTypes.TP_INFO_REQUEST.value: self.on_tp_info_request,
            ClientRcvDataTypes.GAMEMODE_CHANGE.value: self.on_gamemode_change,
            ClientRcvDataTypes.TAG_STATUS.value: self.on_tag_status,
            ClientRcvDataTypes.START_TAG.value: self.on_start_tag,
            ClientRcvDataTypes.PAUSE_FLAGS.value: self.on_pause_flags,
            ClientRcvDataTypes.RESET_FLAGS.value: self.on_reset_flags,
            ClientRcvDataTypes.RESET_TAG.value: self.on_reset_tag,
            ClientRcvDataTypes.TOGGLE_REFILLS.value: self.on_toggle_refills,
            ClientRcvDataTypes.ALLOW_TPS.value: self.on_allow_tps,
            ClientRcvDataTypes.ALLOW_LVL_CHANGES.value: self.on_allow_level_changes,
            ClientRcvDataTypes.MANHUNT_STATUS.value: self.on_manhunt_status,
            ClientRcvDataTypes.START_MANHUNT.value: self.on_start_manhunt,
            ClientRcvDataTypes.RESET_MANHUNT.value: self.on_reset_manhunt
        }

        self.send_thread = Thread(target=self.client_send_loop)
        self.receive_thread = Thread(target=self.client_receive)

    # making this a lambda caused errors on ubuntu for some reason, so I've made it a function instead
    def on_console_msg(self, string, console_type):
        self.console_msg.emit(string, console_type)

    # due to the mix of c++ bindings with PySide6 and PyEnet, python's native garbage collector 
    # doesn't seem to do the complete job for us, so we have to manually delete everything.
    # I'm not 100% sure that all deletions are necessary, but better safe than sorry
    def cleanup(self) -> None:
        # looping through every attribute (a copy is necessary because vars(self) changes as we delete attributes)
        for attr in vars(self).copy():
            # We don't want to include attributes from the class Server is derived from (QObject), and we don't want to delete our Signals
            if not hasattr(QObject, attr) and not attr.startswith('__') and not isinstance(getattr(self, attr), Signal):
                delattr(self, attr)

    def inject_models(self) -> None:
        self.memory.write_u32(0x82500000, 0xFFFFFFFF)   # in case no models are injected, this is used to indicate this function has run successfully

        baseAddress = 0x82500000
        offset = 0
        bmdPointersGuide = ['ma_mdl1.bmd', 'ma_cap1.bmd', 'ma_cap3.bmd', 'ma_hnd2r.bmd', 'ma_hnd2l.bmd', 'ma_hnd3r.bmd', 'ma_hnd3l.bmd', 'ma_hnd4r.bmd', 'ma_glass1.bmd']

        # the following section writes the bmd byte data into memory and the corresponding pointer for it.
        # if you want the longer explanation, then here it is: in the main.c for the sunshine c kit, 
        # I've initalized a 2d array of u32 pointers for each model's bmds (u32** bmdPointers[10][10]).
        # There are 10 'slots' for 10 different models, and inside each slot is room for 10 bmd pointers.
        # This comes out to be 40 bytes for each slot/model, and 400 bytes total (just for the pointers, not the bmd itself obviously). 
        # Here's what each of the 10 pointers inside each slot are reserved for (this is what you find in bmdPointersGuide):
        # 0 = mdl1, 1 = cap1, 2 = cap3, 3 = hnd2r, 4 = hnd2l, 5 = hnd3r, 6 = hnd3l, 7 = hnd4r, 8 = glass1, 9 = extra(J.I.C)
        # You don't need all of these bmds for each model (like wario), but you do need them all for others (like piantissimo);
        # it really just depends on how much you change the model from the default mario model. After the 
        # pointers are written to memory, the c kit asm is able to use them to switch models.
        # There will probably be support for a larger amount of bmds or other j3d file types in the future
        
        count = 0
        for model_index, model_dir_entry in enumerate(os.scandir(f"{self.directory}/Model Data")):
            if count >= 16:
                break
            if model_dir_entry.is_dir():
                for bmd_dir_entry in os.scandir(model_dir_entry):
                    if bmd_dir_entry.is_file():
                        if bmd_dir_entry.name in bmdPointersGuide:
                            with open(bmd_dir_entry, "rb") as f:
                                bmd_data = bytes(f.read())

                            bmd_index = bmdPointersGuide.index(bmd_dir_entry.name)
                            self.memory.write_u32(InGameVars.BMD_POINTERS + (model_index * 40) + (bmd_index * 4), baseAddress + offset)
                            self.memory.write(baseAddress + offset, bmd_data)
                            offset += len(bmd_data)
                        else:
                            self.console_msg.emit(f"{bmd_dir_entry.name} is not a valid model file name! It's been skipped!", ConsoleTypes.ERROR)
                count += 1

        if self.model in self.model_list:
            model_index = self.model_list.index(self.model)
        else:
            model_index = 0

        if model_index == 0:
            model_index = -1    # mario's model isn't technically included, so it's represented as -1
        else:
            model_index -= 1
        self.memory.write_s32(InGameVars.MODEL_INDEX, model_index)

        for player in self.player_data:
            if player.connected == True:
                self.update_dummy_model(player.model, self.peer_id, player.peer_id)

    # called from gui thread to update username
    def update_username(self, username: str) -> None:
        new_username = self.check_username(username)
        if new_username != username:
            self.console_msg.emit(f"You tried to change your name to {username}, but that name is taken!", ConsoleTypes.WARNING)
            self.username_changed.emit(new_username)
        self.console_msg.emit(f"Username changed to {new_username}!", ConsoleTypes.INFO)
        self.username = new_username
        if self.is_connected:
            data = {'dataType': ServerRcvDataTypes.USERNAME.value, 'username': self.username}
            self.network.send(json.dumps(data))

    def chat_message(self, message: str) -> None:
        if self.is_connected:
            data = {'dataType': ServerRcvDataTypes.CHAT_MSG.value, 'msg': message}
            self.network.send(json.dumps(data))

    # Validates that a username isn't duplicated
    def check_username(self, username: str) -> str:
        current_usernames_list = [player.username for player in self.player_data if player.connected == True]
        new_username = username
        i = 1
        while (new_username in current_usernames_list):
            new_username = f"{username}({i})"
            i += 1
        return new_username

    # called from gui thread to update model index
    def update_model(self, model: str) -> None:
        if model == self.model:
            return
        
        if not model in self.model_list:
            self.console_msg.emit(f"You tried to change your model to {model}! But that model could not be found in the 'Model Data' directory!", ConsoleTypes.ERROR)
            return
        model_index = self.model_list.index(model)
        if model_index == 0:
            model_index = -1
        else:
            model_index -= 1
        self.memory.write_s32(InGameVars.MODEL_INDEX, model_index)
        self.console_msg.emit(f"Your model was changed to {model}", ConsoleTypes.INFO)
        self.model = model
        if self.is_connected:
            data = {'dataType': ServerRcvDataTypes.MODEL.value, 'model': self.model}
            self.network.send(json.dumps(data))

    # called from gui thread to update music volume
    def update_volume(self, volume: int) -> None:
        volume /= 100
        trackOne = self.memory.read_u32(0x803e9c80)
        trackTwo = self.memory.read_u32(0x803e9c84)
        trackThree = self.memory.read_u32(0x803e9c88)
        if trackOne != 0:
            trackOne = self.memory.read_u32(trackOne + 0x14)
            if trackOne != 0:
                trackOne = self.memory.read_u32(trackOne + 0x38)
                trackOne += 0x198
                self.memory.write_f32(trackOne, volume)
        if trackTwo != 0:
            trackTwo = self.memory.read_u32(trackTwo + 0x14)
            if trackTwo != 0:
                trackTwo = self.memory.read_u32(trackTwo + 0x38)
                trackTwo += 0x198
                self.memory.write_f32(trackTwo, volume)
        if trackThree != 0:
            trackThree = self.memory.read_u32(trackThree + 0x14)
            if trackThree != 0:
                trackThree = self.memory.read_u32(trackThree + 0x38)
                trackThree += 0x198
                self.memory.write_f32(trackThree, volume)
        self.memory.write_f32(0x8040c1c0, volume)

        self.memory.write_f32(InGameVars.MUSIC_VOLUME, volume)

    def hook_sms(self) -> None:
        if not self.memory.hook_any_dolphin():
            self.stop_client()
            return
        self.dolphin_process = psutil.Process(self.memory.dolphin_pid)

        # start a qtimer to check if dolphin is still running every 1 second
        self.check_dolphin_process_timer = QTimer()
        self.check_dolphin_process_timer.timeout.connect(self.check_dolphin_process)
        self.check_dolphin_process_timer.start(1000)

        self.client_started.emit()
        self.send_thread.start()
        self.receive_thread.start()

    def client_connect(self, ip: str, port: int) -> None:
        self.console_msg.emit("Attempting to connect to the host!", ConsoleTypes.CONNECT)
        data = {"dataType": ServerRcvDataTypes.CONNECT.value, "username": self.username, "model": self.model, "version": self.version}
        if self.network.connect(ip, port, data):
            self.is_connected = True
            self.console_msg.emit("Successfully connected to the host!", ConsoleTypes.CONNECT)
            self.connection_succeeded.emit()
            self.memory.write_u8(InGameVars.CONNECTED, 1)
        else:
            self.is_connected = False
            self.console_msg.emit("Unsuccessful in connecting to the host!", ConsoleTypes.ERROR)
            self.connection_failed.emit()

    def client_disconnect(self) -> None:
        self.console_msg.emit("Attempting to disconnect from the host!", ConsoleTypes.INFO)
        self.network.disconnect()
        self.disconnection_succeeded.emit()
        self.usernames_updated.emit([])
        self.is_connected = False
        self.memory.write_u8(InGameVars.CONNECTED, 0)

    def check_dolphin_process(self):
        try:
            if not self.dolphin_process.is_running():
                self.console_msg.emit("The hooked Dolphin process has ended!", ConsoleTypes.ERROR)
                self.stop_client()
        except:
            self.console_msg.emit("The hooked Dolphin process has ended!", ConsoleTypes.ERROR)
            self.stop_client()

    def stop_client(self) -> None:
        if self.is_connected:
            self.client_disconnect()

        self.running = False

        if self.receive_thread.is_alive():
            self.receive_thread.join()
        if self.send_thread.is_alive():
            self.send_thread.join()

        self.usernames_updated.emit([])

        self.memory.cleanup()
        self.network.cleanup()
        self.cleanup()
        
        self.client_stopped.emit()
        self.deleteLater()

    def on_change_level_sig(self, lvl_id: int):
        if not self.allow_level_changes:
            self.console_msg.emit(f"Level changes are not enabled by the server!", ConsoleTypes.ERROR)
            return

        world, episode = self.level_data.get_name(lvl_id)
        if world == None:
            self.console_msg.emit("That level could not be found!", ConsoleTypes.ERROR)
            return

        self.console_msg.emit(f"Loading into '{world} -> {episode}'", ConsoleTypes.INFO)

        clt = ClientPointers(self.memory)
        self.memory.write_u8(clt.pPauseMenu2 + 0x109, 9)            # tells our custom asm to change stage
        self.memory.write_u16(clt.pApplication + 0x12, lvl_id)      # world and episode id
        self.memory.write_u8(clt.pMarDirector + 0x64, 5)            # game state
        self.memory.write_u32(clt.pPauseMenu2 + 0x10, 5)            # pause state?
        self.memory.write_u8(clt.pPauseMenu2 + 0xE0, 2)             # active pause menu element

        if self.is_connected:
            data = {'dataType': ServerRcvDataTypes.CHANGE_LEVEL.value, 'level': f"{world} -> {episode}"}
            self.network.send(json.dumps(data))

    def on_list_players_sig(self):
        player_list = []
        for player in self.player_data:
            if player.connected:
                player_list.append(player.username)
        if player_list == []:
            self.console_msg.emit("Players: None", ConsoleTypes.INFO)
        else:
            self.console_msg.emit("Players: " + str(player_list), ConsoleTypes.INFO)

    def on_teleport_sig(self, tp_dest: str):
        if not self.allow_tps:
            self.console_msg.emit(f"Teleports are not enabled by the server!", ConsoleTypes.ERROR)
            return

        tp_user_data = None
        for player in self.player_data:
            if player.connected and player.username.lower() == tp_dest.lower():
                tp_user_data = player
        
        if not tp_user_data:
            self.console_msg.emit(f"{tp_dest} is not a recognized username!", ConsoleTypes.ERROR)
            return

        data = {'dataType': ServerRcvDataTypes.TP_REQUEST.value, 'tp_user': self.username, 'tp_dest': tp_dest}
        self.network.send(json.dumps(data))




    ##############################
    #### CLIENT RECEIVE FUNCS ####
    ##############################

    def client_receive(self) -> None:
        while self.running:
            sleep(1/1920)
            if self.is_connected == False:
                continue

            self.update_flag_data()

            event = self.network.receive()

            if event.type == enet.EVENT_TYPE_NONE:
                continue

            elif event.type == enet.EVENT_TYPE_CONNECT:
                self.console_msg.emit(f"You have connected to the server!", ConsoleTypes.CONNECT)
                continue
            elif event.type == enet.EVENT_TYPE_DISCONNECT:
                if event.data == DisconnectSource.DEFAULT.value:
                    self.console_msg.emit(f"You have been disconnected from the server!", ConsoleTypes.DISCONNECT)
                elif event.data == DisconnectSource.SVR_END.value:
                    self.console_msg.emit(f"You have been disconnected! The server has ended!", ConsoleTypes.DISCONNECT)
                elif event.data == DisconnectSource.SVR_KICK.value:
                    self.console_msg.emit(f"You have been kicked from the server!", ConsoleTypes.DISCONNECT)
                elif event.data == DisconnectSource.VERSION.value:
                    self.console_msg.emit(f"Your version of SMSO is not compatible with the server!", ConsoleTypes.DISCONNECT)
                else:
                    self.console_msg.emit(f"You have been disconnected from the server!", ConsoleTypes.DISCONNECT)
                
                for i, player in enumerate(self.player_data):
                    self.player_data[i] = Player(i)

                self.is_connected = False
                self.disconnection_succeeded.emit()
                self.usernames_updated.emit([player.username for player in self.player_data if player.connected])
                continue

            elif event.type == enet.EVENT_TYPE_RECEIVE:
                data = self.network.decode_data(event.packet.data)
                # this line accesses the function specified by the dataType within self.receive_opts, which is created in __init__(). if the
                # data type isn't found, it calls self.on_unknown() instead
                self.receive_opts.get(data.dataType, self.on_unknown)(data, event)

    # data about all other clients when you connect
    def on_self_connect(self, data: dict, event: enet.Event) -> None:
        if 'version' not in data:
            chat_data = {'dataType': ServerRcvDataTypes.CHAT_MSG.value, 'msg': f"Your version of SMSO is not compatible with this client! ({self.version})"}
            self.network.send(json.dumps(chat_data), reliable=True)
            self.network.peer.disconnect_later(data=DisconnectSource.VERSION.value)
            self.console_msg.emit(f"The server's version is not compatible with yours!", ConsoleTypes.DISCONNECT)
            return
        elif data.pop('version') != self.version:
            self.network.peer.disconnect_now(data=DisconnectSource.VERSION.value)
            self.console_msg.emit(f"The server's version is not compatible with yours!", ConsoleTypes.DISCONNECT)
            return

        data.pop("dataType")
        self.player_num = data.pop("player_num")
        self.peer_id = data.pop("self_peer_id")

        self.memory.write_u8(InGameVars.FLUDD_REFILLS, data.pop("disable_refills"))
        self.memory.write_u32(InGameVars.GAMEMODE, data.pop("gamemode"))

        if data.pop('allow_tps'):
            self.allow_tps = True
            self.allow_tps_sig.emit(True)
        else:
            self.allow_tps = False
            self.allow_tps_sig.emit(False)

        if data.pop('allow_level_changes'):
            self.allow_level_changes = True
            self.allow_level_changes_sig.emit(True)
        else:
            self.allow_level_changes = False
            self.allow_level_changes_sig.emit(False)

        for i in range(self.player_num):
            self.player_data.append(Player(i))

        for username, dict in data.items():
            self.player_data[dict.incoming_peer_id].peer_id = dict.incoming_peer_id
            self.player_data[dict.incoming_peer_id].connected = True
            self.player_data[dict.incoming_peer_id].username = username
            self.player_data[dict.incoming_peer_id].model = dict.model

            self.update_dummy_model(dict.model, self.peer_id, dict.incoming_peer_id)

        self.usernames_updated.emit([player.username for player in self.player_data if player.connected])

    # data about another user connecting to the server
    def on_connect(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"{data.username} has connected to the server!", ConsoleTypes.CONNECT)
        
        self.player_data[data.incoming_peer_id].connected = True
        self.player_data[data.incoming_peer_id].username = data.username
        self.player_data[data.incoming_peer_id].model = data.model

        self.update_dummy_model(data.model, self.peer_id, data.incoming_peer_id)

        self.usernames_updated.emit([player.username for player in self.player_data if player.connected])

    def on_disconnect(self, data: dict, event: enet.Event) -> None:
        player = self.player_data[data.incoming_peer_id]
        self.console_msg.emit(f"{player.username} has disconnected from the server!", ConsoleTypes.DISCONNECT)
        player.connected = False

        # set the disconnected mario invisible
        clt = ClientPointers(self.memory)
        if self.memory.read_u32(InGameVars.MARIOS - 4) > 1 and clt.gameState != 9 and clt.gameState != 0:
            offset = self.get_offset(self.peer_id, data.incoming_peer_id)
            dmy = DummyPointers(self.memory.read_u32(InGameVars.MARIOS + 4 + offset*4), self.memory)
            self.memory.write_u32(dmy.pDummyMario + 0x7C, 0x0000133F)

        self.usernames_updated.emit([player.username for player in self.player_data if player.connected])

    # data from another client
    def on_cli_data(self, data: dict, event: enet.Event) -> None:
        offset = self.get_offset(self.peer_id, data.incoming_peer_id)
                
        clt = ClientPointers(self.memory)
        dmy = DummyPointers(self.memory.read_u32(InGameVars.MARIOS + 4 + offset*4), self.memory)    # retrieves pointers for dummy mario

        if (data.level != clt.level or clt.gameState == 9 or clt.gameState == 0 or data.episode == 0xFF or
        data.gameState == 9 or data.gameState == 0 or self.memory.read_u32(InGameVars.MARIOS - 4) <= 1):
            # if the incoming client's data doesn't pass the checks, and we aren't in a loading state, and 
            # the player number is larger than 1, then we make the dummy mario invisible
            if self.memory.read_u32(InGameVars.MARIOS - 4) > 1 and clt.gameState != 9 and clt.gameState != 0:
                self.memory.write_u32(dmy.pDummyMario + 0x7C, 0x0000133F)
            return

        # this is used to turn the dummy marios visible if they aren't yet (gameState 1 is the stage demo scene btw)
        if self.memory.read_u8(dmy.pDummyMario + 0x115) == 0x10 and data.gameState != 1:
            self.memory.write_u32(dmy.pDummyMario + 0x7C, 0x00001337)
            return

        # flooded plaza stuff
        if data.level == 0x1 and data.episode == 0x09 and self.memory.read_u16(clt.pApplication + 0xE) != 0x109:  # checks to see if another player is in dolpic 9(flooded plaza)
            data.yPos += 1000  # since dolpic 9 is lower on the y axis than the other plazas, we 1000 back to sync it
        if self.memory.read_u16(clt.pApplication + 0xE) == 0x109 and data.level == 0x1 and data.episode != 0x09:  # checks to see if the player is in dolpic 9, but not other players
            data.yPos -= 1000  # since dolpic 9 is lower on the y axis than the other plazas, we subtract 1000 back to sync it

        # writes all of the dummy mario's position data
        self.memory.write_f32(dmy.pDummyMario + 0x10, data.xPos)
        self.memory.write_f32(dmy.pDummyMario + 0x14, data.yPos)
        self.memory.write_f32(dmy.pDummyMario + 0x18, data.zPos)
        self.memory.write_u16(dmy.pDummyMario + 0x94, data.xAng)
        self.memory.write_u16(dmy.pDummyMario + 0x96, data.yAng)
        self.memory.write_u16(dmy.pDummyMario + 0x98, data.zAng)
        self.memory.write_u16(dmy.pDummyMario + 0x90, data.accDir)
        self.memory.write_u32(dmy.pDummyMario + 0x78, data.unkOne)
        self.memory.write_f32(dmy.pDummyMario + 0xEB8, data.unkTwo)
        self.memory.write_f32(dmy.pDummyMario + 0x8C, data.baseAcc)

        # this is somewhat lazy, but these are all states that can crash the game in some way,
        # so we just don't sync them (stuff like tightropes, poles, blooper racing, etc.)
        x = data.currentState
        if (x != 0x00001336 and x != 0x2FFCFFE8 and x != 0x00001302 and x != 0x10100341 and 
        x != 0x18100340 and x != 0x10100343 and x != 0x00000350 and x != 0x00000351 and x != 0x00000352
        and x != 0x0000035B and x != 0x00000353 and x != 0x0000035C and x != 0x10000357 and 
        x != 0x10000556 and x != 0x10000554 and x != 0x10000358 and x != 0x00810446 and x != 0x10001308
        and x != 0x00000560 and x != 0x81089B):
            self.memory.write_u32(dmy.pDummyMario + 0x7C, data.currentState)
            self.memory.write_u32(dmy.pDummyMario + 0x80, data.previousState)
            self.memory.write_u32(dmy.pDummyMario + 0x84, data.substate)

        # writes all of the dummy mario's state data (the chunk above does too, but there was already a comment there)
        self.memory.write_u64(dmy.pWaterGun + 0x1C80, data.fluddVals)
        if data.marioFlags != 0x00008100:
            self.memory.write_u32(dmy.pDummyMario + 0x118, data.marioFlags)
        self.memory.write_f32(dmy.pDummyMario + 0xB0, data.fwdSpeed)
        self.memory.write_u16(dmy.pDummyMario + 0x96, data.extraAngles)
        self.memory.write_u16(dmy.pDummyMario + 0x120, data.health)
        self.memory.write_u32(dmy.pDummyMario + 0x74, data.inputFlags)
        self.memory.write_u32(dmy.pMarioController + 0x1C, data.rButton)
        # memory.write_u32(p.pDummyMario + 0x380, data.fluddAnims)
        self.memory.write_u16(dmy.pWaterGun + 0x37A, data.fluddAngle)
        self.memory.write_u8(dmy.pYoshi, data.yoshiState)
        self.memory.write_u32(dmy.pYoshi + 0xC, data.juiceLevel)
        self.memory.write_u32(dmy.pYoshi + 0xB8, data.flutterState)
        self.memory.write_u8(dmy.pWaterGun + 0x715, data.marioSpamSpray)
        self.memory.write_u8(dmy.pWaterGun + 0x153D, data.yoshiSpamSpray)
        self.memory.write_u8(dmy.pMarioCap + 0x5, data.sunglasses)

    # data to sync game flags
    # we can assume the server's flag data is always the most updated, so we just overwrite our own
    def on_flg_data(self, data: dict, event: enet.Event) -> None:
        if len(data.shines_ids) != 0:
            for id in data.shines_ids:
                self.queued_flag_updates.put((0, id))
        if len(data.blues_ids) != 0:
            for id in data.blues_ids:
                self.queued_flag_updates.put((1, id))
        if len(data.misc1_ids) != 0:
            for id in data.misc1_ids:
                self.queued_flag_updates.put((2, id))
        if len(data.misc2_ids) != 0:
            for id in data.misc2_ids:
                self.queued_flag_updates.put((2, id))

    # data on chat message from another player
    def on_chat_msg(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"<b>[{data.username}]</b> {data.msg}", ConsoleTypes.DEFAULT)

    # data on username change (happens when duplicate usernames occur or when sending username lists over)
    def on_username(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"Your username was changed to {data.new_username} because {data.old_username} was taken!", ConsoleTypes.WARNING)
        self.username = data.new_username
        self.username_changed.emit(self.username)

    # data on model changes? (idk if this will ever be used)
    def on_model(self, data: dict, event: enet.Event) -> None:
        self.update_dummy_model(data.model, self.peer_id, data.incoming_peer_id)

    # data on level changes
    def on_change_level(self, data: dict, event: enet.Event) -> None:
        clt = ClientPointers(self.memory)
        self.memory.write_u8(clt.pPauseMenu2 + 0x109, 9)            # tells our custom asm to change stage
        self.memory.write_u16(clt.pApplication + 0x12, data.id)     # world and episode id
        self.memory.write_u8(clt.pMarDirector + 0x64, 5)            # game state
        self.memory.write_u32(clt.pPauseMenu2 + 0x10, 5)            # pause state?
        self.memory.write_u8(clt.pPauseMenu2 + 0xE0, 2)             # active pause menu element
        self.console_msg.emit("The server has changed your stage!", ConsoleTypes.INFO)

    # data on tag. this may get incorporated into a gamemode category eventually
    def on_tag_status(self, data: dict, event: enet.Event) -> None:
        self.tag_status = data.tag_status
        if data.tag_status == TagStatus.TAGGER.value:
            self.console_msg.emit("The server has made you a tagger!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.IS_TAGGER, 1)
        elif data.tag_status == TagStatus.HIDER.value:
            self.console_msg.emit("The server has made you a hider!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.IS_TAGGER, 0)

    def on_tp(self, data: dict, event: enet.Event) -> None:
        clt = ClientPointers(self.memory)
        self_lvl_id = self.memory.read_u16(clt.pApplication + 0x12)

        if self_lvl_id != data.lvl_id:
            self.memory.write_u8(clt.pPauseMenu2 + 0x109, 9)                # tells our custom asm to change stage
            self.memory.write_u16(clt.pApplication + 0x12, data.lvl_id)     # world and episode id
            self.memory.write_u8(clt.pMarDirector + 0x64, 5)                # game state
            self.memory.write_u32(clt.pPauseMenu2 + 0x10, 5)                # pause state?
            self.memory.write_u8(clt.pPauseMenu2 + 0xE0, 2)                 # active pause menu element

            self.tp_timer = Timer(1.0, lambda: self.check_if_tp(data.tp_dest))
            self.tp_timer.start()
        else:
            if self.do_tp(data.tp_dest):
                self.console_msg.emit(f"Teleport to {data.tp_dest} succeeded!", ConsoleTypes.INFO)
            else:
                self.console_msg.emit(f"Could not fulfill teleport request!", ConsoleTypes.ERROR)

    # when this client needs to be teleported to, the server requests stage data
    def on_tp_info_request(self, data: dict, event: enet.Event) -> None:
        clt = ClientPointers(self.memory)
        lvl_id = self.memory.read_u16(clt.pApplication + 0x12)
        tp_info = {'dataType': ServerRcvDataTypes.TP_INFO.value, 'lvl_id': lvl_id, 'tp_user': data.tp_user, 'tp_dest': data.tp_dest}
        self.network.send(json.dumps(tp_info))

    def on_gamemode_change(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit("The gamemode has been changed by the server!", ConsoleTypes.INFO)
        self.gamemode = data.gamemode
        self.memory.write_u32(InGameVars.GAMEMODE, data.gamemode)

    def on_start_tag(self, data: dict, event: enet.Event) -> None:
        if data.start:
            self.console_msg.emit("The server has started tag!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.TAG_ACTIVE, 1)
        else:
            self.console_msg.emit("The server has stopped tag!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.TAG_ACTIVE, 0)

    def on_pause_flags(self, data: dict, event: enet.Event) -> None:
        self.pause_flags = True
        flags_paused_data = {'dataType': ServerRcvDataTypes.FLAGS_PAUSED.value}
        self.network.send(json.dumps(flags_paused_data), reliable=True)

    def on_reset_flags(self, data: dict, event: enet.Event) -> None:
        self.memory.write_u8(InGameVars.RESET_FLAGS, 1)
        self.reset_flags_timer = Timer(1.0, lambda: self.check_if_reset())
        self.reset_flags_timer.start()

    def on_reset_tag(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit("The server has reset tag!", ConsoleTypes.INFO)
        self.memory.write_u8(InGameVars.TAG_RESET, 1)

    def on_toggle_refills(self, data: dict, event: enet.Event) -> None:
        self.memory.write_u8(InGameVars.FLUDD_REFILLS, data.disable)
        if data.disable:
            self.console_msg.emit("FLUDD Refills for hiders have been disabled!", ConsoleTypes.INFO)
        else:
            self.console_msg.emit("FLUDD Refills for hiders have been enabled!", ConsoleTypes.INFO)

    def on_allow_tps(self, data: dict, event: enet.Event) -> None:
        self.allow_tps = data.toggle
        if data.toggle:
            self.console_msg.emit("Teleports for clients have been turned on!", ConsoleTypes.INFO)
            self.allow_tps_sig.emit(True)
        else:
            self.console_msg.emit("Teleports for clients have been turned off!", ConsoleTypes.INFO)
            self.allow_tps_sig.emit(False)

    def on_allow_level_changes(self, data: dict, event: enet.Event) -> None:
        self.allow_level_changes = data.toggle
        if data.toggle:
            self.console_msg.emit("Level changes for clients have been turned on!", ConsoleTypes.INFO)
            self.allow_level_changes_sig.emit(True)
        else:
            self.console_msg.emit("Level changes for clients have been turned off!", ConsoleTypes.INFO)
            self.allow_level_changes_sig.emit(False)

    def on_manhunt_status(self, data: dict, event: enet.Event) -> None:
        self.manhunt_status = data.manhunt_status
        if data.manhunt_status == ManhuntStatus.HUNTER.value:
            self.console_msg.emit("The server has made you a hunter!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.IS_HUNTER, 1)
        elif data.manhunt_status == ManhuntStatus.RUNNER.value:
            self.console_msg.emit("The server has made you a runner!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.IS_HUNTER, 0)

    def on_start_manhunt(self, data: dict, event: enet.Event) -> None:
        if data.start:
            self.console_msg.emit("The server has started manhunt!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.MANHUNT_ACTIVE, 1)
        else:
            self.console_msg.emit("The server has stopped manhunt!", ConsoleTypes.INFO)
            self.memory.write_u8(InGameVars.MANHUNT_ACTIVE, 0)

    def on_reset_manhunt(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit("The server has reset manhunt!", ConsoleTypes.INFO)
        self.memory.write_u8(InGameVars.MANHUNT_RESET, 1)

    # in case of some packet corruption or some huge bug where a packet's dataType value is unknown, this function is called instead
    def on_unknown(self, data: dict, event: enet.Event) -> None:
        self.console_msg.emit(f"Unknown packet type received from the server: {data.dataType}", ConsoleTypes.ERROR)

    def get_offset(self, self_peer_id: int, incoming_peer_id: int) -> int:
        if incoming_peer_id > self_peer_id:
            return incoming_peer_id-1
        else:
            return incoming_peer_id

    def update_flag_data(self) -> None:
        while not self.queued_flag_updates.empty() and self.memory.read_s32(InGameVars.FLAG_TO_UPDATE) == -1:
            flag_type, flag_id = self.queued_flag_updates.get()
            self.memory.write_u32(InGameVars.FLAG_TO_UPDATE + 4, flag_id)
            self.memory.write_u32(InGameVars.FLAG_TO_UPDATE, flag_type)

    # updates one of the dummy marios' model index
    def update_dummy_model(self, model: str, self_peer_id: int, incoming_peer_id: int) -> None:
        offset = self.get_offset(self_peer_id, incoming_peer_id)
        if not model in self.model_list:
            self.console_msg.emit(f"A user tried to change their model to {model}! But that model could not be found in the 'Model Data' directory!", ConsoleTypes.ERROR)
            return
        model_index = self.model_list.index(model)
        if model_index == 0:
            model_index = -1
        else:
            model_index -= 1
        self.memory.write_s32(InGameVars.MODEL_INDEX + 4 + (offset*4), model_index)

    def check_if_tp(self, tp_dest: str) -> None:
        clt = ClientPointers(self.memory)

        if clt.gameState != 9 and clt.gameState != 0 and clt.gameState != 1 and clt.gameState != 5:
            if self.do_tp(tp_dest):
                self.console_msg.emit(f"TP to {tp_dest} succeeded!", ConsoleTypes.INFO)
            else:
                self.console_msg.emit(f"Could not fulfill TP request!", ConsoleTypes.ERROR)
        else:
            self.tp_timer = Timer(1.0, lambda: self.check_if_tp(tp_dest))
            self.tp_timer.start()

    def do_tp(self, tp_dest: str) -> bool:
        offset = -1
        for player in self.player_data:
            if player.connected and player.username.lower() == tp_dest.lower():
                offset = self.get_offset(self.peer_id, player.peer_id)
                break

        if offset == -1:
            return False

        dmy = DummyPointers(self.memory.read_u32(InGameVars.MARIOS + 4 + offset*4), self.memory)
        clt = ClientPointers(self.memory)
        if self.memory.read_u32(dmy.pDummyMario + 0x7C) != 0x1337:
            x = self.memory.read_f32(dmy.pDummyMario + 0x10)
            y = self.memory.read_f32(dmy.pDummyMario + 0x14)
            z = self.memory.read_f32(dmy.pDummyMario + 0x18)
            self.memory.write_f32(clt.pMario + 0x10, x)
            self.memory.write_f32(clt.pMario + 0x14, y)
            self.memory.write_f32(clt.pMario + 0x18, z)
        
        return True
    
    def check_if_reset(self) -> None:
        if self.memory.read_u8(InGameVars.RESET_FLAGS) == 0:
            self.console_msg.emit("The server has reset everyone's flags!", ConsoleTypes.INFO)
            self.pause_flags = False
        else:
            self.reset_flags_timer = Timer(1.0, lambda: self.check_if_reset())
            self.reset_flags_timer.start()





    ###########################
    #### CLIENT SEND FUNCS ####
    ###########################

    def client_send_loop(self) -> None:
        while self.running:
            for frame in range(30):
                sleep(1/30)
                if self.memory.read_u32(0x82500000) == 0:   # check if models have already been injected
                    self.inject_models()
                if self.is_connected == False:
                    break
                self.send_cli_data()
                self.handle_gamemode(frame)

    def send_cli_data(self) -> None:
        self.client_data.update_data()
        self.network.send(self.client_data.to_json())

    def handle_gamemode(self, frame: int):
        if self.gamemode == GamemodeTypes.DEFAULT.value:
            self.handle_default(frame)
        elif self.gamemode == GamemodeTypes.TAG.value:
            self.handle_tag()
        elif self.gamemode == GamemodeTypes.MANHUNT.value:
            self.handle_manhunt(frame)

    def handle_default(self, frame: int) -> None:
        if frame == 0 and not self.pause_flags and self.queued_flag_updates.empty():
            self.flag_data.update_data()
            self.network.send(self.flag_data.to_json())

    def handle_tag(self) -> None:
        # request to become tagger if mario has died
        clt = ClientPointers(self.memory)
        if self.memory.read_u8(InGameVars.TAG_ACTIVE) == 1 and self.tag_status == TagStatus.HIDER.value and clt.gameState == 7:
            self.tag_status = TagStatus.PENDING_TAGGER.value
            tag_status_data = {'dataType': ServerRcvDataTypes.TAG_STATUS.value, 'tag_status': TagStatus.TAGGER.value}
            self.network.send(json.dumps(tag_status_data))

    # COME BACK TO THIS AND STUDY THE WAY OF THE FLAGS
    def handle_manhunt(self, frame: int) -> None:
        return
        if frame == 0 and not self.pause_flags and self.queued_flag_updates.empty():
            self.flag_data.update_data()
            self.network.send(self.flag_data.to_json())

        