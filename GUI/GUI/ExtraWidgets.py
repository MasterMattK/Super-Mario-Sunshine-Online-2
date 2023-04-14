from PySide6.QtWidgets import (QWidget, QVBoxLayout, QHBoxLayout, QLineEdit, QTextEdit, QLabel, 
    QPushButton, QComboBox, QGroupBox, QLayout, QStackedWidget, QListWidget, QFrame, QMessageBox)
from PySide6.QtGui import (QFont, QTextOption, QTextCursor, QColor, QTextCharFormat, QDropEvent, 
                           QStandardItemModel, QKeyEvent, QIcon, QPixmap, QPainter, QPalette)
from PySide6.QtCore import Signal, QSize, QPoint, QDataStream, QIODevice, QModelIndex, Qt

from Misc.DataTypes import ConsoleTypes, PopUpBoxTypes
import qdarktheme
from os import path
import sys

class LastLineTextEdit(QTextEdit):
    user_input = Signal(str)

    def __init__(self):
        super().__init__()

        self.directory = path.abspath(path.dirname(sys.argv[0]))

        self.init_ui()
        self.insertHtml(">> ")

        self.cursorPositionChanged.connect(self.on_cursor_position_changed)

    def init_ui(self):
        # Set the top and right margins to make space for the clear button
        #self.setViewportMargins(0, 0, 55, 0)

        # Add a QHBoxLayout to the widget's main layout
        self.console_buttons_layout = self.layout() or QVBoxLayout()
        self.setLayout(self.console_buttons_layout)

        # Add a QPushButton widget to the QHBoxLayout
        self.clear_button = QPushButton()
        self.clear_button.clicked.connect(self.clear_text)
        self.console_buttons_layout.addWidget(self.clear_button)
        self.console_buttons_layout.setAlignment(Qt.AlignTop | Qt.AlignRight)
        self.console_buttons_layout.setContentsMargins(11, 11, 20, 11)

        self.clear_button.setIcon(QIcon(f"{self.directory}/Resources/trash_icon.png"))
        self.clear_button.setIconSize(QSize(16, 16))

    def clear_text(self):
        # Clear the text when the clear button is clicked
        self.setPlainText("")
        self.insertHtml(">> ")
        
    def keyPressEvent(self, event: QKeyEvent):
        cursor = self.textCursor()
        if cursor.blockNumber() == self.document().blockCount() - 1:
            if event.key() == Qt.Key_Return or event.key() == Qt.Key_Enter:
                cursor.movePosition(QTextCursor.EndOfBlock)
                cursor.select(QTextCursor.LineUnderCursor)
                last_line_text = cursor.selectedText()[3:]
                if last_line_text.strip():
                    cursor.insertHtml(f"<b>[<i>YOU</i>]</b> {last_line_text}")
                    cursor.clearSelection()
                    self.append(">> ")
                    self.user_input.emit(last_line_text.strip())
            elif event.key() == Qt.Key_Backspace and cursor.positionInBlock() <= 3:
                pass
            else:
                super().keyPressEvent(event)
        else:
            event.ignore()

    def insertLineAbove(self, text: str):
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.End)
        cursor.movePosition(QTextCursor.StartOfLine)
        cursor.insertHtml(f"{text}")
        cursor.insertBlock()
        cursor = self.textCursor()
        cursor.movePosition(QTextCursor.End)

    def on_cursor_position_changed(self):
        cursor = self.textCursor()
        if cursor.atEnd():
            self.setReadOnly(False)
        else:
            self.setReadOnly(True)


