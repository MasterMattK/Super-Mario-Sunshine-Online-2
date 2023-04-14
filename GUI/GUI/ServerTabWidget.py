from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QGridLayout, QScrollArea, QLabel, QLineEdit, 
    QPushButton, QComboBox, QStackedWidget, QRadioButton, QFrame, QAbstractItemView, QMessageBox, QCheckBox)
from PySide6.QtGui import QPalette, QFont, QStandardItemModel, QStandardItem
from PySide6.QtCore import Signal, Qt, QPoint

from GUI.ExtraWidgets import StackedWidget, TagListWidget, Separator, PopUpBox
from Misc.DataTypes import ConsoleTypes, PopUpBoxTypes
from Misc.LevelData import LevelData

class ServerActionsTab(QScrollArea):
    console_msg = Signal(str, ConsoleTypes)
    command = Signal(str)

    def __init__(self) -> None:
        super().__init__()
        self.setWidgetResizable(True)
        self.setBackgroundRole(QPalette.AlternateBase)

        # General Layout
        self.server_layout = QVBoxLayout()
        self.server_layout.setAlignment(Qt.AlignTop)
        self.main_widget = QWidget()
        self.main_widget.setLayout(self.server_layout)
        self.setWidget(self.main_widget)

        # Make sections
        self.make_general_section()
        self.make_gamemode_section()

        # add the widgets to the layout
        self.server_layout.addWidget(self.actions_section)
        self.server_layout.addWidget(Separator())
        self.server_layout.addWidget(self.gamemode_section)
        self.server_layout.setSpacing(10)

        self.setDisabled(True)

    def make_general_section(self):
        # Server Actions section layout
        self.actions_section = QWidget()
        self.actions_layout = QGridLayout()
        self.actions_layout.setColumnStretch(1, 5) # make it so column 1 fills the gaps
        self.actions_section.setLayout(self.actions_layout)

        # model of usernames
        self.username_and_all_model = QStandardItemModel(1, 1)
        self.username_and_all_model.setItem(0, 0, QStandardItem("All Users"))
        self.username_only_model = QStandardItemModel(0, 1)

        # teleport
        self.teleport_layout = QHBoxLayout()
        self.teleport_label = QLabel('Teleport:')
        self.teleport_user_combobox = QComboBox()
        self.teleport_destination_combobox = QComboBox()
        self.teleport_user_combobox.setModel(self.username_only_model)
        self.teleport_destination_combobox.setModel(self.username_only_model)
        self.teleport_button = QPushButton("Teleport!")
        self.teleport_layout.addWidget(self.teleport_user_combobox)
        self.teleport_layout.addWidget(self.teleport_destination_combobox)
        self.actions_layout.addWidget(self.teleport_label, 0, 0)
        self.actions_layout.addLayout(self.teleport_layout, 0, 1, 1, 3)
        self.actions_layout.addWidget(self.teleport_button, 0, 4)

        # set level
        self.level_data = LevelData()
        self.level_label = QLabel('Set Level:')
        self.stage_combobox = QComboBox()
        self.stage_combobox.addItems(self.level_data.get_stage_options())
        self.episode_combobox = QComboBox()
        self.episode_combobox.setDuplicatesEnabled(True)
        self.episode_combobox.addItems(self.level_data.get_episode_options()[0])
        self.level_button = QPushButton('Change Level!')
        self.level_user_combobox = QComboBox()
        self.level_user_combobox.setModel(self.username_and_all_model)
        self.level_layout = QHBoxLayout()
        self.level_layout.addWidget(self.stage_combobox, 1)
        self.level_layout.addWidget(self.episode_combobox, 3)
        self.level_layout.addWidget(self.level_user_combobox, 3)
        self.actions_layout.addWidget(self.level_label, 2, 0)
        self.actions_layout.addLayout(self.level_layout, 2, 1, 1, 3)
        self.actions_layout.addWidget(self.level_button, 2, 4)

        # kick
        self.kick_label = QLabel("Kick:")
        self.kick_user_combobox = QComboBox()
        self.kick_user_combobox.setModel(self.username_and_all_model)
        self.kick_button = QPushButton("Kick!")
        self.actions_layout.addWidget(self.kick_label, 3, 0)
        self.actions_layout.addWidget(self.kick_user_combobox, 3, 1)
        self.actions_layout.addWidget(self.kick_button, 3, 2)

        self.allow_tps_layout = QHBoxLayout()
        self.allow_tps_label = QLabel("Allow Client Teleports:")
        self.allow_tps_checkbox = QCheckBox()
        self.allow_tps_layout.addWidget(self.allow_tps_label)
        self.allow_tps_layout.addWidget(self.allow_tps_checkbox)

        self.allow_level_changes_layout = QHBoxLayout()
        self.allow_level_changes_label = QLabel("Allow Client Level Changes:")
        self.allow_level_changes_checkbox = QCheckBox()
        self.allow_level_changes_layout.addWidget(self.allow_level_changes_label)
        self.allow_level_changes_layout.addWidget(self.allow_level_changes_checkbox)

        self.actions_layout.addLayout(self.allow_tps_layout, 3, 3)
        self.actions_layout.addLayout(self.allow_level_changes_layout, 3, 4)

        # connections
        self.stage_combobox.currentIndexChanged.connect(self.on_stage_changed)
        self.level_button.clicked.connect(self.on_level_change_clicked)
        self.teleport_button.clicked.connect(self.on_teleport_clicked)
        self.kick_button.clicked.connect(self.on_kick_clicked)
        self.allow_tps_checkbox.clicked.connect(self.on_allow_tps_clicked)
        self.allow_level_changes_checkbox.clicked.connect(self.on_allow_level_changes_clicked)

    def make_gamemode_section(self) -> None:
        self.gamemode_section = QWidget()
        self.gamemode_layout = QGridLayout()
        self.gamemode_layout.setColumnStretch(1, 5) # make it so column 1 fills the gaps
        self.gamemode_section.setLayout(self.gamemode_layout)

        # gamemode options
        self.gamemode_label = QLabel("Gamemode:")
        self.gamemode_combobox = QComboBox()
        self.gamemode_combobox.addItem("Cooperative Play")
        self.gamemode_combobox.addItem("Tag/Hide'n'Seek")
        self.gamemode_layout.addWidget(self.gamemode_label, 5, 0)
        self.gamemode_layout.addWidget(self.gamemode_combobox, 5, 1, 1, 4)

        # gamemode stacked widget for different gamemodes
        self.gamemode_frame = QFrame()
        self.gamemode_frame.setFrameShape(QFrame.StyledPanel)
        self.gamemode_stack_layout = QHBoxLayout()
        self.gamemode_stack = StackedWidget()
        self.gamemode_stack_layout.addWidget(self.gamemode_stack)
        self.gamemode_frame.setLayout(self.gamemode_stack_layout)
        self.gamemode_layout.addWidget(self.gamemode_frame, 6, 0, 1, 5)

        # sync flags
        self.flags_layout = QHBoxLayout()
        self.sync_flags_checkbutton = QRadioButton("Sync Flags")
        self.sync_flags_checkbutton.setCheckable(True)
        self.reset_flags_button = QPushButton("Reset Flags")
        self.flags_layout.addWidget(self.sync_flags_checkbutton, stretch=0)
        self.flags_layout.addWidget(self.reset_flags_button, stretch=5)
        self.flags_widget = QWidget()
        self.flags_widget.setLayout(self.flags_layout)
        self.gamemode_stack.addWidget(self.flags_widget)

        # tag stuff
        self.tagger_label = QLabel("Taggers")
        self.tagger_list = TagListWidget()
        self.hider_label = QLabel("Hiders")
        self.hider_list = TagListWidget()
        self.tagger_list.setDragDropMode(QAbstractItemView.DragDrop)
        self.hider_list.setDragDropMode(QAbstractItemView.DragDrop)
        self.tagger_list.setDefaultDropAction(Qt.MoveAction)
        self.hider_list.setDefaultDropAction(Qt.MoveAction)
        self.tag_stack = QStackedWidget()
        self.start_tag_button = QPushButton("Start Tag")
        self.stop_tag_button = QPushButton("Stop Tag")
        self.tag_stack.addWidget(self.start_tag_button)
        self.tag_stack.addWidget(self.stop_tag_button)
        self.reset_tag_button = QPushButton("Reset Tag")
        self.disable_refills_checkbutton = QRadioButton("Disable FLUDD refills for hiders")

        self.tag_layout = QGridLayout()
        self.tag_layout.addWidget(self.tagger_label, 0, 0, 1, 3, alignment=Qt.AlignCenter)
        self.tag_layout.addWidget(self.hider_label, 0, 3, 1, 3, alignment=Qt.AlignCenter)
        self.tag_layout.addWidget(self.tagger_list, 1, 0, 1, 3)
        self.tag_layout.addWidget(self.hider_list, 1, 3, 1, 3)
        self.tag_layout.addWidget(self.tag_stack, 2, 0, 1, 2)
        self.tag_layout.addWidget(self.reset_tag_button, 2, 2, 1, 2)
        self.tag_layout.addWidget(self.disable_refills_checkbutton, 2, 4, 1, 2)
        self.tag_widget = QWidget()
        self.tag_widget.setLayout(self.tag_layout)
        self.gamemode_stack.addWidget(self.tag_widget)

        self.gamemode_combobox.activated.connect(self.on_gamemode_changed)
        self.sync_flags_checkbutton.clicked.connect(self.on_sync_flags_toggled)
        self.reset_flags_button.clicked.connect(self.on_reset_flags_clicked)
        self.tagger_list.newUsernameDropped.connect(lambda username: self.command.emit(f"/tag add {username}"))
        self.hider_list.newUsernameDropped.connect(lambda username: self.command.emit(f"/tag remove {username}"))
        self.start_tag_button.clicked.connect(lambda: self.command.emit("/tag start"))
        self.stop_tag_button.clicked.connect(lambda: self.command.emit("/tag stop"))
        self.reset_tag_button.clicked.connect(self.on_reset_tag_clicked)
        self.disable_refills_checkbutton.clicked.connect(self.on_disable_refills_toggled)

    def on_flags_edited(self) -> None:
        if self.sync_flags_label.text().startswith("*"):
            return
        my_font = QFont()
        my_font.setBold(True)
        self.sync_flags_label.setFont(my_font)
        self.sync_flags_label.setText("*"+self.sync_flags_label.text())

    def on_flags_applied(self) -> None:
        if not self.sync_flags_label.text().startswith("*"):
            return
        my_font = QFont()
        my_font.setBold(False)
        self.sync_flags_label.setFont(my_font)
        self.sync_flags_label.setText(self.sync_flags_label.text()[1:])
        #self.set_config.emit("SERVER", "flags", self.flags_menu.currentText().lower())

    def on_stage_changed(self, index: int) -> None:
        self.episode_combobox.clear()
        self.episode_combobox.addItems(self.level_data.get_episode_options()[index])

    def on_level_change_clicked(self) -> None:
        if self.level_user_combobox.currentText() == "All Users":
            username = ""
        else:
            username = self.level_user_combobox.currentText()
        self.command.emit(f"/level {self.level_data.level_data[self.stage_combobox.currentText()][self.episode_combobox.currentText()]['ep_command']} {username}")

    def on_teleport_clicked(self) -> None:
        tp_user = self.teleport_user_combobox.currentText()
        tp_dest = self.teleport_destination_combobox.currentText()
        if not tp_user or not tp_dest:
            self.console_msg.emit("You didn't specify any users to teleport!", ConsoleTypes.ERROR)
            return
        
        self.command.emit(f"/tp {tp_user} {tp_dest}")

    def on_kick_clicked(self) -> None:
        user = self.kick_user_combobox.currentText()
        if not user:
            self.console_msg.emit("You didn't specify any users to teleport!", ConsoleTypes.ERROR)
            return

        if user == "All Users":
            username = "all"
        else:
            username = user

        self.command.emit(f"/kick {username}")

    def on_allow_tps_clicked(self, state: bool) -> None:
        if state:
            self.command.emit("/allowtps on")
        else:
            self.command.emit("/allowtps off")

    def on_allow_level_changes_clicked(self, state: bool) -> None:
        if state:
            self.command.emit("/allowlevels on")
        else:
            self.command.emit("/allowlevels off")

    def on_gamemode_changed(self, index: int) -> None:
        self.command.emit(f"/gamemode {index}")
        self.gamemode_stack.setCurrentIndex(index)

    def on_sync_flags_toggled(self, checked: bool) -> None:
        if checked:
            self.command.emit("/flags on")
        else:
            self.command.emit("/flags off")

    def on_reset_flags_clicked(self) -> None:
        result = PopUpBox.display("Are you sure you want to reset all flags?\nAll shines, blue coins, and other flags will be reset for everyone.", 
                                  PopUpBoxTypes.CONFIRM)
        if result == QMessageBox.Yes:
            self.command.emit("/flagsreset")

    def on_reset_tag_clicked(self) -> None:
        result = PopUpBox.display("Are you sure you want to reset this game of tag?\nAll timers will be reset.", 
                         PopUpBoxTypes.CONFIRM)
        if result == QMessageBox.Yes:
            self.command.emit("/tag reset")

    def on_disable_refills_toggled(self, checked: bool) -> None:
        if checked:
            self.command.emit("/tag refills off")
        else:
            self.command.emit("/tag refills on")
    
    def update_username_models(self, username_list: list) -> None:
        self.username_and_all_model.clear()
        self.username_only_model.clear()
        self.username_and_all_model.setItem(0, 0, QStandardItem("All Users"))

        for i, username in enumerate(username_list):
            self.username_and_all_model.setItem(i+1, 0, QStandardItem(username))
            self.username_only_model.setItem(i, 0, QStandardItem(username))

        new_tagger_list = []
        for i in range(self.tagger_list.count()):
            item = self.tagger_list.item(i).text()
            if item in username_list:
                new_tagger_list.append(item)
        self.tagger_list.clear()
        self.tagger_list.addItems(new_tagger_list)

        new_hider_list = []
        for i in range(self.hider_list.count()):
            item = self.hider_list.item(i)
            if item in username_list:
                new_hider_list.append(item)

        for item in username_list:
            if item not in new_tagger_list and item not in new_hider_list:
                new_hider_list.append(item)

        self.hider_list.clear()
        self.hider_list.addItems(new_hider_list)

        self.teleport_user_combobox.setCurrentIndex(0)
        self.teleport_destination_combobox.setCurrentIndex(0)
        self.level_user_combobox.setCurrentIndex(0)
        self.kick_user_combobox.setCurrentIndex(0)

    # whenever a username is changed rather than a new player connecting or leaving, we need to update
    # it separately to keep that user consistent
    def on_username_change(self, changed_username: tuple) -> None:
        for row in range(self.username_only_model.rowCount()):
            if self.username_only_model.item(row, 0).text() == changed_username[0]:
                self.username_only_model.setItem(row, 0, QStandardItem(changed_username[1]))
                self.username_and_all_model.setItem(row+1, 0, QStandardItem(changed_username[1]))
                break
        
        for i in range(self.hider_list.count()):
            item = self.hider_list.item(i)
            if item.text() == changed_username[0]:
                item.setText(changed_username[1])

        for i in range(self.tagger_list.count()):
            item = self.tagger_list.item(i)
            if item.text() == changed_username[0]:
                item.setText(changed_username[1])

    def on_set_hider(self, username: str) -> None:
        for i in range(self.tagger_list.count()):
            item = self.tagger_list.item(i)
            if item.text() == username:
                self.tagger_list.takeItem(i)
                self.hider_list.addItem(username)
                break

    def on_set_tagger(self, username: str) -> None:
        for i in range(self.hider_list.count()):
            item = self.hider_list.item(i)
            if item.text() == username:
                self.hider_list.takeItem(i)
                self.tagger_list.addItem(username)
                break
