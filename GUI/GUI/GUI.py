from PySide6.QtWidgets import QMainWindow, QTabWidget
from PySide6.QtGui import QCloseEvent, Qt, QDesktopServices
from PySide6 import QtGui
from PySide6.QtCore import Signal, QThread, QUrl
from PySide6.QtWebEngineWidgets import QWebEngineView
import qdarktheme
from subprocess import Popen
import socket   # only used to find available IPs
from os import path
import sys

from GUI.ConsoleDockedWidgets import ClientConsole, ServerConsole
from GUI.SettingsWidget import SettingsTab
from GUI.ClientTabWidget import ClientActionsTab
from GUI.ServerTabWidget import ServerActionsTab
from GUI.ExtraWidgets import PopUpBox
from GUI.Commands import ServerCommands, ClientCommands
from Client.Client import Client
from Server.Server import Server
from Misc.DataTypes import ConsoleTypes, ConfigTypes, GamemodeTypes, PopUpBoxTypes
from Misc.Config import Config


class MainWindow(QMainWindow):
    stop_client = Signal()
    stop_server = Signal()
    client_connect = Signal(str, int)
    client_disconnect = Signal()
    client_command = Signal(str, Client)
    server_command = Signal(str, Server)
    chat = Signal(str)
    hm = Signal(str)

    VERSION = '2.2 Beta' # I'm leaving it as a string just in case we ever have something like '2.2a' with a letter in it

    def __init__(self) -> None:
        super().__init__()
        qdarktheme.setup_theme()

        self.directory = path.abspath(path.dirname(sys.argv[0]))

        self.setWindowTitle(f'Super Mario Sunshine Online {self.VERSION}')
        self.setWindowIcon(QtGui.QIcon(f"{self.directory}/Resources/smso_icon.png"))
        self.setGeometry(300, 300, 700, 600)
        self.setMinimumSize(600, 400)

        self.tabs = QTabWidget()
        self.setCentralWidget(self.tabs)

        self.config = Config()

        # initialize the tab widgets
        self.init_console_docked_widgets()
        self.init_settings_tab()
        self.init_client_tab()
        self.init_server_tab()

        # initialize toolbar
        self.init_menubar()

        # initialize the client and server objects and threads to None
        # this is to avoid errors in the closeEvent function
        self.client = None
        self.client_thread = None
        self.server = None
        self.server_thread = None

        self.populate_fields()

    # we need to make sure to clean up the client and server threads before exiting
    def closeEvent(self, event: QCloseEvent) -> None:
        if self.client_thread is not None and self.client_thread.isRunning():
            self.stop_client.emit()
            self.client_thread.destroyed.connect(self.close)
            event.ignore()
            return
        elif self.server_thread is not None and self.server_thread.isRunning():
            self.stop_server.emit()
            self.server_thread.destroyed.connect(self.close)
            event.ignore()
            return
        event.accept()

    def init_menubar(self):
        self.view_menu = self.menuBar().addMenu("View")
        self.options_menu = self.menuBar().addMenu("Options")
        self.help_menu = self.menuBar().addMenu("Help")

        self.dark_mode = self.view_menu.addAction("Dark Mode")
        self.dark_mode.setCheckable(True)
        self.dark_mode.triggered.connect(self.toggle_dark_mode)
        self.reset_docks = self.view_menu.addAction("Reset Consoles")
        self.reset_docks.triggered.connect(self.reset_docked_widgets)
        if self.config.dark_mode:
            self.dark_mode.setChecked(True)
            self.toggle_dark_mode(True)
        else:
            self.toggle_dark_mode(False)
            self.dark_mode.setChecked(False)

        self.launch_sms_with_gui = self.options_menu.addAction("Launch SMS with Dolphin GUI")
        self.launch_sms_with_gui.setCheckable(True)
        self.launch_sms_with_gui.triggered.connect(self.launch_with_dolphin_gui_checkbox_changed)
        if self.config.launch_with_dolphin:
            self.launch_sms_with_gui.setChecked(True)
        else:
            self.launch_sms_with_gui.setChecked(False)

        self.bug_report = self.help_menu.addAction("Report Bug")
        self.bug_report.triggered.connect(lambda: QDesktopServices.openUrl(QUrl("https://forms.gle/oSRA7r1ZbhfJwCHA6")))
        self.documentation = self.help_menu.addAction("Documentation")
        self.documentation.triggered.connect(lambda: QDesktopServices.openUrl(QUrl("https://discord.com/channels/964674658697879632/993182836473466920")))
        self.faq = self.help_menu.addAction("FAQ")
        self.faq.triggered.connect(lambda: QDesktopServices.openUrl(QUrl("https://discord.com/channels/964674658697879632/987893415238852699")))
        self.help_menu.addSeparator()
        self.about = self.help_menu.addAction("About")
        self.about.triggered.connect(self.about_tab)
    
    def toggle_dark_mode(self, checked: bool):
        if checked:
            qdarktheme.setup_theme()
            self.config.set_value("GENERAL", "dark_mode", "True", ConfigTypes.BOOL)
            self.client_console.client_io_widget.change_text_theme()
            self.server_console.server_io_widget.change_text_theme()
        else:
            qdarktheme.setup_theme("light")
            self.config.set_value("GENERAL", "dark_mode", "False", ConfigTypes.BOOL)
            self.client_console.client_io_widget.change_text_theme(dark_mode=False)
            self.server_console.server_io_widget.change_text_theme(dark_mode=False)

    def launch_with_dolphin_gui_checkbox_changed(self, checked: bool) -> None:
        if checked:
            self.config.set_value("GENERAL", "launch_with_dolphin", "True", ConfigTypes.BOOL)
        else:
            self.config.set_value("GENERAL", "launch_with_dolphin", "False", ConfigTypes.BOOL)

    # this gets triggered when the client thread is deleted. setting it to None prevents errors in the closeEvent() func
    def on_client_deleted(self) -> None:
        self.client = None
        self.client_thread = None

    # this gets triggered when the server thread is deleted. setting it to None prevents errors in the closeEvent() func
    def on_server_deleted(self) -> None:
        self.server = None
        self.server_thread = None

    def init_console_docked_widgets(self) -> None:
        self.client_console = ClientConsole()
        self.server_console = ServerConsole()
        self.addDockWidget(Qt.BottomDockWidgetArea, self.client_console)
        self.addDockWidget(Qt.BottomDockWidgetArea, self.server_console)

        self.client_console.launch_sms_button.clicked.connect(self.on_launch_sms)

    def reset_docked_widgets(self) -> None:
        self.client_console.setVisible(True)
        self.server_console.setVisible(True)
        self.client_console.setFloating(False)
        self.server_console.setFloating(False)
        self.addDockWidget(Qt.BottomDockWidgetArea, self.client_console)
        self.addDockWidget(Qt.BottomDockWidgetArea, self.server_console)

    def about_tab(self) -> None:
        about_string = ""
        about_string += f"Super Mario Sunshine Online version {self.VERSION}\n\n"

        about_string += "This is an online mod for Super Mario Sunshine by MasterMattK and Angry_Max.\n\n" 

        about_string += "Special thanks to everyone who has provided help:\n" 
        about_string += "Brocoli (provided SMS co-op source code), Smubs (playtester),\n" 
        about_string += "MithterTheup (playtester), ZenithPunch (playtester), GoogleCheese (playtester, map developer, model maker),\n"
        about_string += "EpicWade (playtester and map developer), Flauke (playtester), and anyone who has been present in the discord.\n"
        about_string += "UncleMeat (model maker), GamerSubzero (model maker)\n\n"

        about_string += "This software is licensed under the MIT license. You should have received a copy on download."

        PopUpBox.display(about_string, PopUpBoxTypes.INFO)

    def init_settings_tab(self) -> None:
        self.settings_tab = SettingsTab()
        self.settings_tab.launch_path_changed.connect(self.on_path_changed)
        self.settings_tab.set_config.connect(self.config.set_value)
        self.tabs.addTab(self.settings_tab, "Settings")

    def on_path_changed(self) -> None:
        if self.config.dolphin_path != '' and self.config.sms_path != '':
            self.clt_tab.launch_game_button.setEnabled(True)
        
    def init_client_tab(self) -> None:
        self.clt_tab = ClientActionsTab()
        self.client_console.hook_button.clicked.connect(self.on_hook_sms)
        self.client_console.connect_button.clicked.connect(self.on_connect_client)
        self.client_console.disconnect_button.clicked.connect(self.on_disconnect_client)

        self.clt_tab.console_msg.connect(self.client_console.client_io_widget.output)
        self.clt_tab.set_config.connect(self.config.set_value)

        self.client_commands = ClientCommands()
        self.client_command.connect(self.client_commands.handle_command)
        self.client_commands.console_msg.connect(self.client_console.client_io_widget.output)
        self.client_console.client_io_widget.command.connect(lambda s: self.client_command.emit(s, self.client))
        self.clt_tab.command.connect(lambda s: self.client_command.emit(s, self.client))
        self.client_commands.clear_sig.connect(self.client_console.client_io_widget.io_text.clear_button.click)
        self.client_commands.hm.connect(self.on_hm)

        self.tabs.addTab(self.clt_tab, 'Client Actions')

    # this function needs to be outside of the ClientTab widget to deal with the Client() object
    def on_hook_sms(self) -> None:
        self.client_console.hook_button.setDisabled(True)
        self.client_console.hook_button.setText("Hooking...")
        self.client_console.client_io_widget.output("Starting Client and attempting to hook...", ConsoleTypes.STARTING)

        self.client_thread = QThread()
        self.client = Client(self.config.username, self.clt_tab.model_list, self.config.model, self.VERSION)
        
        self.client.moveToThread(self.client_thread)

        self.client_thread.started.connect(self.client.hook_sms)
        self.client.destroyed.connect(self.client_thread.quit)
        self.client_thread.finished.connect(self.client_thread.deleteLater)
        self.client_thread.destroyed.connect(self.on_client_deleted)

        self.client.console_msg.connect(self.client_console.client_io_widget.output)
        self.client.client_started.connect(self.on_client_started)
        self.client.client_stopped.connect(self.on_client_stopped)
        self.client.usernames_updated.connect(self.clt_tab.update_username_models)
        self.client.connection_succeeded.connect(self.on_connection_succeeded)
        self.client.connection_failed.connect(self.on_connection_failed)
        self.client.disconnection_succeeded.connect(self.on_disconnection_succeeded)
        self.client.username_changed.connect(lambda username: self.settings_tab.username_line_edit.setText(username))
        self.client.allow_tps_sig.connect(self.on_allow_tps_sig)
        self.client.allow_level_changes_sig.connect(self.on_allow_level_changes_sig)
        self.client_console.unhook_button.clicked.connect(self.client.stop_client)
        self.client_connect.connect(self.client.client_connect)
        self.client_disconnect.connect(self.client.client_disconnect)
        self.stop_client.connect(self.client.stop_client)
        self.client_console.client_io_widget.chat.connect(self.client.chat_message)
        self.hm.connect(self.client.update_model)

        self.settings_tab.update_username.connect(self.client.update_username)
        self.clt_tab.update_model.connect(self.client.update_model)
        self.clt_tab.update_volume.connect(self.client.update_volume)

        self.client_commands.change_level_sig.connect(self.client.on_change_level_sig)
        self.client_commands.list_players_sig.connect(self.client.on_list_players_sig)
        self.client_commands.on_teleport_sig.connect(self.client.on_teleport_sig)

        self.client_thread.start()

    def on_client_started(self) -> None:
        self.clt_tab.setEnabled(True)
        self.client_console.hook_button.setEnabled(True)
        self.client_console.hook_button.setText("Hook onto SMS")
        self.client_console.client_button_stack.setCurrentIndex(1)
        self.client_console.client_io_widget.output("Client Hooked!", ConsoleTypes.STARTING)

    def on_client_stopped(self) -> None:
        self.clt_tab.setDisabled(True)
        self.client_console.hook_button.setText("Hook onto SMS")
        self.client_console.hook_button.setEnabled(True)
        self.client_console.client_button_stack.setCurrentIndex(0)
        self.client_console.connect_stack.setCurrentIndex(0)
        self.client_console.client_io_widget.output("Client Exited!", ConsoleTypes.EXITING)

    def on_connection_succeeded(self) -> None:
        self.client_console.connect_stack.setCurrentIndex(1)
        self.client_console.connect_button.setEnabled(True)
        self.client_console.connect_button.setText("Connect")

    def on_connection_failed(self) -> None:
        self.client_console.connect_stack.setCurrentIndex(0)
        self.client_console.connect_button.setEnabled(True)
        self.client_console.connect_button.setText("Connect")

    def on_disconnection_succeeded(self) -> None:
        self.client_console.connect_stack.setCurrentIndex(0)
        self.client_console.disconnect_button.setEnabled(True)

        self.clt_tab.teleport_button.setEnabled(True)
        self.clt_tab.teleport_destination_combobox.setEnabled(True)
        self.clt_tab.teleport_label.setEnabled(True)

        self.clt_tab.level_button.setEnabled(True)
        self.clt_tab.level_label.setEnabled(True)
        self.clt_tab.stage_combobox.setEnabled(True)
        self.clt_tab.episode_combobox.setEnabled(True)

    def on_allow_tps_sig(self, toggle: bool) -> None:
        self.clt_tab.teleport_button.setEnabled(toggle)
        self.clt_tab.teleport_destination_combobox.setEnabled(toggle)
        self.clt_tab.teleport_label.setEnabled(toggle)

    def on_allow_level_changes_sig(self, toggle: bool) -> None:
        self.clt_tab.level_button.setEnabled(toggle)
        self.clt_tab.level_label.setEnabled(toggle)
        self.clt_tab.stage_combobox.setEnabled(toggle)
        self.clt_tab.episode_combobox.setEnabled(toggle)

    def on_launch_sms(self) -> None:
        self.client_console.client_io_widget.output("Launching SMS!", ConsoleTypes.STARTING)
        if self.config.launch_with_dolphin:
            with_dolphin = ""
        else:
            with_dolphin = "-b"

        if not self.config.verify_game_config():
            self.client_console.client_io_widget.output("The game settings for Sunshine Online (GMSE10) couldn't be verified properly! Your memory may not be expanded!", ConsoleTypes.WARNING)
        try:
            cmd = [
                self.config.dolphin_path,
                f"--exec={self.config.sms_path}",
                with_dolphin
            ]
            self.process = Popen(cmd)
        except OSError:
            self.client_console.client_io_widget.output("You're specified paths failed to launch! Make sure you specified the right paths!", ConsoleTypes.ERROR)
            return
    
    def on_connect_client(self) -> None:
        if self.client == None:
            return
        self.client_console.connect_button.setDisabled(True)
        self.client_console.connect_button.setText("Connecting...")
        self.client_connect.emit(self.config.client_ip, self.config.client_port)

    def on_disconnect_client(self) -> None:
        if self.client == None:
            return
        self.client_console.disconnect_button.setDisabled(True)
        self.client_disconnect.emit()

    def on_hm(self, model: str) -> None:
        model += "_hidden"
        if model.lower() in self.clt_tab.model_list:
            self.clt_tab.model_combo_box.addItem(model.capitalize())
            self.clt_tab.model_combo_box.setCurrentIndex(self.clt_tab.model_combo_box.count() - 1)
            self.hm.emit(model)

    def init_server_tab(self) -> None:
        self.svr_tab = ServerActionsTab()
        self.server_console.start_server_button.clicked.connect(self.start_server_clicked)

        self.svr_tab.console_msg.connect(self.server_console.server_io_widget.output)

        self.server_commands = ServerCommands()
        self.server_command.connect(self.server_commands.handle_command)
        self.server_commands.set_config.connect(self.config.set_value)
        self.server_commands.console_msg.connect(self.server_console.server_io_widget.output)
        self.server_console.server_io_widget.command.connect(lambda s: self.server_command.emit(s, self.server))
        self.svr_tab.command.connect(lambda s: self.server_command.emit(s, self.server))
        self.server_commands.clear_sig.connect(self.server_console.server_io_widget.io_text.clear_button.click)

        self.tabs.addTab(self.svr_tab, 'Server Actions')

    def start_server_clicked(self) -> None:
        self.server_console.start_server_button.setDisabled(True)
        self.server_console.start_server_button.setText("Starting...")
        self.server_console.server_io_widget.output("Starting Server...", ConsoleTypes.STARTING)

        try:
            self.server = Server(self.config.server_ip, self.config.server_port, 8, self.config.sync_flags, self.config.disable_refills, self.VERSION)
        except MemoryError:
            self.server_console.server_io_widget.output("The server could not be started! This could be due to an invalid IP!", ConsoleTypes.ERROR)
            self.server = None
            self.on_server_stopped()
            return
        
        self.server_thread = QThread()
        
        self.server.moveToThread(self.server_thread)

        self.server_thread.started.connect(self.server.start_server)
        self.server.destroyed.connect(self.server_thread.quit)
        self.server_thread.finished.connect(self.server_thread.deleteLater)
        self.server_thread.destroyed.connect(self.on_server_deleted)

        self.server.console_msg.connect(self.server_console.server_io_widget.output)
        self.server.server_started.connect(self.on_server_started)
        self.server.server_stopped.connect(self.on_server_stopped)
        self.server.usernames_updated.connect(self.svr_tab.update_username_models)
        self.server.username_changed.connect(self.svr_tab.on_username_change)
        self.server_console.stop_server_button.clicked.connect(self.server.stop_server)
        self.stop_server.connect(self.server.stop_server)
        self.server_console.server_io_widget.chat.connect(self.server.chat_message)
        self.server.tag_started.connect(lambda: self.svr_tab.tag_stack.setCurrentIndex(1))
        self.server.tag_stopped.connect(lambda: self.svr_tab.tag_stack.setCurrentIndex(0))
        self.server.set_hider.connect(self.svr_tab.on_set_hider)
        self.server.set_tagger.connect(self.svr_tab.on_set_tagger)
        self.server.gamemode_change.connect(self.on_gamemode_change)

        self.server_commands.flags_sig.connect(self.server.on_sync_flags_sig)
        self.server_commands.flags_reset_sig.connect(self.server.on_reset_flags_sig)
        self.server_commands.change_level_sig.connect(self.server.on_change_level_sig)
        self.server_commands.allow_tps_sig.connect(self.server.on_allow_tps_sig)
        self.server_commands.allow_tps_sig.connect(lambda toggle: self.svr_tab.allow_tps_checkbox.setChecked(toggle))
        self.server_commands.allow_level_changes_sig.connect(self.server.on_allow_level_changes_sig)
        self.server_commands.allow_level_changes_sig.connect(lambda toggle: self.svr_tab.allow_level_changes_checkbox.setChecked(toggle))
        self.server_commands.kick_sig.connect(self.server.on_kick_sig)
        self.server_commands.list_players_sig.connect(self.server.on_list_players_sig)
        self.server_commands.on_teleport_sig.connect(self.server.on_teleport_sig)
        self.server_commands.change_gamemode_sig.connect(self.server.on_change_gamemode_sig)
        self.server_commands.tag_commands.add_sig.connect(self.server.on_new_tagger_sig)
        self.server_commands.tag_commands.remove_sig.connect(self.server.on_new_hider_sig)
        self.server_commands.tag_commands.start_sig.connect(self.server.start_tag)
        self.server_commands.tag_commands.stop_sig.connect(self.server.stop_tag)
        self.server_commands.tag_commands.reset_sig.connect(self.server.on_tag_reset_sig)
        self.server_commands.tag_commands.refills_sig.connect(self.server.on_tag_refills_sig)

        self.server_thread.start()

    def on_server_started(self) -> None:
        self.svr_tab.setEnabled(True)
        self.server_console.start_server_button.setEnabled(True)
        self.server_console.start_server_button.setText("Start Server")
        self.server_console.server_button_stack.setCurrentIndex(1)
        self.server_console.server_io_widget.output("Server Started!", ConsoleTypes.STARTING)

    def on_server_stopped(self) -> None:
        self.svr_tab.setDisabled(True)
        self.server_console.start_server_button.setText("Start Server")
        self.server_console.start_server_button.setEnabled(True)
        self.server_console.server_button_stack.setCurrentIndex(0)
        self.server_console.server_io_widget.output("Server Exited!", ConsoleTypes.EXITING)

    def on_gamemode_change(self, mode: GamemodeTypes):
        self.svr_tab.gamemode_stack.setCurrentIndex(mode.value)
        self.svr_tab.gamemode_combobox.setCurrentIndex(mode.value)

    def populate_fields(self) -> None:
        self.settings_tab.dolphin_path_line_edit.setText(self.config.dolphin_path)
        self.settings_tab.game_path_line_edit.setText(self.config.sms_path)
        self.settings_tab.username_line_edit.setText(self.config.username)
        self.settings_tab.client_ip_line_edit.setText(self.config.client_ip)
        self.settings_tab.client_port_line_edit.setText(str(self.config.client_port))
        if self.clt_tab.model_list_display != []:
            self.clt_tab.model_combo_box.addItems(x.capitalize() for x in self.clt_tab.model_list_display)
            lower_model_list = [model.lower() for model in self.clt_tab.model_list_display]
            if self.config.model in lower_model_list:
                self.clt_tab.model_combo_box.setCurrentIndex(lower_model_list.index(self.config.model))
            if self.clt_tab.removed_models != []:
                self.client_console.client_io_widget.output(f"You have more than 16 models in 'Model Data'! The following models will be skipped: {self.clt_tab.removed_models}", ConsoleTypes.WARNING)
        else:
            self.clt_tab.model_combo_box.addItem("'Model Data' Directory Not Found!")
        self.clt_tab.volume_slider.setSliderPosition(self.config.music_volume)
        self.svr_tab.sync_flags_checkbutton.setChecked(self.config.sync_flags)
        self.svr_tab.disable_refills_checkbutton.setChecked(self.config.disable_refills)

        for ip in socket.gethostbyname_ex(socket.gethostname())[2]:
            self.settings_tab.server_ip_combo_box.addItem(ip, userData=ip)
        for i in range(self.settings_tab.server_ip_combo_box.count()):
            if self.config.server_ip == self.settings_tab.server_ip_combo_box.itemData(i):
                self.settings_tab.server_ip_combo_box.setCurrentIndex(i)
        else:
            self.config.set_value("SERVER", "server_ip", self.settings_tab.server_ip_combo_box.currentText(), ConfigTypes.STR)
            
        self.settings_tab.server_ip_combo_box.setPasswordMode(True)
        self.settings_tab.server_port_line_edit.setText(str(self.config.server_port))