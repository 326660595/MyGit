import sys
import time
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout
from PyQt5.QtCore import Qt
from PyQt5.QtCore import (Q_ARG, Q_RETURN_ARG, QMetaObject, Qt, QThread,
                          pyqtSignal, pyqtSlot)
from threading import Thread

class ThreadPy(Thread):

    def __init__(self, parent):
        super(ThreadPy, self).__init__()
        self._running = True
        self._parent = parent

    def stop(self):
        self._running = False

    def run(self):
        while self._running:
            # 通过`invokeMethod`队列调用对应控件信号，`self._parent`是Window窗口对象
            QMetaObject.invokeMethod(self._parent, 'print_world', Qt.QueuedConnection)
            time.sleep(1)

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

        # PY线程
        self.thread2 = ThreadPy(self)
        self.thread2.start()

    def init_ui(self):
        # Create four buttons
        button1 = QPushButton('Button 1', self)
        button2 = QPushButton('Button 2', self)
        button3 = QPushButton('Button 3', self)
        button4 = QPushButton('Button 4', self)
        button5 = QPushButton('Button 5', self)
        button6 = QPushButton('Button 6', self)
        button7 = QPushButton('Button 7', self)
        button8 = QPushButton('Button 8', self)

        # Connect button clicks to the slot (function) that handles the click event
        button1.clicked.connect(self.print_hello)
        button2.clicked.connect(self.print_hello)
        button3.clicked.connect(self.print_hello)
        button4.clicked.connect(self.print_hello)

        # Create a vertical layout and add buttons to it
        layout = QVBoxLayout()
        layout.addWidget(button1)
        layout.addWidget(button2)
        layout.addWidget(button3)
        layout.addWidget(button4)
        layout.addWidget(button5)
        layout.addWidget(button6)
        layout.addWidget(button7)
        layout.addWidget(button8)

        # Set the layout for the main window
        self.setLayout(layout)

        # Set window properties
        self.setWindowTitle('Hello Button App')
        self.setGeometry(100, 100, 300, 200)
        self.show()

    def closeEvent(self, event):
        # 在关闭窗口之前停止线程
        self.thread2.stop()
        self.thread2.join()
        event.accept()

    def print_hello(self):
        print('hello')

    @pyqtSlot(result=bool)
    def print_world(self):
        print('world')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    sys.exit(app.exec_())
