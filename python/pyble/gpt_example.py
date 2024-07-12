import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel, QVBoxLayout, QWidget
from PyQt5.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothDeviceInfo

class BluetoothApp(QMainWindow):1

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

        self.central_widget.setLayout(layout)

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

    def on_discovery_finished(self):
        self.device_list.setText(f"{self.device_list.text()}\nDiscovery Finished.")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = BluetoothApp()
    window.show()
    sys.exit(app.exec_())
