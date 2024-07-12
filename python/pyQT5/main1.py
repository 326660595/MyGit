import asyncio
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QPushButton, QListWidget, QLabel, QWidget
from PyQt5.QtCore import pyqtSlot
from bleak import BleakScanner, BleakClient

class BleApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.scanner = BleakScanner()
        self.client = None

        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 300, 200)
        self.setWindowTitle('Bleak PyQt App')

        self.main_widget = QWidget(self)
        self.setCentralWidget(self.main_widget)

        v_layout = QVBoxLayout(self.main_widget)

        self.device_list = QListWidget(self)
        self.refresh_button = QPushButton('Refresh', self)
        self.connect_button = QPushButton('Connect', self)
        self.status_label = QLabel('Not Connected', self)

        v_layout.addWidget(self.device_list)
        v_layout.addWidget(self.refresh_button)
        v_layout.addWidget(self.connect_button)
        v_layout.addWidget(self.status_label)

        self.refresh_button.clicked.connect(self.on_refresh)
        self.connect_button.clicked.connect(self.on_connect)

    def on_refresh(self):
        self.device_list.clear()
        asyncio.run(self.refresh())

    async def refresh(self):
        devices = await self.scanner.discover()
        for device in devices:
            self.device_list.addItem(device.name)

    def on_connect(self):
        device_name = self.device_list.currentItem().text()
        if device_name:
            asyncio.run(self.connect(device_name))

    async def connect(self, name):
        devices = await self.scanner.discover()
        for device in devices:
            if device.name == name:
                self.client = BleakClient(device)
                break

        if self.client is not None:
            await self.client.connect()
            if self.client.is_connected:
                self.status_label.setText('Connected')
            else:
                self.status_label.setText('Failed to connect')

app = QApplication([])
myapp = BleApp()
myapp.show()
app.exec_()
