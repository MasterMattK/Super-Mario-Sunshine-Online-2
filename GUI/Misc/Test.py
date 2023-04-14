import sys
from PySide6 import QtWidgets, QtCore

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()

        # Create two QListWidget instances for the Taggers and Hiders
        self.taggers_list = QtWidgets.QListWidget()
        self.hiders_list = QtWidgets.QListWidget()

        # Create a layout for the two QListWidgets
        layout = QtWidgets.QHBoxLayout()
        layout.addWidget(self.taggers_list)
        layout.addWidget(self.hiders_list)

        # Create a central widget and set the layout
        central_widget = QtWidgets.QWidget()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

        # Add the players to the Taggers list
        self.taggers_list.addItems(["Player 1", "Player 2", "Player 3", "Player 4"])

        # Enable drag and drop for both QListWidgets
        self.taggers_list.setDragEnabled(True)
        self.hiders_list.setDragEnabled(True)
        self.taggers_list.setAcceptDrops(True)
        self.hiders_list.setAcceptDrops(True)
        self.taggers_list.setDropIndicatorShown(True)
        self.hiders_list.setDropIndicatorShown(True)
        self.taggers_list.setDefaultDropAction(QtCore.Qt.MoveAction)
        self.hiders_list.setDefaultDropAction(QtCore.Qt.MoveAction)

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
