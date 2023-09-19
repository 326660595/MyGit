import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton
from PyQt5.QtCore import QThread, pyqtSignal

class ClickThread(QThread):
    clicked = pyqtSignal()

    def run(self):
        # 模拟点击按钮的动作
        self.sleep(3)
        self.clicked.emit()

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Click Simulation")
        layout = QVBoxLayout()

        self.button1 = QPushButton("Button 1", self)
        self.button2 = QPushButton("Button 2", self)
        self.button3 = QPushButton("Button 3", self)

        self.button1.clicked.connect(self.on_button_clicked)
        self.button2.clicked.connect(self.on_button_clicked)
        self.button3.clicked.connect(self.on_button_clicked)

        layout.addWidget(self.button1)
        layout.addWidget(self.button2)
        layout.addWidget(self.button3)

        self.setLayout(layout)

        self.click_thread1 = ClickThread()
        self.click_thread2 = ClickThread()
        self.click_thread3 = ClickThread()

        self.click_thread1.clicked.connect(self.button1.click)
        self.click_thread2.clicked.connect(self.button2.click)
        self.click_thread3.clicked.connect(self.button3.click)

    def on_button_clicked(self):
        sender = self.sender()
        print(f"{sender.text()} clicked!")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()

    # 在另一个线程中发射点击信号
    window.click_thread1.start()
    window.click_thread2.start()
    window.click_thread3.start()

    sys.exit(app.exec_())
