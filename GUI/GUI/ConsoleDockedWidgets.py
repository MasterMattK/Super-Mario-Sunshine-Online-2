from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QDockWidget, QTabWidget, QPushButton, QStackedWidget)
from PySide6.QtGui import QPalette
from PySide6.QtCore import Signal
from os import path
import sys

from GUI.ExtraWidgets import IOWidget
from Misc.DataTypes import ConfigTypes

class ClientConsole(QDockWidget):
    def __init__(self) -> None:
        super().__init__()

        self.directory = path.abspath(path.dirname(sys.argv[0]))

        self.setWindowTitle("Client Output")

        self.make_client_io_section()
        self.setWidget(self.client_console)

    def make_client_io_section(self):
        # IO Section Layout
        self.client_console = QWidget()
        self.client_console_layout = QVBoxLayout()
        self.client_console.setLayout(self.client_console_layout)

        # hook smso button
        self.hook_button = QPushButton('Hook onto SMS')

        # unhook button
        self.unhook_stack = QStackedWidget()
        self.unhook_button = QPushButton('Unhook from SMS')
        self.unhook_stack.addWidget(self.unhook_button)

        # connect and disconnect buttons
        self.connect_stack = QStackedWidget()
        self.connect_button = QPushButton('Connect')
        self.disconnect_button = QPushButton('Disconnect')
        self.connect_stack.addWidget(self.connect_button)
        self.connect_stack.addWidget(self.disconnect_button)

        # connect and unhook button layout and widget
        self.unhook_and_connect_layout = QHBoxLayout()
        self.unhook_and_connect_layout.addWidget(self.unhook_stack)
        self.unhook_and_connect_layout.addWidget(self.connect_stack)
        self.unhook_and_connect_layout.setContentsMargins(0, 0, 0, 0)
        self.unhook_and_connect_widget = QWidget()
        self.unhook_and_connect_widget.setLayout(self.unhook_and_connect_layout)

        # stacked widget for start and stop client buttons
        self.client_button_stack = QStackedWidget()
        self.client_button_stack.addWidget(self.hook_button)
        self.client_button_stack.addWidget(self.unhook_and_connect_widget)
        self.client_button_stack.setFixedHeight(50)
        self.client_console_layout.addWidget(self.client_button_stack)

        # client input and output
        self.client_io_widget = IOWidget()
        self.client_console_layout.addWidget(self.client_io_widget)

        # launch sms button for console
        self.launch_sms_button = QPushButton()
        self.client_io_widget.add_console_button(self.launch_sms_button, f"{self.directory}/Resources/shine_icon.png")

class ServerConsole(QDockWidget):
    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("Server Output")

        self.make_server_io_section()
        self.setWidget(self.server_console)

    def make_server_io_section(self) -> None:
        # IO Section Layout
        self.server_console = QWidget()
        self.server_console_layout = QVBoxLayout()
        self.server_console.setLayout(self.server_console_layout)

        # start server button
        self.start_server_button = QPushButton('Start Server')

        # stop server button
        self.stop_server_button = QPushButton('Stop Server')

        # stacked widget for start and stop buttons
        self.server_button_stack = QStackedWidget()
        self.server_button_stack.addWidget(self.start_server_button)
        self.server_button_stack.addWidget(self.stop_server_button)
        self.server_button_stack.setFixedHeight(50)
        self.server_console_layout.addWidget(self.server_button_stack)

        # server input and output
        self.server_io_widget = IOWidget()
        self.server_console_layout.addWidget(self.server_io_widget)