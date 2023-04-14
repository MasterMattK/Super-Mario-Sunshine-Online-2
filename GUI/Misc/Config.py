from PySide6.QtCore import QObject, Signal
from os import path, getenv, makedirs
from Misc.StringChecks import is_bool, is_int, is_ip_address, is_path
from Misc.DataTypes import ConfigTypes
import configparser
import sys
import re

class Config(QObject):
    config_updated = Signal(str, str)

    def __init__(self) -> None:
        super().__init__()

        self.directory = path.abspath(path.dirname(sys.argv[0]))

        self.config = configparser.ConfigParser()
        self.config.read(f'{self.directory}/config.ini')

        if 'CLIENT' not in self.config:
            self.config['CLIENT'] = {}
        if 'username' not in self.config['CLIENT'] or self.config['CLIENT']['username'] == '':
            self.config['CLIENT']['username'] = 'User'
        if 'client_ip' not in self.config['CLIENT'] or not is_ip_address(self.config['CLIENT']['client_ip']):
            self.config['CLIENT']['client_ip'] = '127.0.0.1'
        if 'client_port' not in self.config['CLIENT'] or not is_int(self.config['CLIENT']['client_port'], 0, 65535):
            self.config['CLIENT']['client_port'] = '8234'
        if 'model' not in self.config['CLIENT']:
            self.config['CLIENT']['model'] = 'mario'
        if 'music_volume' not in self.config['CLIENT'] or not is_int(self.config['CLIENT']['music_volume'], 0, 150):
            self.config['CLIENT']['music_volume'] = '75'
        if 'dolphin_path' not in self.config['CLIENT'] or not is_path(self.config['CLIENT']['dolphin_path']): # these paths should be checked even further
            self.config['CLIENT']['dolphin_path'] = ''
        if 'sms_path' not in self.config['CLIENT'] or not is_path(self.config['CLIENT']['sms_path']):
            self.config['CLIENT']['sms_path'] = ''
        if 'user_path' not in self.config['CLIENT'] or not is_path(self.config['CLIENT']['user_path']):
            self.config['CLIENT']['user_path'] = ''

        if 'SERVER' not in self.config:
            self.config['SERVER'] = {}
        if 'server_ip' not in self.config['SERVER'] or not is_ip_address(self.config['SERVER']['server_ip']):
            self.config['SERVER']['server_ip'] = '127.0.0.1'
        if 'server_port' not in self.config['SERVER'] or not is_int(self.config['SERVER']['server_port'], 0, 65535):
            self.config['SERVER']['server_port'] = '8234'
        if 'sync_flags' not in self.config['SERVER'] or not is_bool(self.config['SERVER']['sync_flags']):
            self.config['SERVER']['sync_flags'] = 'True'
        if 'disable_refills' not in self.config['SERVER'] or not is_bool(self.config['SERVER']['disable_refills']):
            self.config['SERVER']['disable_refills'] = 'True'

        if 'GENERAL' not in self.config:
            self.config['GENERAL'] = {}
        if 'dark_mode' not in self.config['GENERAL'] or not is_bool(self.config['GENERAL']['dark_mode']):
            self.config['GENERAL']['dark_mode'] = 'True'
        if 'launch_with_dolphin' not in self.config['GENERAL'] or not is_bool(self.config['GENERAL']['launch_with_dolphin']):
            self.config['GENERAL']['launch_with_dolphin'] = 'True'

        with open(f'{self.directory}/config.ini', 'w') as configfile:
            configfile.write('; DO NOT MANUALLY EDIT THIS FILE! EVERY OPTION SHOULD BE EDITED FROM THE GUI!\n')
            self.config.write(configfile)
        
        self.username = self.config['CLIENT']['username'][:30]
        self.client_ip = self.config['CLIENT']['client_ip']
        self.client_port = self.config['CLIENT'].getint('client_port')
        self.model = self.config['CLIENT']['model']
        self.music_volume = self.config['CLIENT'].getint('music_volume')
        self.dolphin_path = self.config['CLIENT']['dolphin_path']
        self.sms_path = self.config['CLIENT']['sms_path']
        self.user_path = self.config['CLIENT']['user_path']

        self.server_ip = self.config['SERVER']['server_ip']
        self.server_port = self.config['SERVER'].getint('server_port')
        self.sync_flags = self.config['SERVER'].getboolean('sync_flags')
        self.disable_refills = self.config['SERVER'].getboolean('disable_refills')

        self.dark_mode = self.config['GENERAL'].getboolean('dark_mode')
        self.launch_with_dolphin = self.config['GENERAL'].getboolean('launch_with_dolphin')

    # the values are always sent in as a string so that it's easy to use signals
    def set_value(self, section: str, option: str, value: str, type: ConfigTypes) -> None:
        if not self.config.has_option(section, option):
            return
        
        if type == ConfigTypes.INT:
            if not is_int(value):
                raise TypeError("You specified a type of integer but no integer value was given")
            value = int(value)
        elif type == ConfigTypes.BOOL:
            if not is_bool(value):
                raise TypeError("You specified a type of boolean but no boolean value was given")
            elif value == 'True':
                value = True
            elif value == 'False':
                value = False

        setattr(self, option, value)
        self.config[section][option] = str(value)
        self.config_updated.emit(option, str(value))
        with open(f'{self.directory}/config.ini', 'w') as configfile:
            configfile.write('; DO NOT MANUALLY EDIT THIS FILE! EVERY OPTION SHOULD BE EDITED FROM THE GUI!\n')
            self.config.write(configfile)

    # this function searches for the user path and makes sure that memory is expanded for SMSO.
    # this function should really only return false if the user has never ran dolphin and therefore doesn't have a user path yet
    def verify_game_config(self) -> bool:
        # Go to https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/UICommon/UICommon.cpp for where I got the info for how
        # to get user paths on each platform. It's in the SetUserDirectory() function.

        home_path = path.expanduser("~")    # this should work on all platforms

        if sys.platform == 'win32':
            import winreg
            local = ""
            config_path = ""

            try:
                key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, "Software\\Dolphin Emulator")
            except:
                key = None
            if key:
                try:
                    local, _ = winreg.QueryValueEx(key, "LocalUserConfig")
                except:
                    local = ""
                try:
                    config_path, _ = winreg.QueryValueEx(key, "UserConfigPath")
                except:
                    config_path = ""
                winreg.CloseKey(key)

            if (local) or (self.dolphin_path != "" and path.exists(path.join(path.dirname(self.dolphin_path), "portable.txt"))): 
                if path.exists(path.join(path.dirname(self.dolphin_path), "User")):
                    user_path = path.join(path.dirname(self.dolphin_path), "User")
                else:
                    return False    # if they have portable.txt but not User, they need to run Dolphin first
            elif config_path:
                user_path = config_path
            elif path.exists(path.join(home_path, "Documents\\Dolphin Emulator")):
                user_path = path.join(home_path, "Documents\\Dolphin Emulator")
            elif path.exists(path.join(home_path, "AppData\\Roaming\\Dolphin Emulator")):
                user_path = path.join(home_path, "AppData\\Roaming\\Dolphin Emulator")
            else:
                return False

        elif sys.platform == 'linux':
            data_home = getenv("XDG_DATA_HOME")

            if self.dolphin_path != "" and path.exists(path.join(path.dirname(self.dolphin_path), "portable.txt")): 
                if path.exists(path.join(path.dirname(self.dolphin_path), "User")):
                    user_path = path.join(path.dirname(self.dolphin_path), "User")
                else:
                    return False    # if they have portable.txt but not User, they need to run Dolphin first
            elif path.exists(path.join(home_path, ".dolphin-emu")):
                user_path = path.join(home_path, ".dolphin-emu")
            elif data_home and data_home.startswith("/"):
                user_path = data_home
            elif path.exists(path.join(home_path, ".local/share/dolphin-emu")):
                user_path = path.join(home_path, ".local/share/dolphin-emu")
            else:
                return False

        # after getting the user path, everything should be the same on all platforms
        game_config_path = path.join(user_path, "GameSettings/GMSE10.ini")
        if path.exists(game_config_path):
            with open(game_config_path, "r") as file:
                config_str = file.read()
            if "[Core]" in config_str:
                pattern = re.compile(r'RAMOverrideEnable\s*=\s*.*')
                match = pattern.search(config_str)
                if match:
                    config_str = config_str.replace(match.group(), "RAMOverrideEnable = True")
                else:
                    config_str = config_str.replace("[Core]", "[Core]\nRAMOverrideEnable = True")
                pattern = re.compile(r'MEM1Size\s*=\s*.*')
                match = pattern.search(config_str)
                if match:
                    config_str = config_str.replace(match.group(), "MEM1Size = 0x03000000")
                else:
                    config_str = config_str.replace("RAMOverrideEnable = True", "RAMOverrideEnable = True\nMEM1Size = 0x03000000")
            else:
                config_str += "\n[Core]\nRAMOverrideEnable = True\nMEM1Size = 0x03000000"
            with open(game_config_path, "w") as file:
                file.write(config_str)
        elif path.exists(path.join(user_path, "GameSettings")):
            with open(game_config_path, "w") as file:
                file.write("[Core]\nRAMOverrideEnable = True\nMEM1Size = 0x03000000")
        else:
            makedirs(path.join(user_path, "GameSettings"))
            with open(game_config_path, "w") as file:
                file.write("[Core]\nRAMOverrideEnable = True\nMEM1Size = 0x03000000")
        
        self.set_value('CLIENT', 'user_path', user_path, ConfigTypes.STR)
        return True
