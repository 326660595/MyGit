import sys  
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit  
  
class MyWidget(QWidget):  
    def __init__(self):  
        super().__init__()  
  
        self.initUI()  
  
    def initUI(self):  
        self.setWindowTitle('PyQt5 Input Box Example')  
        self.setGeometry(300, 300, 300, 150)  
  
        # 创建一个标签和输入框  
        self.label = QLabel(self)  
        self.label.setText('请输入您的名字：')  
        self.label.move(20, 20)  
  
        self.name_input = QLineEdit(self)  
        self.name_input.move(120, 20)  
  
        # 获取输入框的值并打印出来  
        self.name_input.textChanged.connect(self.print_name)  
  
    def print_name(self):  
        name = self.name_input.text()  
        print("您输入的名字是：", name)  
  
if __name__ == '__main__':  
    app = QApplication(sys.argv)  
    my_widget = MyWidget()  
    my_widget.show()  
    sys.exit(app.exec_())