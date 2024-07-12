import sys  
from PyQt6.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton  
from PyQt6.QtBluetooth import QBluetoothDeviceDiscoveryAgent, QBluetoothConnectionConfiguration, QBluetoothHostInfo, QBluetoothServiceInfo  
  
class BluetoothConnection(QWidget):  
    def __init__(self):  
        super().__init__()  
        self.initUI()  
  
    def initUI(self):  
        self.setWindowTitle('PyQt6 Bluetooth Connection')  
        self.setGeometry(300, 300, 300, 150)  
  
        # Create a label to display a message  
        self.label = QLabel(self)  
        self.label.setGeometry(50, 50, 200, 20)  
  
        # Create a button to start the bluetooth connection process  
        self.connectButton = QPushButton('Connect', self)  
        self.connectButton.setGeometry(50, 100, 100, 30)  
        self.connectButton.clicked.connect(self.connect)  
  
        # Create a line edit to display the bluetooth address of the device to connect to  
        self.deviceLineEdit = QLineEdit(self)  
        self.deviceLineEdit.setGeometry(50, 150, 150, 30)  
  
        # Initialize the bluetooth device discovery agent  
        self.discoveryAgent = QBluetoothDeviceDiscoveryAgent()  
        self.discoveryAgent.setHostMode(QBluetoothDeviceDiscoveryAgent.ActiveHostMode)  
  
        # Start the device discovery process  
        self.discoveryAgent.discoverDevices()  
  
        # Display the message "Searching for bluetooth devices..." in the label until the device discovery process is complete  
        self.label.setText('Searching for bluetooth devices...')  
        self.label.show()  
  
    def connect(self):  
        # Get the bluetooth address of the device to connect to from the line edit  
        address = self.deviceLineEdit.text()  
  
        # Get the bluetooth device information from the discovery agent  
        devices = self.discoveryAgent.discoveredDevices()  
        for device in devices:  
            if device.address().toString() == address:  
                # Set up the connection configuration for the device  
                configuration = QBluetoothConnectionConfiguration()  
                configuration.setRemoteHost(QBluetoothHostInfo(device.address()))  
                configuration.setRemoteService(QBluetoothServiceInfo(device.serviceRecord(0)))  
                configuration.setRemoteServiceType(QBluetoothServiceInfo.RfcommProtocol)  
                configuration.setLocalServiceType(QBluetoothServiceInfo.RfcommProtocol)  
                configuration.setLocalServicePort(1)  
                configuration.setRemoteServicePort(2)  
                configuration.setEncryptionEnabled(False)  
                configuration.setAuthenticationEnabled(False)  
                configuration.setHostMode(QBluetoothDeviceDiscoveryAgent.ActiveHostMode)  
  
                # Establish the bluetooth connection with the device using the connection configuration  
                connection = QBluetoothConnection(configuration)  
                if connection.state() == QBluetoothConnectionManager.ConnectedState:  
                    # Connection successful, display the message "Connected to device" in the label and disable the connect button  
                    self.label.setText('Connected to device')  
                    self.label.show()  
                    self.connectButton.setEnabled(False)  
                else:  
                    # Connection failed, display the message "Failed to connect to device" in the label and enable the connect button again  
                    self.label.setText('Failed to connect to device')