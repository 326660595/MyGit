import sys
import time
from PyQt5.QtCore import QObject, QThread, pyqtSignal, pyqtSlot, Qt
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget

# 自定义工作线程
class WorkerThread(QThread):
    # 定义一个信号，用于传递消息
    update_signal = pyqtSignal(str)
    update_signal1 = pyqtSignal()

    def __init__(self, parent=None):
        QThread.__init__(self, parent)

    def run(self):
        # 模拟耗时操作
        for i in range(5):
            time.sleep(1)
            # 发送信号，传递消息给主线程
            if (i%2) == 0:
                self.update_signal.emit(f'Processing {i+1}...')
            else:
                self.update_signal1.emit()


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setWindowTitle('Thread Communication Example')

        # 创建一个标签用于显示消息
        self.label = QLabel(self)
        self.label.setText('Waiting for updates...')
        self.label.setAlignment(Qt.AlignCenter)

        # 创建一个垂直布局，并将标签添加到布局中
        layout = QVBoxLayout()
        layout.addWidget(self.label)

        # 创建一个主窗口部件，并将布局设置为主窗口的布局
        main_widget = QWidget()
        main_widget.setLayout(layout)
        self.setCentralWidget(main_widget)

        # 创建并启动工作线程
        self.worker_thread = WorkerThread()
        self.worker_thread.update_signal.connect(self.updateLabel)  # 连接信号与槽
        self.worker_thread.update_signal1.connect(self.print_hello)  # 连接信号与槽
        self.worker_thread.start()

        self.show()

    # @pyqtSlot(str)  # 指定槽函数的参数类型
    def updateLabel(self, message):
        self.label.setText(message)

    def print_hello(self):
        print("hello")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())