class IOWidget(QWidget):
    command = Signal(str)
    chat = Signal(str)

    def __init__(self, parent: QWidget=None) -> None:
        super().__init__(parent)
        self.dark_mode = False

        # Create the widgets
        self.io_text = LastLineTextEdit()
        self.io_text.setWordWrapMode(QTextOption.NoWrap)
        self.font = QFont()
        self.font.setPointSize(10)
        self.io_text.setFont(self.font)

        # Create the layout
        general_layout = QVBoxLayout()
        general_layout.addWidget(self.io_text)
        self.setLayout(general_layout)

        # Connect the widgets
        self.io_text.user_input.connect(self.handle_input)

    def handle_input(self, input: str) -> None:
        if input.strip() == "":
            return
        if input.startswith("/"):
            self.command.emit(input)
        else:
            self.chat.emit(input)

    def output(self, output: str, type: ConsoleTypes) -> None:
        output = output.replace("\n", "<br>")
        if self.dark_mode:
            color = type.value['dark_mode_color']
        else:
            color = type.value['light_mode_color']
        self.io_text.insertLineAbove(f"<font color='{color}'><b>{type.value['prefix']}</b> {output}</font>")

    def change_text_theme(self, dark_mode: bool=True) -> None:
        self.dark_mode = dark_mode

        if dark_mode:
            button_color = qdarktheme.load_palette().buttonText().color()
            background_color = hex(qdarktheme.load_palette().window().color().rgb())[2:]
        else:
            button_color = qdarktheme.load_palette(theme="light").buttonText().color()
            background_color = hex(qdarktheme.load_palette(theme='light').window().color().rgb())[2:]

        for i in range(self.io_text.console_buttons_layout.count()):
            button = self.io_text.console_buttons_layout.itemAt(i).widget()
            if button is not None and isinstance(button, QPushButton):
                pixmap = button.icon().pixmap(QSize(16, 16))
                painter = QPainter(pixmap)
                painter.setCompositionMode(QPainter.CompositionMode_SourceIn)
                painter.fillRect(pixmap.rect(), button_color)
                painter.end()
                button.setIcon(QIcon(pixmap))
                #button.setStyleSheet(f"QPushButton {{background: #{background_color}}}")

        cursor = QTextCursor(self.io_text.document())
        # this essentially acts like a do-while loop so that the check happens at the end
        while True:
            cursor.movePosition(QTextCursor.StartOfLine)
            cursor.movePosition(QTextCursor.EndOfLine, QTextCursor.KeepAnchor)
            format = cursor.charFormat()
            color = ConsoleTypes.get_corresponding_color(format.foreground().color().name(), dark_mode)
            new_format = QTextCharFormat()
            new_format.setForeground(QColor(color))
            cursor.mergeCharFormat(new_format)
            cursor.clearSelection()
            if cursor.atEnd():
                break
            cursor.movePosition(QTextCursor.Down)

    def add_console_button(self, button: QPushButton, image_path: str):
        button.setIcon(QIcon(image_path))
        button.setIconSize(QSize(16, 16))
        self.io_text.console_buttons_layout.addWidget(button)


class CollapsibleGroupBox(QGroupBox):
    def __init__(self, name: str) -> None:
        super().__init__(name)
        self.setCheckable(True)
        #rself.setFlat(True)
        self.toggled.connect(self.toggleGroupBox)
        self.original_max_height = self.height()
        self.original_min_height = self.minimumHeight()

    def toggleGroupBox(self, state: bool) -> None:
        if state:
            self.collapseLayout(self.layout(), True)
            self.setMaximumHeight(self.original_max_height)
            self.setMinimumHeight(self.original_min_height)
        else:
            self.collapseLayout(self.layout(), False)
            self.setMaximumHeight(20, replace_original=False)
            self.setMinimumHeight(0, replace_original=False)

    def collapseLayout(self, lay: QLayout, restore: bool) -> None:
        for i in range(lay.count()):
            w = lay.itemAt(i)
            if w.widget():
                w.widget().setVisible(restore)
            else:
                self.collapseLayout(w, restore)

    # these next two funcs just allow the group boxes to retain their original sizes after being collapsed and uncollapsed
    def setMaximumHeight(self, maxh: int, replace_original: bool=True) -> None:
        super().setMaximumHeight(maxh)
        if replace_original:
            self.original_max_height = maxh
    def setMinimumHeight(self, minh: int, replace_original: bool=True) -> None:
        super().setMinimumHeight(minh)
        if replace_original:
            self.original_min_height = minh

class PasswordComboBox(QComboBox):
    def __init__(self, parent=None) -> None:
        super().__init__(parent)
        self._password_mode = False
        
    def setPasswordMode(self, password_mode: bool) -> None:
        self._password_mode = password_mode

        for i in range(self.count()):
            if password_mode:
                item_text = "•" * len(self.itemData(i))
            else:
                item_text = self.itemData(i)
            self.setItemText(i, item_text)
    
    def passwordMode(self) -> bool:
        return self._password_mode

class StackedWidget(QStackedWidget):
    def sizeHint(self) -> QSize:
        return self.currentWidget().sizeHint()

    def minimumSizeHint(self) -> QSize:
        return self.currentWidget().minimumSizeHint()

class TagListWidget(QListWidget):
    newUsernameDropped = Signal(str)
    def dropEvent(self, event: QDropEvent) -> None:
        if event.source() != self:
            model = QStandardItemModel()
            model.dropMimeData(event.mimeData(), Qt.CopyAction, 0, 0, QModelIndex())
            username = model.item(0, 0).text()
            self.newUsernameDropped.emit(username)
        super().dropEvent(event)

class Separator(QFrame):
    def __init__(self) -> None:
        super().__init__()
        self.setFrameShape(QFrame.HLine)

class PopUpBox:
    @staticmethod
    def display(text: str, type: PopUpBoxTypes, detailed_text: str = None) -> int:
        message_box = QMessageBox()

        message_box.setText(text)
        if detailed_text:
            message_box.setDetailedText(detailed_text)
            
        if type == PopUpBoxTypes.ERROR:
            message_box.setIcon(QMessageBox.Critical)
            message_box.setWindowTitle("Error")
        elif type == PopUpBoxTypes.CONFIRM:
            message_box.setIcon(QMessageBox.Question)
            message_box.setWindowTitle("Confirmation")
            
            message_box.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
            message_box.setDefaultButton(QMessageBox.No)
        elif type == PopUpBoxTypes.INFO:
            message_box.setIcon(QMessageBox.Information)
            message_box.setWindowTitle("Info")

        return message_box.exec()