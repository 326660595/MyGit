#打印蓝牙特征值

import asyncio
from bleak import BleakClient

async def print_characteristics(address):
    async with BleakClient(address) as client:
        services = await client.get_services()
        for service in services:
            print(f"Service UUID: {service.uuid}")
            for characteristic in service.characteristics:
                print(f"  Characteristic UUID: {characteristic.uuid}")
                # 可能还可以打印更多特征值的信息，例如权限等

if __name__ == "__main__":
    address = "C9:2B:AF:90:38:16"  # 你的蓝牙设备地址
    asyncio.run(print_characteristics(address))



# log
# C:\code\MyGit\python\blue_test\print_ble_characteristic.py:8: FutureWarning: This method will be removed future version, use the services property instead.
#   services = await client.get_services()
# Service UUID: 00001801-0000-1000-8000-00805f9b34fb
#   Characteristic UUID: 00002a05-0000-1000-8000-00805f9b34fb
# Service UUID: 00001800-0000-1000-8000-00805f9b34fb
#   Characteristic UUID: 00002a00-0000-1000-8000-00805f9b34fb
#   Characteristic UUID: 00002a01-0000-1000-8000-00805f9b34fb
#   Characteristic UUID: 00002a04-0000-1000-8000-00805f9b34fb
# Service UUID: 0000fff0-0000-1000-8000-00805f9b34fb
#   Characteristic UUID: 0000fff4-0000-1000-8000-00805f9b34fb
#   Characteristic UUID: 0000fff3-0000-1000-8000-00805f9b34fb
# Service UUID: 8a97f7c0-8506-11e3-baa7-0800200c9a66
#   Characteristic UUID: 122e8cc0-8508-11e3-baa7-0800200c9a66
#   Characteristic UUID: 210f99f0-8508-11e3-baa7-0800200c9a66
#   Characteristic UUID: 2691aa80-8508-11e3-baa7-0800200c9a66
#   Characteristic UUID: 2bdc5760-8508-11e3-baa7-0800200c9a66