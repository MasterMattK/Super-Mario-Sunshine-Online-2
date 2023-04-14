from PySide6.QtCore import *

from Misc.DataTypes import ConsoleTypes, ConfigTypes, GamemodeTypes
from Misc.LevelData import LevelData
from Misc.StringChecks import is_int
from Server.Server import Server
from Client.Client import Client

class ServerCommands(QObject):
    console_msg = Signal(str, ConsoleTypes) # signal used to emit a console message on the gui
    set_config = Signal(str, str, str, ConfigTypes)

    clear_sig = Signal()
    flags_sig = Signal(bool)
    flags_reset_sig = Signal()
    change_level_sig = Signal(int, str)
    allow_tps_sig = Signal(bool)
    allow_level_changes_sig = Signal(bool)
    change_gamemode_sig = Signal(GamemodeTypes)
    kick_sig = Signal(str)
    list_players_sig = Signal()
    on_teleport_sig = Signal(str, str)
    tag_sig = Signal()

    def __init__(self) -> None:
        super().__init__()

        # the following are all of the commands. 
        # the arguments all are italisized and given < and > in html, which is why the '<i>&lt;{}&gt;</i>' is everywhere
        self.commands = {
            "/help": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Show a list of available commands",
                "requires_server": False,
                "handler": self.on_help
            },
            "/clear": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Clears the server console",
                "requires_server": False,
                "handler": self.on_clear
            },
            "/exit": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Exits from SMSO",
                "requires_server": False,
                "handler": self.on_exit
            },
            "/flags": {
                "args": "<i>&lt;{}&gt;</i>".format("on/off"),
                "min_args": 1,
                "max_args": 1,
                "description": "Toggles flag syncing on or off",
                "requires_server": False,
                "handler": self.on_flags
            },
            "/flagsreset": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Resets all users' flags",
                "requires_server": True,
                "handler": self.on_flagsreset
            },
            "/level": {
                "args": "<i>&lt;{}&gt;</i> <i>&lt;{}&gt;</i> <i>[{}]</i>".format("world", "episode", "player"),
                "min_args": 1,
                "max_args": 3,
                "description": "Loads user(s) into the specified level",
                "requires_server": True,
                "handler": self.on_change_level
            },
            "/allowtps": {
                "args": "<i>&lt;{}&gt;</i>".format("on/off"),
                "min_args": 1,
                "max_args": 1,
                "description": "Toggles client teleporting on or off",
                "requires_server": False,
                "handler": self.on_allowtps
            },
            "/allowlevels": {
                "args": "<i>&lt;{}&gt;</i>".format("on/off"),
                "min_args": 1,
                "max_args": 1,
                "description": "Toggles client leveling changing on or off",
                "requires_server": False,
                "handler": self.on_allowlevels
            },
            "/gamemode": {
                "args": "<i>&lt;{}&gt;</i>".format("mode"),
                "min_args": 1,
                "max_args": 1,
                "description": "Changes the custom gamemode",
                "requires_server": True,
                "handler": self.change_gamemode
            },
            "/kick": {
                "args": "<i>&lt;{}&gt;</i>".format("user"),
                "min_args": 1,
                "max_args": 1,
                "description": "Kicks the specified user from the server",
                "requires_server": True,
                "handler": self.on_kick
            },
            "/kickall": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Kicks all users from the server",
                "requires_server": True,
                "handler": self.on_kickall
            },
            "/players": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Lists all connected players",
                "requires_server": True,
                "handler": self.list_players
            },
            "/about": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Links the Discord and other info",
                "requires_server": False,
                "handler": self.on_about
            },
            "/tp": {
                "args": "<i>&lt;{}&gt;</i> <i>&lt;{}&gt;</i>".format("teleported user", "destination user"),
                "min_args": 2,
                "max_args": 2,
                "description": "Teleports one user to another",
                "requires_server": True,
                "handler": self.on_teleport
            },
            "/tag": {
                "args": "<i>&lt;{}&gt;</i>".format("setting"),
                "min_args": 1,
                "max_args": 3,
                "description": "Changes the specified Tag/Hide n' Seek setting. Type '/tag help' for more info.",
                "requires_server": True,
                "handler": self.on_tag
            }
        }

        self.tag_commands = TagCommands()
        self.tag_commands.console_msg.connect(lambda msg, type: self.console_msg.emit(msg, type))
        self.tag_commands.set_config.connect(lambda section, option, value, type: self.set_config.emit(section, option, value, type))


    # handles the command input from the user
    def handle_command(self, command: str, server: Server) -> None:
        parts = command.split()
        if len(parts) == 0:
            return
        name = parts[0]
        args = parts[1:]
        for command_name, command in self.commands.items():
            if name == command_name:
                if len(args) >= command['min_args'] and len(args) <= command['max_args']:
                    if command['requires_server'] and not server:
                        self.console_msg.emit("You have not started the server! Please start the server first!", ConsoleTypes.ERROR)
                    else:
                        command["handler"](*args)
                    break
                else:
                    if command['min_args'] == command['max_args']:
                        arg_str = command['min_args']
                    else:
                        arg_str = f"{command['min_args']}-{command['max_args']}"
                    self.console_msg.emit(f"{command_name} requires {arg_str} arguments, but you provided {len(args)}! Do /help for a list of available commands.", 
                        ConsoleTypes.ERROR)
                    break  
        else:
            self.console_msg.emit(f"{name} is not a recognized command! Do /help for a list of available commands.", ConsoleTypes.ERROR)

    def on_help(self) -> None:      ### NOTE: specify the difference between <> and [] for command args ###
        cmd_help = ""
        for command_name, command in self.commands.items():
            cmd_help += f"\n>> <b>{command_name} {command['args']}</b>: {command['description']}"
            
        self.console_msg.emit(cmd_help, ConsoleTypes.INFO)

    def on_clear(self) -> None:
        self.clear_sig.emit()

    def on_exit(self) -> None:
        self.console_msg.emit("Just click the X button :)", ConsoleTypes.INFO)

    def on_flags(self, toggle: str) -> None:
        if toggle.lower() == 'on':
            self.flags_sig.emit(True)
            self.console_msg.emit("Flags syncing has been turned on!", ConsoleTypes.INFO)
            self.set_config.emit("SERVER", "sync_flags", "True", ConfigTypes.BOOL)
        elif toggle.lower() == 'off':
            self.flags_sig.emit(False)
            self.console_msg.emit("Flags syncing has been turned off!", ConsoleTypes.INFO)
            self.set_config.emit("SERVER", "sync_flags", "False", ConfigTypes.BOOL)
        else:
            self.console_msg.emit(f"/flags requires an argument of 'on' or 'off'! You provided '{toggle}'!", ConsoleTypes.ERROR)

    def on_flagsreset(self) -> None:
        self.flags_reset_sig.emit()
        self.console_msg.emit("Flags for all clients have been reset!", ConsoleTypes.INFO)

    def on_change_level(self, world: str, episode: str="", player: str="") -> None:
        level_input = f"{world} {episode}".strip()
        level_data = LevelData()

        lvl_id = level_data.get_lvl_id(level_input)

        if lvl_id == -1:
            self.console_msg.emit(f"{level_input} is not a valid level name!", ConsoleTypes.ERROR)
            return

        if player == "":
            self.change_level_sig.emit(lvl_id, "all")
        else:
            self.change_level_sig.emit(lvl_id, player)

    def on_allowtps(self, toggle: str) -> None:
        if toggle.lower() == 'on':
            self.allow_tps_sig.emit(True)
            self.console_msg.emit("Teleporting for all clients has been turned on!", ConsoleTypes.INFO)
        elif toggle.lower() == 'off':
            self.allow_tps_sig.emit(False)
            self.console_msg.emit("Teleporting for all clients has been turned off!", ConsoleTypes.INFO)
        else:
            self.console_msg.emit(f"/allowtp requires an argument of 'on' or 'off'! You provided '{toggle}'!", ConsoleTypes.ERROR)

    def on_allowlevels(self, toggle: str) -> None:
        if toggle.lower() == 'on':
            self.allow_level_changes_sig.emit(True)
            self.console_msg.emit("Level changing for all clients has been turned on!", ConsoleTypes.INFO)
        elif toggle.lower() == 'off':
            self.allow_level_changes_sig.emit(False)
            self.console_msg.emit("Level changing for all clients has been turned off!", ConsoleTypes.INFO)
        else:
            self.console_msg.emit(f"/allowlevel requires an argument of 'on' or 'off'! You provided '{toggle}'!", ConsoleTypes.ERROR)

    def change_gamemode(self, mode: str) -> None:
        if is_int(mode):
            self.change_gamemode_sig.emit(GamemodeTypes.get_gamemode_from_num(int(mode)))
        else:
            self.console_msg.emit(f"The gamemode type needs to be an integer!", ConsoleTypes.ERROR)

    def on_kick(self, user: str) -> None:
        self.kick_sig.emit(user)

    def on_kickall(self) -> None:
        self.kick_sig.emit("all")

    def list_players(self) -> None:
        self.list_players_sig.emit()

    def on_about(self) -> None:
        self.console_msg.emit("Official SMSO Discord: https://discord.gg/aYHKKDhtuv. Stop by for credits, updates, news, and more!", ConsoleTypes.INFO)

    def on_teleport(self, tp_user: str, tp_dest: str) -> None:
        self.on_teleport_sig.emit(tp_user, tp_dest)
    
    def on_tag(self, tag_option: str, user: str="") -> None:
        for tag_command_name, tag_command in self.tag_commands.commands.items():
            if tag_option == tag_command_name:
                if user:
                    if tag_command['arg_num'] == 1:
                        tag_command["handler"](user)
                    else:
                        self.console_msg.emit(f"/tag {tag_command_name} requires 0 arguments, but you provided 1! Do /tag help for a list of available commands.", ConsoleTypes.ERROR)
                    break
                elif not user:
                    if tag_command['arg_num'] == 0:
                        tag_command["handler"]()
                    else:
                        self.console_msg.emit(f"/tag {tag_command_name} requires 1 argument, but you provided 0! Do /tag help for a list of available commands.", ConsoleTypes.ERROR)
                    break
        else:
            self.console_msg.emit(f"{tag_option} is not a recognized tag command! Do /tag help for a list of available commands.", ConsoleTypes.ERROR)

