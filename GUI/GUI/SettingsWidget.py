from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QGridLayout, QScrollArea, QLabel, QLineEdit,   
    QPushButton, QSizePolicy, QCheckBox, QComboBox, QSlider, QFileDialog)
from PySide6.QtGui import QPalette, QFont, QIntValidator, QRegularExpressionValidator
from PySide6.QtCore import Signal, Qt

from GUI.ExtraWidgets import CollapsibleGroupBox, PasswordComboBox, PopUpBox
from Misc.StringChecks import is_ip_address
from Misc.DataTypes import ConfigTypes, PopUpBoxTypes
import os, sys

class SettingsTab(QScrollArea):
    set_config = Signal(str, str, str, ConfigTypes)
    update_username = Signal(str)
    launch_path_changed = Signal()

    def __init__(self) -> None:
        super().__init__()
        self.setWidgetResizable(True)
        self.setBackgroundRole(QPalette.AlternateBase)

        # General Layout
        self.settings_layout = QVBoxLayout() 
        self.settings_layout.setAlignment(Qt.AlignTop)   # this is so that the widgets always push to the top
        self.main_widget = QWidget()
        self.main_widget.setLayout(self.settings_layout)
        self.setWidget(self.main_widget)

        # Make sections
        self.make_client_settings_section()
        self.make_server_settings_section()
        self.make_game_setup_section()

        # add the widgets to the layout
        self.settings_layout.addWidget(self.client_settings_section)
        self.settings_layout.addWidget(self.server_settings_section)
        self.settings_layout.addWidget(self.game_setup_section)
        self.settings_layout.setSpacing(10)

    def make_client_settings_section(self):
        # Settings Layout
        self.client_settings_section = CollapsibleGroupBox("Client Settings")
        self.client_settings_layout = QGridLayout()
        self.client_settings_layout.setColumnStretch(1, 5) # make it so column 1 fills the gaps
        self.client_settings_section.setLayout(self.client_settings_layout)

        # username
        self.username_label = QLabel('Username:')
        self.username_line_edit = QLineEdit()
        self.username_line_edit.setMaxLength(30)
        self.client_settings_layout.addWidget(self.username_label, 0, 0)
        self.client_settings_layout.addWidget(self.username_line_edit, 0, 1, 1, 3)

        # ip
        self.client_ip_label = QLabel('IP:')
        self.client_ip_line_edit = QLineEdit()
        self.client_ip_validator = QRegularExpressionValidator("[0-9.]+")
        self.client_ip_line_edit.setValidator(self.client_ip_validator)
        self.client_show_ip_label = QLabel('Show IP:')
        self.client_show_ip_checkbox = QCheckBox()
        self.client_ip_layout = QHBoxLayout()
        self.client_ip_layout.addWidget(self.client_ip_line_edit)
        self.client_ip_layout.addWidget(self.client_show_ip_label)
        self.client_ip_layout.addWidget(self.client_show_ip_checkbox)
        self.client_settings_layout.addWidget(self.client_ip_label, 1, 0)
        self.client_settings_layout.addLayout(self.client_ip_layout, 1, 1, 1, 3)
        self.client_ip_line_edit.setEchoMode(QLineEdit.Password)

        # port
        self.client_port_label = QLabel('Port:')
        self.client_port_line_edit = QLineEdit()
        self.client_port_validator = QRegularExpressionValidator("^(?:0|[1-9]\d{0,3}|[1-5]\d{4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5])$") # only accept 0-65535
        self.client_port_line_edit.setValidator(self.client_port_validator)
        self.client_port_line_edit.setMaxLength(5)
        self.client_settings_layout.addWidget(self.client_port_label, 2, 0)
        self.client_settings_layout.addWidget(self.client_port_line_edit, 2, 1, 1, 3)

        # apply button
        self.client_settings_apply_button = QPushButton('Apply All')
        self.client_settings_layout.addWidget(self.client_settings_apply_button, 5, 0, 1, 4)

        # keep the section from taking up too much space
        self.client_settings_section.setMaximumHeight(self.client_settings_section.height())

        # make connections
        self.username_line_edit.textEdited.connect(lambda: self.on_edited(self.username_label))
        self.client_ip_line_edit.textEdited.connect(lambda: self.on_edited(self.client_ip_label))
        self.client_port_line_edit.textEdited.connect(lambda: self.on_edited(self.client_port_label))
        self.client_settings_apply_button.clicked.connect(self.on_username_applied)
        self.client_settings_apply_button.clicked.connect(self.on_client_ip_applied)
        self.client_settings_apply_button.clicked.connect(self.on_client_port_applied)
        self.client_show_ip_checkbox.stateChanged.connect(self.client_ip_checkbox_changed)

    def make_server_settings_section(self):
        # Settings Layout
        self.server_settings_section = CollapsibleGroupBox("Server Settings")
        self.server_settings_layout = QGridLayout()
        self.server_settings_layout.setColumnStretch(1, 5) # make it so column 1 fills the gaps
        self.server_settings_section.setLayout(self.server_settings_layout)

        # ip
        self.server_ip_label = QLabel('IP:')
        self.server_settings_layout.addWidget(self.server_ip_label, 0, 0)
        self.server_ip_layout = QHBoxLayout()
        self.server_ip_combo_box = PasswordComboBox()
        self.server_ip_combo_box.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        
        self.server_show_ip_label = QLabel('Show IP:')
        self.server_show_ip_checkbox = QCheckBox()
        self.server_ip_layout.addWidget(self.server_ip_combo_box)
        self.server_ip_layout.addWidget(self.server_show_ip_label)
        self.server_ip_layout.addWidget(self.server_show_ip_checkbox)
        self.server_settings_layout.addLayout(self.server_ip_layout, 0, 1, 1, 3)

        # port
        self.server_port_label = QLabel('Port:')
        self.server_port_line_edit = QLineEdit()
        self.server_port_validator = QRegularExpressionValidator("^(?:0|[1-9]\d{0,3}|[1-5]\d{4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5])$") # only accept 0-65535
        self.server_port_line_edit.setValidator(self.server_port_validator)
        self.server_port_line_edit.setMaxLength(5)
        self.server_settings_layout.addWidget(self.server_port_label, 1, 0)
        self.server_settings_layout.addWidget(self.server_port_line_edit, 1, 1, 1, 3)

        # apply button
        self.server_settings_apply_btn = QPushButton('Apply All')
        self.server_settings_layout.addWidget(self.server_settings_apply_btn, 2, 0, 1, 4)

        # Set connections
        self.server_ip_combo_box.activated.connect(lambda: self.on_edited(self.server_ip_label))
        self.server_port_line_edit.textEdited.connect(lambda: self.on_edited(self.server_port_label))
        self.server_settings_apply_btn.clicked.connect(self.on_server_ip_applied)
        self.server_settings_apply_btn.clicked.connect(self.on_server_port_applied)
        self.server_show_ip_checkbox.stateChanged.connect(self.server_ip_checkbox_changed)

    def make_game_setup_section(self):
        self.game_setup_section = CollapsibleGroupBox("Game Setup")
        self.game_setup_layout = QGridLayout()
        self.game_setup_layout.setColumnStretch(1, 5)  # make it so column 1 fills the gaps
        self.game_setup_section.setLayout(self.game_setup_layout)

        # dolphin browse option
        self.dolphin_path_label = QLabel("Dolphin path:")
        self.dolphin_path_line_edit = QLineEdit()
        self.dolphin_path_line_edit.setReadOnly(True)
        self.dolphin_path_browse_button = QPushButton("Browse")
        self.game_setup_layout.addWidget(self.dolphin_path_label)
        self.game_setup_layout.addWidget(self.dolphin_path_label, 1, 0)
        self.game_setup_layout.addWidget(self.dolphin_path_line_edit, 1, 1, 1, 2)
        self.game_setup_layout.addWidget(self.dolphin_path_browse_button, 1, 3)

        # game browse option
        self.game_path_label = QLabel("Game path:")
        self.game_path_line_edit = QLineEdit()
        self.game_path_line_edit.setReadOnly(True)
        self.game_path_browse_button = QPushButton("Browse")
        self.game_setup_layout.addWidget(self.game_path_label, 2, 0)
        self.game_setup_layout.addWidget(self.game_path_line_edit, 2, 1, 1, 2)
        self.game_setup_layout.addWidget(self.game_path_browse_button, 2, 3)

        # get filter depending on platform for the browse() function
        if sys.platform == 'win32':
            filter = "Dolphin Executable (Dolphin.exe DolphinQt2.exe DolphinWx.exe)"
        elif sys.platform == 'linux':
            filter = "Dolphin Executable (dolphin-emu dolphin-emu-qt2 dolphin-emu-wx)"

        # make connections
        self.dolphin_path_browse_button.clicked.connect(lambda: self.browse("dolphin_path", self.dolphin_path_line_edit, "Select Dolphin Executable", filter))
        self.game_path_browse_button.clicked.connect(lambda: self.browse("sms_path", self.game_path_line_edit, "Select SMSO ISO or dol", "Gamecube File (*.iso *.dol)"))

    # whenever inputs are edited, they become bold until they're applied
    def on_edited(self, label: QLabel) -> None:
        if label.text().startswith("*"):
            return
        bold_font = QFont()
        bold_font.setBold(True)
        label.setFont(bold_font)
        label.setText("*"+label.text())

    def on_applied(self, label: QLabel) -> bool:
        if not label.text().startswith("*"):
            return False
        regular_font = QFont()
        regular_font.setBold(False)
        label.setFont(regular_font)
        label.setText(label.text()[1:])
        return True
    
    # client input applied functions
    def on_username_applied(self) -> None:
        if self.on_applied(self.username_label):
            self.set_config.emit("CLIENT", "username", self.username_line_edit.text(), ConfigTypes.STR)
            self.update_username.emit(self.username_line_edit.text())
    def on_client_ip_applied(self) -> None:
        if self.client_ip_label.text().startswith("*") and not is_ip_address(self.client_ip_line_edit.text()):
            PopUpBox.display("You provided an invalid IP address!", PopUpBoxTypes.ERROR)
            return
        if self.on_applied(self.client_ip_label):
            self.set_config.emit("CLIENT", "client_ip", self.client_ip_line_edit.text(), ConfigTypes.STR)
    def on_client_port_applied(self) -> None:
        if self.on_applied(self.client_port_label):
            self.set_config.emit("CLIENT", "client_port", self.client_port_line_edit.text(), ConfigTypes.INT)

    # when the ip box state is changed
    def client_ip_checkbox_changed(self, state: int) -> None:
        if state == 2:
            self.client_ip_line_edit.setEchoMode(QLineEdit.Normal)
        elif state == 0:
            self.client_ip_line_edit.setEchoMode(QLineEdit.Password)

    # server input applied functions
    def on_server_ip_applied(self) -> None:
        if self.on_applied(self.server_ip_label):
            self.set_config.emit("SERVER", "server_ip", self.server_ip_combo_box.currentText(), ConfigTypes.STR)
    def on_server_port_applied(self) -> None:
        if self.on_applied(self.server_port_label):
            self.set_config.emit("SERVER", "server_port", self.server_port_line_edit.text(), ConfigTypes.INT)

    def server_ip_checkbox_changed(self, state: int) -> None:
        if state == 2:
            self.server_ip_combo_box.setPasswordMode(False)
        elif state == 0:
            self.server_ip_combo_box.setPasswordMode(True)

    # opens file dialog and emits set_config signal. This is used in the make_launch_game_section() func
    def browse(self, option: str, line_edit_widget: QLineEdit, caption: str, filter: str) -> None:
        file_name, _ = QFileDialog.getOpenFileName(self, caption, os.getcwd(), filter)
        if file_name:
            self.set_config.emit("CLIENT", option, file_name, ConfigTypes.STR)
            line_edit_widget.setText(file_name)
            self.launch_path_changed.emit()