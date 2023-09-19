from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QLabel, QComboBox, QPushButton
from PyQt6.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothSocket, QBluetoothUuid

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Bluetooth Scanner")
        self.setFixedSize(300, 200)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        layout = QVBoxLayout(self.central_widget)

        self.label = QLabel("Available Devices:")
        layout.addWidget(self.label)

        self.combo_box = QComboBox()
        layout.addWidget(self.combo_box)

        self.scan_button = QPushButton("Scan")
        self.scan_button.clicked.connect(self.scan)
        layout.addWidget(self.scan_button)

        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect)
        layout.addWidget(self.connect_button)

        self.device_discovery_agent = QBluetoothDeviceDiscoveryAgent()
        self.device_discovery_agent.deviceDiscovered.connect(self.add_device)

        self.bluetooth_socket = QBluetoothSocket(QBluetoothSocket.Protocol.RfcommSocket)
        self.bluetooth_socket.connected.connect(self.on_connected)

    def scan(self):
        self.combo_box.clear()
        self.device_discovery_agent.start()

    def add_device(self, info):
        self.combo_box.addItem(info.address().toString() + ": " + info.name())

    def connect(self):
        address = self.combo_box.currentText().split(":")[0]
        service_uuid = QBluetoothUuid()
        self.bluetooth_socket.connectToService(QBluetoothAddress(address), service_uuid)
        
    def on_connected(self):
        print("Connected to device:", self.bluetooth_socket.peerName())
        # 在这里可以进行进一步的操作，如发送和接收数据

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()
