import asyncio
from bleak import BleakScanner
from bleak import BleakClient

# 设备MAC地址或UUID，根据实际情况替换
TARGET_DEVICE_ADDRESS = "C9:2B:AF:90:38:16"
received_message = b""  # 初始化接收的消息为空字节串

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


asyncio.run(scan_and_connect())

#log:

# PS C:\code\MyGit>  c:; cd 'c:\code\MyGit'; & 'c:\Users\l3266\AppData\Local\Programs\Python\Python310\python.exe' 'c:\Users\l3266\.vscode\extensions\ms-python.debugpy-2024.4.0-win32-x64\bundled\libs\debugpy\adapter/../..\debugpy\launcher' '64186' '--' 'C:\code\MyGit\python\blue_test\bleak_connect_and_rw_message.py' 
# Scanning for BLE devices...
# Found target device: TACW2243223T0001 (C9:2B:AF:90:38:16)
# Connected to device.
# Sent message: b"\xfe\xfe\x00\x002\x00\x00]\x00\x00\x00\x00\x00\x00\x00\x000\x00g\xafl\xc4|\xb7\x99'\xfe\xb19\x80*\xba\xb4\x8f\x7f#H\x08\x1bT\x13\xe1\xa8v\xd5k\xd0\x19\xc7\xbf0\xe9%r\xa2\x0e\xe1.\x7f\x1c\x92\x01\xcd\xba\x10\x1d"
# Received notification from 0000fff4-0000-1000-8000-00805f9b34fb (Handle: 13): Vendor specific: aafe000022000010000000000000000000544143
# Received notification from 0000fff4-0000-1000-8000-00805f9b34fb (Handle: 13): Vendor specific: 335a393131383930363731303234372323050601
# Received notification from 0000fff4-0000-1000-8000-00805f9b34fb (Handle: 13): Vendor specific: 030132d8bb72f9a13c27
# received_message:aafe000022000010000000000000000000544143335a393131383930363731303234372323050601030132d8bb72f9a13c27
# PS C:\code\MyGit> 




