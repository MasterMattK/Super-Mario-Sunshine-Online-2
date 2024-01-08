from PySide6.QtWidgets import QWidget
import logging

from GUI.GUI import PopUpBox
from Misc.DataTypes import PopUpBoxTypes

class ErrorHandling(QWidget):
	@staticmethod
	def log_exception(exctype, value, traceback):
		logging.exception("Uncaught exception", exc_info=(exctype, value, traceback))
		PopUpBox.display("An error has occured in the program!", PopUpBoxTypes.ERROR, "The error has been written to exceptions.log")