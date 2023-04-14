from enum import Enum
from bitarray import bitarray

# specifies the type of data sent to the client
class ClientRcvDataTypes(Enum):
    SELF_CONNECT = 0        # client receives info from svr after it connects
    CONNECT = 1             # a different client connects to the server
    CLI_DATA = 2            # data from another client
    FLG_DATA = 3            # data from server to update flag data
    CHAT_MSG = 4            # chat message from another client
    USERNAME = 5            # server updates the user's username in case of conflict
    MODEL = 6               # model data from another client
    CHANGE_LEVEL = 7        # server requests level change
    TAG_STATUS = 8          # server requests tag status change
    DISCONNECT = 9          # another client has disconnected from the server
    TP = 10                 # when a client needs to teleport to another user
    TP_INFO_REQUEST = 11    # when the server requests level info from a client for teleportation
    GAMEMODE_CHANGE = 12    # when the server updates the gamemode
    START_TAG = 13          # when the server sets starts the actual tag gamemode
    PAUSE_FLAGS = 14        # when the server is about to reset flag data, it will tell the clients to stop sending flag data
    RESET_FLAGS = 15        # when the server needs to reset a clients flags
    RESET_TAG = 16          # when the server needs to reset a clients tag timer
    TOGGLE_REFILLS = 17     # when the server toggles tag refills for hiders
    ALLOW_TPS = 18          # when the server enables or disables tps for clients
    ALLOW_LVL_CHANGES = 19  # when the server enables or disables level changes for clients

# specifies the type of data sent to the server
class ServerRcvDataTypes(Enum):
    CONNECT = 0         # a client connects to the server
    CLI_DATA = 1        # data from a client
    FLG_DATA = 2        # flag data from a client
    MODEL = 3           # model data from a client
    USERNAME = 4
    CHAT_MSG = 5        # chat message from a client
    TP_INFO = 6         # client sends teleportation info to the server
    TP_REQUEST = 7      # a client requests to be teleported to another client
    CHANGE_LEVEL = 8    # a client notifies the server it changed level
    TAG_STATUS = 9      # a client requests a tag status change
    FLAGS_PAUSED = 10   # a client confirms that it has paused flags

# this is used to distinguish between the different forms of disconnection
class DisconnectSource(Enum):
    DEFAULT = 0
    CLT_END = 1
    SVR_END = 2
    SVR_KICK = 3
    VERSION = 4

# each of these are types of console messages that can be displayed and their colors.
class ConsoleTypes(Enum):
    STARTING = {"prefix": "[STARTING]", "light_mode_color": "#008000", "dark_mode_color": "#3cb371"}        # green, medium sea green
    EXITING = {"prefix": "[EXITING]", "light_mode_color": "#ff0000", "dark_mode_color": "#ff0000"}          # red, red
    SETTINGS = {"prefix": "[SETTINGS]", "light_mode_color": "#808080", "dark_mode_color": "#808080"}        # gray, gray
    INFO = {"prefix": "[INFO]", "light_mode_color": "#0000ff", "dark_mode_color": "#5555ff"}                # blue, lighter blue
    CONNECT = {"prefix": "[CONNECT]", "light_mode_color": "#329d32", "dark_mode_color": "#32cd32"}          # darker lime green, lime green
    DISCONNECT = {"prefix": "[DISCONNECT]", "light_mode_color": "#ff0000", "dark_mode_color": "#ff0000"}    # red, red
    WARNING = {"prefix": "[WARNING]", "light_mode_color": "#daa520", "dark_mode_color": "#ffd700"}          # golden rod, gold
    ERROR = {"prefix": "[ERROR]", "light_mode_color": "#dc143c", "dark_mode_color": "#dc143c"}              # crimson, crimson
    DEFAULT = {"prefix": "", "light_mode_color": "#000000", "dark_mode_color": "#ffffff"}                   # black, white

    @staticmethod
    def get_corresponding_color(color: str, dark_mode: bool) -> None:
        for type in list(ConsoleTypes):
            if dark_mode and type.value['light_mode_color'] == color:
                return type.value['dark_mode_color']
            elif not dark_mode and type.value['dark_mode_color'] == color:
                return type.value['light_mode_color']

        return color

class GamemodeTypes(Enum):
    DEFAULT = 0
    TAG = 1

    @staticmethod
    def get_gamemode_from_num(num: int):
        for gamemode in list(GamemodeTypes):
            if gamemode.value == num:
                return gamemode

        return GamemodeTypes.DEFAULT

class TagStatus(Enum):
    HIDER = 0
    PENDING_TAGGER = 1
    TAGGER = 2
    SPECTATOR = 3

class ConfigTypes(Enum):
    STR = 0
    INT = 1
    BOOL = 2

class PopUpBoxTypes(Enum):
    ERROR = 0
    CONFIRM = 1
    INFO = 2