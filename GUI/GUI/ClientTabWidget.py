from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QGridLayout, QScrollArea, QLabel, QLineEdit,   
    QPushButton, QSizePolicy, QCheckBox, QComboBox, QSlider, QStackedWidget, QFrame)
from PySide6.QtGui import QPalette, QStandardItemModel, QStandardItem
from PySide6.QtCore import Signal, Qt

from GUI.ExtraWidgets import CollapsibleGroupBox, IOWidget, Separator
from Misc.LevelData import LevelData
from Misc.DataTypes import ConsoleTypes, ConfigTypes
import os
import sys

class ClientActionsTab(QScrollArea):
    console_msg = Signal(str, ConsoleTypes)
    set_config = Signal(str, str, str, ConfigTypes)
    update_model = Signal(str)
    update_volume = Signal(int)
    command = Signal(str)

    def __init__(self) -> None:
        super().__init__()

        self.directory = os.path.abspath(os.path.dirname(sys.argv[0]))

        self.setWidgetResizable(True)
        self.setBackgroundRole(QPalette.AlternateBase)

        # General Layout
        self.client_layout = QVBoxLayout() 
        self.client_layout.setAlignment(Qt.AlignTop)   # this is so that the widgets always push to the top
        self.main_widget = QWidget()
        self.main_widget.setLayout(self.client_layout)
        self.setWidget(self.main_widget)

        # Make sections
        self.make_client_actions_section()

        # add the widgets to the layout
        self.client_layout.addWidget(self.actions_section)
        self.client_layout.setSpacing(10)

        self.setDisabled(True)
        
    def make_client_actions_section(self):
        # Client Actions section layout
        self.actions_section = QWidget()
        self.actions_layout = QGridLayout()
        self.actions_layout.setColumnStretch(1, 5) # make it so column 1 fills the gaps
        self.actions_section.setLayout(self.actions_layout)

        # model of usernames
        self.username_model = QStandardItemModel(0, 1)

        # teleport
        self.teleport_layout = QHBoxLayout()
        self.teleport_label = QLabel('Teleport:')
        self.teleport_destination_combobox = QComboBox()
        self.teleport_destination_combobox.setModel(self.username_model)
        self.teleport_button = QPushButton("Teleport!")
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
        self.level_layout = QHBoxLayout()
        self.level_layout.addWidget(self.stage_combobox, 1)
        self.level_layout.addWidget(self.episode_combobox, 3)
        self.actions_layout.addWidget(self.level_label, 2, 0)
        self.actions_layout.addLayout(self.level_layout, 2, 1, 1, 3)
        self.actions_layout.addWidget(self.level_button, 2, 4)

        # model
        self.model_label = QLabel('Model:')
        self.model_combo_box = QComboBox()
        self.actions_layout.addWidget(self.model_label, 3, 0)
        self.actions_layout.addWidget(self.model_combo_box, 3, 1, 1, 4)

        # get model list
        if os.path.exists(f"{self.directory}/Model Data"):
            self.model_list = os.listdir(f"{self.directory}/Model Data")
            self.model_list.insert(0, "mario")
        else:
            self.model_list = []

        self.removed_models = []
        if len(self.model_list) > 16:
            dif = len(self.model_list) - 16
            self.removed_models = []
            for i in range(dif):
                self.removed_models.append(self.model_list.pop(-1))

        self.model_list_display = self.model_list.copy()
        to_remove = []
        for model in self.model_list_display:
            if model.endswith("_hidden"):
                to_remove.append(model)

        for model in to_remove:
            self.model_list_display.remove(model)

        # volume slider
        self.volume_label = QLabel('Music Volume:')
        self.volume_slider = QSlider(orientation=Qt.Horizontal)
        self.volume_slider.setRange(0, 150)
        self.volume_slider.setSliderPosition(75)
        self.actions_layout.addWidget(self.volume_label, 4, 0)
        self.actions_layout.addWidget(self.volume_slider, 4, 1, 1, 4)

        # make connections
        self.stage_combobox.currentIndexChanged.connect(self.on_stage_changed)
        self.teleport_button.clicked.connect(self.on_teleport_clicked)
        self.level_button.clicked.connect(self.on_change_level_clicked)
        self.model_combo_box.activated.connect(self.on_model_changed)
        self.volume_slider.valueChanged.connect(self.on_volume_changed)

    def on_stage_changed(self, index: int) -> None:
        self.episode_combobox.clear()
        self.episode_combobox.addItems(self.level_data.get_episode_options()[index])

    def on_teleport_clicked(self):
        tp_dest = self.teleport_destination_combobox.currentText()
        if not tp_dest:
            self.console_msg.emit("You didn't specify any users to teleport to!", ConsoleTypes.ERROR)
            return
        
        self.command.emit(f"/tp {tp_dest}")

    def on_change_level_clicked(self):
        self.command.emit(f"/level {self.level_data.level_data[self.stage_combobox.currentText()][self.episode_combobox.currentText()]['ep_command']}")

    def on_model_changed(self) -> None:
        self.set_config.emit("CLIENT", "model", self.model_combo_box.currentText().lower(), ConfigTypes.STR)
        self.update_model.emit(self.model_combo_box.currentText().lower())

    def on_volume_changed(self) -> None:
        self.set_config.emit("CLIENT", "music_volume", str(self.volume_slider.value()), ConfigTypes.INT)
        self.update_volume.emit(self.volume_slider.value())

    def update_username_models(self, username_list: list) -> None:
        self.username_model.clear()

        for i, username in enumerate(username_list):
            self.username_model.setItem(i, 0, QStandardItem(username))

        self.teleport_destination_combobox.setCurrentIndex(0)
