# Super-Mario-Sunshine-Online-2
This is a repository that contains the python-based GUI and sunshine c-kit source code for the Super Mario Sunshine Online 2 Project

**Here's how you can compile the c-kit source code:**
  1. Install [devKitPPC](https://github.com/devkitPro/installer/releases). 
  2. Add a vanilla SMS main.dol (USA version) into the compiler folder. If you don't know how to get this, here's a quick overview:
        1. Obtain a USA SMS iso or other disc image type (I can't help you with how to obtain this, but you probably already have one if you're following this tutorial).
        3. Open Dolphin Emulator (which I assume you already have, but [install it](https://dolphin-emu.org/download/) if you don't) and go to Config->Paths
        4. Add the path to the folder that your USA SMS iso is in if you haven't already
        5. Go back to the main Dolphin screen, and now you should be able to see Super Mario Sunshine listed. Right click it and go to Properties->Filesystem.
        6. Right click on Disc and click Extract Entire Disc.
        7. Once this is done, open the folder you extracted it into, and then open the sys folder, and main.dol should be in there.
  3. Create a txt file called 'dol_path.txt' in the CKit/compiler folder. Put the file path of wherever you want the output main.dol to be. Don't include quotes. (For example, something like C:\SMSO_DOL\main.dol)
  4. Change the paths at the top of devkit_tools.py to reflect wherever you installed devKitPPC.
  5. Run buildmain.bat, and it should output a dol to whatever path you specified.

Credit to RenolY2 for [the python-based c-kit](https://github.com/RenolY2/gc-c-kit) which I've slightly modified for this project.

**Here's how you can run and build the python GUI code:**
  1. If you haven't installed python, install it. This was developed with 3.8.10, but other versions probably work too.
  2. Install the following modules with pip (i.e. 'pip install _module_'): PySide6, bitarray, PyEnet, psutil, and PyQtDarkTheme. 
  3. If you don't want to build an exe from the python code, you can directly run the program by running main.py.
  4. To actually build an exe, you will also need to get cx_Freeze using pip. 
  5. You can then use the following command in the folder with setup.py: 'python setup.py build'. This should build into a build folder, and all necessary resources should be provided