class TagCommands(QObject):
    console_msg = Signal(str, ConsoleTypes)
    set_config = Signal(str, str, str, ConfigTypes)

    add_sig = Signal(str)
    remove_sig = Signal(str)
    start_sig = Signal()
    stop_sig = Signal()
    reset_sig = Signal()
    refills_sig = Signal(bool)

    def __init__(self) -> None:
        super().__init__()

        self.commands = {
            "help": {
                "args": "",
                "arg_num": 0,
                "description": "Show a list of available tag commands",
                "handler": self.on_help
            },
            "add": {
                "args": "<i>&lt;{}&gt;</i>".format("user"),
                "arg_num": 1,
                "description": "Add a user to the tag team",
                "handler": self.on_add
            },
            "remove": {
                "args": "<i>&lt;{}&gt;</i>".format("user"),
                "arg_num": 1,
                "description": "Remove a user to the tag team",
                "handler": self.on_remove
            },
            "start": {
                "args": "",
                "arg_num": 0,
                "description": "Start a game of tag",
                "handler": self.on_start
            },
            "stop": {
                "args": "",
                "arg_num": 0,
                "description": "Stop a game of tag",
                "handler": self.on_stop
            },
            "reset": {
                "args": "",
                "arg_num": 0,
                "description": "Resets a game of tag (including everyone's timers)",
                "handler": self.on_reset
            },
            "refills": {
                "args": "<i>&lt;{}&gt;</i>".format("on/off"),
                "arg_num": 1,
                "description": "Toggle FLUDD refills on or off for hiders",
                "handler": self.on_refills
            }
        }

    def on_help(self):
        cmd_help = ""
        for command_name, command in self.commands.items():
            cmd_help += f"\n>> <b>/tag {command_name} {command['args']}</b>: {command['description']}"
            
        self.console_msg.emit(cmd_help, ConsoleTypes.INFO)

    def on_add(self, user: str):
        self.add_sig.emit(user)
    
    def on_remove(self, user: str):
        self.remove_sig.emit(user)
    
    def on_start(self):
        self.start_sig.emit()
    
    def on_stop(self):
        self.stop_sig.emit()
    
    def on_reset(self):
        self.reset_sig.emit()
    
    def on_refills(self, toggle: str):
        if toggle.lower() == 'on':
            self.refills_sig.emit(False)
            self.console_msg.emit("FLUDD refills for hiders have been enabled!", ConsoleTypes.INFO)
            self.set_config.emit("SERVER", "disable_refills", "False", ConfigTypes.BOOL)
        elif toggle.lower() == 'off':
            self.refills_sig.emit(True)
            self.console_msg.emit("FLUDD refills for hiders have been disable!", ConsoleTypes.INFO)
            self.set_config.emit("SERVER", "disable_refills", "True", ConfigTypes.BOOL)
        else:
            self.console_msg.emit(f"/tag refills requires an argument of 'on' or 'off'! You provided '{toggle}'!", ConsoleTypes.ERROR)

