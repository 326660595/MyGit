import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction, QFileDialog

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        # 创建一个菜单栏
        menubar = self.menuBar()

        # 创建一个文件菜单
        file_menu = menubar.addMenu('File')

        # 创建一个加载文件的动作
        open_action = QAction('Open', self)
        open_action.triggered.connect(self.openFile)

        # 将加载文件的动作添加到文件菜单
        file_menu.addAction(open_action)

        self.setGeometry(300, 300, 300, 200)
        self.setWindowTitle('File Loader')
        self.show()

    def openFile(self):
        # 打开文件对话框，让用户选择要加载的文件
        options = QFileDialog.Options()
        options |= QFileDialog.ReadOnly

        file_path, _ = QFileDialog.getOpenFileName(self, 'Open File', '', 'Text Files (*.txt);;All Files (*)', options=options)

        if file_path:
            # 在这里可以处理加载文件的逻辑，这里只是简单地打印文件路径
            print('Selected file:', file_path)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())
