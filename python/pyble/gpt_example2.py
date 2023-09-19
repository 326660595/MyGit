import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel, QVBoxLayout, QWidget, QMessageBox
from PyQt5.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothDeviceInfo, QBluetoothSocket, QBluetoothUuid

class BluetoothApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Bluetooth App")
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        layout = QVBoxLayout()

        self.discover_button = QPushButton("Discover Bluetooth Devices")
        self.discover_button.clicked.connect(self.discover_bluetooth_devices)
        layout.addWidget(self.discover_button)

        self.device_list_label = QLabel("Discovered Devices:")
        layout.addWidget(self.device_list_label)

        self.device_list = QLabel()
        layout.addWidget(self.device_list)

        self.connect_button = QPushButton("Connect to Selected Device")
        self.connect_button.clicked.connect(self.connect_to_device)
        layout.addWidget(self.connect_button)

        self.central_widget.setLayout(layout)

        self.selected_device_info = None
        self.socket = QBluetoothSocket(QBluetoothSocket.RfcommSocket)
        self.socket.connected.connect(self.on_connected)
        self.socket.disconnected.connect(self.on_disconnected)
        self.socket.readyRead.connect(self.on_ready_read)

    def discover_bluetooth_devices(self):
        self.device_list.setText("Scanning for Bluetooth devices...")
        self.device_discovery_agent = QBluetoothDeviceDiscoveryAgent()
        self.device_discovery_agent.deviceDiscovered.connect(self.on_device_discovered)
        self.device_discovery_agent.finished.connect(self.on_discovery_finished)
        self.device_discovery_agent.start()

    def on_device_discovered(self, device_info):
        name = device_info.name()
        address = device_info.address().toString()
        self.device_list.setText(f"{self.device_list.text()}\n{name} - {address}")
        self.selected_device_info = device_info

    def on_discovery_finished(self):
        self.device_list.setText(f"{self.device_list.text()}\nDiscovery Finished.")

    def connect_to_device(self):
        if not self.selected_device_info:
            QMessageBox.warning(self, "Error", "No device selected.")
            return

        self.socket.connectToService(self.selected_device_info.address(), QBluetoothUuid.SerialPort)
        if not self.socket.waitForConnected(5000):
            QMessageBox.warning(self, "Error", "Failed to connect to the device.")

    def on_connected(self):
        QMessageBox.information(self, "Success", "Connected to the device.")

    def on_disconnected(self):
        QMessageBox.warning(self, "Disconnected", "The device has disconnected.")
        self.socket.close()

    def on_ready_read(self):
        data = self.socket.readAll()
        # Process received data here

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = BluetoothApp()
    window.show()
    sys.exit(app.exec_())
