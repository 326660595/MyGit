import sys  
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton  
import time
from datetime import datetime
from threading import Thread

from PyQt5.QtCore import (Q_ARG, Q_RETURN_ARG, QMetaObject, Qt, QThread,
                          pyqtSignal, pyqtSlot)
from PyQt5.QtWidgets import QApplication, QHBoxLayout, QTextBrowser, QWidget

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
            QMetaObject.invokeMethod(self._parent, 'printHello', Qt.QueuedConnection)
            time.sleep(1)


class Example(object):  
  
    def __init__(self):  
        super().__init__()   
        self.button = QPushButton('Print Hello', self)  
        self.button.setToolTip('Click to say hello')  
        self.button.resize(self.button.sizeHint())  
        self.button.clicked.connect(self.printHello)  
  
        self.setGeometry(300, 300, 300, 200)  
        self.setWindowTitle('Print Hello')  
        self.show()  
       # PY线程
        self.thread2 = ThreadPy(self)
        self.thread2.start()
    
   
    
    def test():
        pass
  
    @pyqtSlot(result=bool)
    def printHello(self):  
        print('Hello')  
  
if __name__ == '__main__':  
  
    app = QApplication(sys.argv)  
    ex = Example()  
    sys.exit(app.exec_())