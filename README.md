# Super-Mario-Sunshine-Online-2.1
This is a repository that contains the python-based GUI and sunshine c-kit source code for the Super Mario Sunshine Online 2.X Project

**Here's how you can compile the c-kit source code:**
  1. Install [devKitPPC](https://github.com/devkitPro/installer/releases). 
  2. Change the path at the very bottom of mainproject.py (the line with p.build). Set this to wherever you want the output main.dol to be. 
  3. Change the paths at the top of devkit_tools.py to reflect wherever you installed devKitPPC. 
  4. Change the paths at the top of replace_var.py. mapDir is the path to the project.map file which will be created in the compiler folder once you compile the code.  scriptDir is a path to InGameVars.py, which is part of the GUI. This is necessary because it gives the GUI the addresses of variables from the c-kit so that it can interface with the game. 
  5. Run buildmain.bat, and it should output a dol to whatever path you specified.

Credit to RenolY2 for [the python-based c-kit](https://github.com/RenolY2/gc-c-kit) which I've slightly modified for this project.

**Here's how you can run and build the python GUI code:**
  1. If you haven't installed python, install it. This was developed with 3.8.10, but other versions probably work too.
  2. Install the following modules with pip (i.e. 'pip install _module_'): PySide6, bitarray, PyEnet, psutil, and PyQtDarkTheme. 
  3. If you don't want to build an exe from the python code, you can directly run the program by running main.py.
  4. To actually build an exe, you will also need to get cx_Freeze using pip. 
  5. You can then use the following command in the folder with setup.py: 'python setup.py build'. This should build into a build folder, and all necessary resources should be provided
