import sys
from PyQt5.QtWidgets import  QApplication,QWidget,QMainWindow,QPushButton,QSpinBox,QLineEdit,QTextEdit
from PyQt5 import uic
from Hemming import Hemming

class Program(QMainWindow):
    def __init__(self):
        super(Program, self).__init__()
        uic.loadUi('main_window.ui',self)
        self.init_widgets()
        self.show()

    def init_widgets(self):
        self.btn_encode = self.findChild(QPushButton, 'btn_encode')
        self.btn_encode.clicked.connect(self.button_encode_pressed)

        self.btn_decode = self.findChild(QPushButton, 'btn_decode')
        self.btn_decode.clicked.connect(self.button_decode_pressed)

        self.btn_find_errors = self.findChild(QPushButton, 'btn_find_errors')
        self.btn_find_errors.clicked.connect(self.button_find_errors)

        self.sb_bit = self.findChild(QSpinBox, 'sb_bit')
        self.le_encode = self.findChild(QLineEdit, 'le_encode')
        self.le_decode = self.findChild(QLineEdit, 'le_decode')

        self.txt_result_encode = self.findChild(QTextEdit,'txt_result_encode')
        self.txt_result_decode = self.findChild(QTextEdit, 'txt_result_decode')

    def button_encode_pressed(self):
        message = self.le_encode.text()
        bit = self.sb_bit.value()
        self.hemming = Hemming(message,BITS=bit)
        encode_message = self.hemming.to_hemming_code()
        self.txt_result_encode.setHtml(
            f"<div align='center'><b>Закодированное сообщение:</b></div> <code>{encode_message}</code>"
        )

    def button_decode_pressed(self):
        message = self.le_decode.text()
        bit = self.sb_bit.value()
        self.hemming = Hemming(message, BITS=bit)
        decode_message = self.hemming.from_hemming_code(message)
        self.txt_result_decode.setHtml(
            f"<div align='center'><b>Декодированное сообщение:</b></div> <code>{decode_message}</code>"
        )

    def button_find_errors(self):
        message = self.le_decode.text()
        bit = self.sb_bit.value()
        self.hemming = Hemming(message, BITS=bit)
        self.txt_result_decode.setHtml(
           self.hemming.find_errors_message(message)
        )

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Program()
    sys.exit(app.exec_())