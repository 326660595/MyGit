from bluepy.btle import Scanner, DefaultDelegate

# 自定义扫描结果处理代理类
class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if isNewDev:
            print("发现新设备:", dev.addr)

# 创建扫描器对象和代理对象
scanner = Scanner().withDelegate(ScanDelegate())

# 扫描BLE设备
devices = scanner.scan(10.0)  # 扫描10秒

# 打印扫描到的设备信息
for device in devices:
    print("设备名:", device.getValueText(8))  # 获取设备名称
    print("MAC地址:", device.addr)  # 获取设备MAC地址
    print("信号强度:", device.rssi)  # 获取信号强度
    print("")

# 连接到指定MAC地址的BLE设备
device_address = "00:11:22:33:44:55"  # 替换成你要连接的设备的MAC地址
device = scanner.getDevice(device_address)
if device is not None:
    print("连接到设备:", device.addr)
    # 在这里执行与设备的交互操作，例如读写特征值、订阅通知等
else:
    print("无法找到设备:", device_address)
