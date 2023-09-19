import sys
# from PyQt6.QtCore import QBluetoothDeviceDiscoveryAgent, QBluetoothDeviceInfo, QBluetoothSocket
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6 import QtCore
from PyQt6.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothDeviceInfo, QBluetoothSocket

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # 创建设备发现代理对象
        self.discovery_agent = QBluetoothDeviceDiscoveryAgent()
        self.discovery_agent.deviceDiscovered.connect(self.device_discovered)
        
        # 开始设备发现
        self.discovery_agent.start()
        
    def device_discovered(self, device_info: QBluetoothDeviceInfo):
        print("Discovered device:", device_info.name())
        
        # 连接到蓝牙设备
        socket = QBluetoothSocket(QBluetoothSocket.Protocol.Rfcomm)
        socket.connectToService(device_info.address(), device_info.deviceUuid())
        
        if socket.state() == QBluetoothSocket.SocketState.ConnectedState:
            print("Connected to device:", device_info.name())
            # 在这里可以进行进一步的蓝牙通信操作
        else:
            print("Failed to connect to device:", device_info.name())

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
