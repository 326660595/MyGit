import sys
import time
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QPushButton, QVBoxLayout, QWidget
from PyQt5.QtCore import QThread, pyqtSignal

class CountThread(QThread):
    count_changed = pyqtSignal(int)

    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window

    def run(self):
        for i in range(1, 11):
            time.sleep(1)  # 模拟耗时操作
            self.count_changed.emit(i)
            self.main_window.update_count_from_thread(i)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("QThread Example")
        self.setGeometry(100, 100, 400, 150)

        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        self.layout = QVBoxLayout(self.central_widget)

        self.count_label = QLabel("Count: 0", self.central_widget)
        self.layout.addWidget(self.count_label)

        self.start_button = QPushButton("Start Counting", self.central_widget)
        self.start_button.clicked.connect(self.start_counting)
        self.layout.addWidget(self.start_button)

        self.count_thread = CountThread(self)  # 将MainWindow实例传给CountThread
        self.count_thread.count_changed.connect(self.update_count)

    def start_counting(self):
        self.start_button.setEnabled(False)
        self.count_thread.start()

    def update_count(self, count):
        self.count_label.setText(f"Count: {count}")

    def update_count_from_thread(self, count):
        self.count_label.setText(f"Count (from thread): {count}")

    def ppt():
        print("hello ")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
