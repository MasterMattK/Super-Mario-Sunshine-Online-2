# this is just here for organization

import sys
if sys.platform == 'win32':
    from Client.DolphinMemoryLibWin import Dolphin
elif sys.platform == 'linux':
    from Client.DolphinMemoryLibLin import Dolphin