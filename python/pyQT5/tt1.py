import sys
import time
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QLineEdit
from PyQt5.QtCore import Qt, QThread

class ThreadPy(QThread):
    def __init__(self):
        super(ThreadPy, self).__init__()
        self._running = True

    def stop(self):
        self._running = False

    def run(self):
        while self._running:
            print('world')
            time.sleep(1)

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.input_fields = []  # 创建一个列表来存储文本输入框
        self.init_ui()

        # PY线程
        self.thread2 = ThreadPy()
        self.thread2.start()

    def init_ui(self):
        # 创建四个按钮
        button1 = QPushButton('按钮1', self)
        button2 = QPushButton('按钮2', self)
        button3 = QPushButton('按钮3', self)
        button4 = QPushButton('按钮4', self)

        # 将按钮点击事件连接到处理点击的槽函数
        button1.clicked.connect(self.print_hello)
        button2.clicked.connect(self.print_hello)
        button3.clicked.connect(self.print_hello)
        button4.clicked.connect(self.print_hello)

        # 创建八个文本输入框
        for i in range(8):
            input_field = QLineEdit(self)
            self.input_fields.append(input_field)

        # 创建一个垂直布局并将按钮和文本输入框添加到其中
        layout = QVBoxLayout()
        layout.addWidget(button1)
        layout.addWidget(button2)
        layout.addWidget(button3)
        layout.addWidget(button4)

        # 将文本输入框添加到布局中
        for input_field in self.input_fields:
            layout.addWidget(input_field)

        # 设置主窗口的布局
        self.setLayout(layout)

        # 设置窗口属性
        self.setWindowTitle('按钮和文本输入框示例')
        self.setGeometry(100, 100, 300, 300)
        self.show()

    def closeEvent(self, event):
        # 在关闭窗口之前停止线程
        self.thread2.stop()
        self.thread2.wait()
        event.accept()

    def print_hello(self):
        print('你好')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    sys.exit(app.exec_())
