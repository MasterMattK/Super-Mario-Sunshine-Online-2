from PySide6.QtWidgets import QApplication
import sys
import logging
import os

from GUI.GUI import MainWindow
from Misc.ErrorHandling import ErrorHandling

# this function creates an excepthook so that we can log exceptions and create popups when one occurs.
# we also want to eventually give the option to report these exceptions to a google form when they occur
def setup_excepthook() -> None:
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
    sys.excepthook = ErrorHandling.log_exception

# main function which creates Qt application and window and starts the event loop
def main() -> None:
    setup_excepthook()

    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()