from cx_Freeze import setup, Executable
import sys

base = None
if sys.platform == "win32":
    base = "Win32GUI"

exe = Executable(
    script="main.py",
    base=base,
    icon="Resources/smso.ico",
    target_name="SMSO.exe"
)

options = {
    "build_exe": {
        "excludes": ["tkinter", "pygame", "pandas", "matplotlib"],
        "include_files": ["Resources", "Model Data", "LICENSE"],
    }
}

setup (
    name="SMSO",
    version="2.1",
    description="Super Mario Sunshine Online",
    options=options,
    executables=[exe]
)
