import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel, QPushButton
from PyQt6.QtCore import Qt
from PyQt6.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothLocalDevice


class BluetoothApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Bluetooth Connection")
        self.setGeometry(100, 100, 300, 200)

        self.discovery_agent = QBluetoothDeviceDiscoveryAgent()

        self.label = QLabel("No devices found.", self)
        self.label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.label.setGeometry(40, 40, 220, 30)

        self.scan_button = QPushButton("Scan", self)
        self.scan_button.setGeometry(100, 100, 100, 30)
        self.scan_button.clicked.connect(self.scan_devices)

    def scan_devices(self):
        self.discovery_agent.setLowEnergyDiscoveryTimeout(2000)
        self.discovery_agent.deviceDiscovered.connect(self.device_discovered)
        self.discovery_agent.finished.connect(self.scan_finished)

        self.discovery_agent.start()

        # 停止扫描并手动调用scan_finished函数
        # self.discovery_agent.stop()
        # self.scan_finished()

    def device_discovered(self, device_info):
        self.label.setText(f"Device found: {device_info.name()}")

    def scan_finished(self):
        print("scan_finished")
        self.label.setText("Scan finished.")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = BluetoothApp()
    window.show()
    sys.exit(app.exec())