class ClientCommands(QObject):
    console_msg = Signal(str, ConsoleTypes) # signal used to emit a console message on the gui

    clear_sig = Signal()
    change_level_sig = Signal(int)
    list_players_sig = Signal()
    on_teleport_sig = Signal(str)
    hm = Signal(str)

    def __init__(self):
        super().__init__()

        # the following are all of the commands. 
        # the arguments all are italisized and given < and > in html, which is why the '<i>&lt;{}&gt;</i>' is everywhere
        self.commands = {
            "/help": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Show a list of available commands",
                "requires_client": False,
                "handler": self.on_help
            },
            "/clear": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Clears the client console",
                "requires_client": False,
                "handler": self.on_clear
            },
            "/exit": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Exits from SMSO",
                "requires_client": False,
                "handler": self.on_exit
            },
            "/level": {
                "args": "<i>&lt;{}&gt;</i> <i>&lt;{}&gt;</i>".format("world", "episode"),
                "min_args": 1,
                "max_args": 2,
                "description": "Loads you into the specified level",
                "requires_client": True,
                "handler": self.on_change_level
            },
            "/players": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Lists all connected players",
                "requires_client": True,
                "handler": self.list_players
            },
            "/about": {
                "args": "",
                "min_args": 0,
                "max_args": 0,
                "description": "Links the Discord and other info",
                "requires_client": False,
                "handler": self.on_about
            },
            "/tp": {
                "args": "<i>&lt;{}&gt;</i>".format("destination user"),
                "min_args": 1,
                "max_args": 1,
                "description": "Teleports you to another user",
                "requires_client": True,
                "handler": self.on_teleport
            },
            "/hm": {
                "args": "<i>&lt;{}&gt;</i>".format("?"),
                "min_args": 1,
                "max_args": 1,
                "description": "???",
                "requires_client": True,
                "handler": self.on_hm
            }
        }

    # handles the command input from the user
    def handle_command(self, command: str, client: Client) -> None:
        parts = command.split()
        if len(parts) == 0:
            return
        name = parts[0]
        args = parts[1:]
        for command_name, command in self.commands.items():
            if name == command_name:
                if len(args) >= command['min_args'] and len(args) <= command['max_args']:
                    if command['requires_client'] and not client:
                        self.console_msg.emit(f"You have not started the client! Please start the client first!", ConsoleTypes.ERROR)
                    else:
                        command["handler"](*args)
                    break
                else:
                    if command['min_args'] == command['max_args']:
                        arg_str = command['min_args']
                    else:
                        arg_str = f"{command['min_args']}-{command['max_args']}"
                    self.console_msg.emit(f"{command_name} requires {arg_str} arguments, but you provided {len(args)}! Do /help for a list of available commands.", 
                        ConsoleTypes.ERROR)
                    break  
        else:
            self.console_msg.emit(f"{name} is not a recognized command! Do /help for a list of available commands.", ConsoleTypes.ERROR)

    def on_help(self) -> None:      ### NOTE: specify the difference between <> and [] for command args ###
        cmd_help = ""
        for command_name, command in self.commands.items():
            cmd_help += f"\n>> <b>{command_name} {command['args']}</b>: {command['description']}"
            
        self.console_msg.emit(cmd_help, ConsoleTypes.INFO)

    def on_clear(self) -> None:
        self.clear_sig.emit()

    def on_exit(self) -> None:
        self.console_msg.emit("Just click the X button :)", ConsoleTypes.INFO)

    def on_change_level(self, world: str, episode: str="") -> None:
        level_input = f"{world} {episode}".strip()
        level_data = LevelData()

        lvl_id = level_data.get_lvl_id(level_input)

        if lvl_id == -1:
            self.console_msg.emit(f"{level_input} is not a valid level name!", ConsoleTypes.ERROR)
            return

        self.change_level_sig.emit(lvl_id)

    def list_players(self) -> None:
        self.list_players_sig.emit()

    def on_about(self) -> None:
        self.console_msg.emit("Official SMSO Discord: https://discord.gg/aYHKKDhtuv. Stop by for credits, updates, news, and more!", ConsoleTypes.INFO)

    def on_teleport(self, tp_dest: str) -> None:
        self.on_teleport_sig.emit(tp_dest)

    def on_hm(self, model: str) -> None:
        self.hm.emit(model)


if __name__ == '__main__':
    cmd = ServerCommands()
    while True:
        cmd_input = input("Type /help\n")
        cmd.handle_command(cmd_input)