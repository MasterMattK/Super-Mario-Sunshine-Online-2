from PySide6.QtWidgets import QApplication
import sys

from GUI.GUI import MainWindow

# main function which creates Qt application and window and starts the event loop
def main() -> None:
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    main()