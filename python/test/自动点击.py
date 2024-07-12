import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton
from PyQt5.QtCore import QThread, pyqtSignal

class ClickThread(QThread):
    def __init__(self,ui):
        super().__init__()
        self.ui = ui

    clicked = pyqtSignal()

    def run(self):
        # 模拟点击按钮的动作
        self.sleep(3)
        print(888)
        self.clicked.emit()

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Click Simulation")
        layout = QVBoxLayout()

        self.click_button = QPushButton("Click Me!", self)
        self.click_button.clicked.connect(self.on_button_clicked)

        layout.addWidget(self.click_button)
        self.setLayout(layout)

        self.click_thread = ClickThread(self)
        self.click_thread.clicked.connect(self.on_button_clicked)

    def on_button_clicked(self):
        print("Button clicked!")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()

    # 在另一个线程中发射点击信号
    window.click_thread.start()

    sys.exit(app.exec_())
