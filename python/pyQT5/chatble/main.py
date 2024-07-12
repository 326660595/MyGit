from PyQt5 import QtWidgets, uic
from PyQt5 import QtBluetooth
from PyQt5.QtCore import Qt, QIODevice, QByteArray

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()

        uic.loadUi('C:\\code\\MyGit\\python\\pyQT5\\chatble\\mainWindow.ui', self)

        self.scanButton.clicked.connect(self.scan)

        self.agent = QtBluetooth.QBluetoothDeviceDiscoveryAgent()
        self.agent.deviceDiscovered.connect(self.deviceDiscovered)

        self.controller = None
        self.service = None

    def scan(self):
        self.agent.start()

    def deviceDiscovered(self, device):
        item = QtWidgets.QListWidgetItem(device.name() + " [" + device.address().toString() + "]")
        self.listWidget.addItem(item)
        item.setData(Qt.UserRole, device)
        self.listWidget.itemDoubleClicked.connect(self.connectToDevice)

    def connectToDevice(self, item):
        device = item.data(Qt.UserRole)
        self.controller = QtBluetooth.QLowEnergyController.createCentral(device)
        self.controller.connected.connect(self.onConnected)
        self.controller.disconnected.connect(self.onDisconnected)
        self.controller.serviceDiscovered.connect(self.serviceDiscovered)
        self.controller.error.connect(self.onError)
        self.controller.connectToDevice()

    def onConnected(self):
        print("Connected to BLE device.")
        self.controller.discoverServices()

    def onDisconnected(self):
        print("Disconnected from BLE device.")

    def serviceDiscovered(self, uuid):
        service = self.controller.createServiceObject(uuid)
        self.service = service
        self.service.stateChanged.connect(self.onServiceStateChanged)
        self.service.characteristicChanged.connect(self.onCharacteristicChanged)
        self.service.characteristicWritten.connect(self.onCharacteristicWritten)
        self.service.characteristicRead.connect(self.onCharacteristicRead)
        self.service.enableNotifications(True)

    def onError(self, error):
        print("Error:", error)

    def onServiceStateChanged(self, newState):
        if newState == QtBluetooth.QLowEnergyService.ServiceDiscovered:
            print("Service discovered")

    def onCharacteristicChanged(self, characteristic, newValue):
        print("Characteristic value changed:", newValue)

    def onCharacteristicWritten(self, characteristic, newValue):
        print("Characteristic value written:", newValue)

    def onCharacteristicRead(self, characteristic, value):
        print("Characteristic value read:", value)

if __name__ == "__main__":
    app = QtWidgets.QApplication([])
    window = MainWindow()
    window.show()
    app.exec()
