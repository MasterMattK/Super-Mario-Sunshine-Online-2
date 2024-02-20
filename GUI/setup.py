from cx_Freeze import setup, Executable
import sys

base = None
icon = None
if sys.platform == "win32":
    base = "Win32GUI"
    icon="Resources/smso.ico"

main_exe = Executable(
    script="main.py",
    base=base,
    icon=icon,
    target_name="SMSO"
)

updater_exe = Executable(
    script="Updater/Updater.py",
    base=base,
    icon=icon,
    target_name="Updater"
)

options = {
    "build_exe": {
        "excludes": [],
        "include_files": ["Resources", "Model Data", "LICENSE"]
    }
}

setup (
    name="SMSO",
    version="2.2",
    description="Super Mario Sunshine Online",
    options=options,
    executables=[main_exe]
)
