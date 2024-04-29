import asyncio
from bleak import BleakScanner
from bleak import BleakClient


find_ble_name = "TACW2243223T0001"
# 设备MAC地址或UUID，根据实际情况替换
# TARGET_DEVICE_ADDRESS = "C9:2B:AF:90:38:16"
TARGET_DEVICE_ADDRESS = ""

received_message = b""  # 初始化接收的消息为空字节串

async def scan():
    global find_ble_name
    global TARGET_DEVICE_ADDRESS
    #设置扫描时间为3s
    devices = await BleakScanner.discover(timeout=3)
    for device in devices:
        #检查蓝牙名
        if find_ble_name == device.name:
            print(f"Name: {device.name}, MAC Address: {device.address}")
            TARGET_DEVICE_ADDRESS = device.address
            #打印蓝牙广播包信息
            print("Advertisement data:", device._metadata)
            # break



def handle_notification(sender, data):
    global received_message  # 使用全局变量
    received_message += data  # 将接收到的数据追加到已接收消息中
    print(f"Received notification from {sender}: {data.hex()}")

async def scan_and_connect():
    global received_message
    scanner = BleakScanner()
    print("Scanning for BLE devices...")
    await scanner.start()
    # send_data_ble = [0xfe, 0xb1, 0x00, 0x00, 0x24, 0x00, 0xa5, 0x4f, 0xd7, 0x62, 0xa2, 0xe4, 0x19, 0x28, 0x12, 0x0a, 0x0e, 0xfe, 0x33, 0x13, 0xa0, 0xd0, 0xe6, 0xa2, 0x55, 0x2f, 0x1a, 0x52, 0x3a, 0x41, 0xa0, 0x9d, 0xc4, 0xca, 0xae, 0x43, 0x21, 0x55, 0xb2, 0xe0, 0x8a, 0x9e, 0x39, 0x23]
    send_data_ble = [0xfe, 0xfe, 0x00, 0x00, 0x32, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x67, 0xaf, 0x6c, 0xc4, 
                     0x7c, 0xb7, 0x99, 0x27, 0xfe, 0xb1, 0x39, 0x80, 0x2a, 0xba, 0xb4, 
                     0x8f, 0x7f, 0x23, 0x48, 0x08, 0x1b, 0x54, 0x13, 0xe1, 0xa8, 0x76, 
                     0xd5, 0x6b, 0xd0, 0x19, 0xc7, 0xbf, 0x30, 0xe9, 0x25, 0x72, 0xa2, 
                     0x0e, 0xe1, 0x2e, 0x7f, 0x1c, 0x92, 0x01, 0xcd, 0xba, 0x10, 0x1d]
    try:
        device = await scanner.find_device_by_address(TARGET_DEVICE_ADDRESS)
        if device is not None:
            print(f"Found target device: {device.name} ({TARGET_DEVICE_ADDRESS})")
            async with BleakClient(device.address) as client:
                print("Connected to device.")
                
                # 发送消息示例
                message_to_send = bytes(send_data_ble)
                await client.write_gatt_char("0000fff3-0000-1000-8000-00805f9b34fb", message_to_send)
                print(f"Sent message: {message_to_send}")

                # 接收消息示例
                notification_uuid = "0000fff4-0000-1000-8000-00805f9b34fb"
                await client.start_notify(notification_uuid, handle_notification)
                await asyncio.sleep(1)
                print(f"received_message:{received_message.hex()}")

                while True:
                    await asyncio.sleep(1)

        else:
            print(f"Target device ({TARGET_DEVICE_ADDRESS}) not found.")

    finally:
        await scanner.stop()

asyncio.run(scan())


asyncio.run(scan_and_connect())




