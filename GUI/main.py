from PySide6.QtWidgets import QApplication
import sys
import logging
import os

from GUI.GUI import MainWindow

def log_exception(exctype, value, traceback):
    logging.exception("Uncaught exception", exc_info=(exctype, value, traceback))

def main() -> None:
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

# get the directory path of the script being executed
script_dir = os.path.abspath(os.path.dirname(sys.argv[0]))
log_file_path = os.path.join(script_dir, "exceptions.log")

# create a custom formatter that includes a timestamp
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')

# create a file handler and set the formatter
file_handler = logging.FileHandler(log_file_path)
file_handler.setFormatter(formatter)

# add the file handler to the logger
logger = logging.getLogger()
logger.addHandler(file_handler)

# set the global exception handler
sys.excepthook = log_exception

if __name__ == '__main__':
    main()