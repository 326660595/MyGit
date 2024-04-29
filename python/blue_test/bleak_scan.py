import asyncio
from bleak import BleakScanner

async def scan():
    find_ble_name = "TACW2243223T0001"
    #设置扫描时间为3s
    devices = await BleakScanner.discover(timeout=3)
    for device in devices:
        #检查蓝牙名
        if find_ble_name == device.name:
            print(f"Name: {device.name}, MAC Address: {device.address}")
            #打印蓝牙广播包信息
            print("Advertisement data:", device._metadata)
            # break



def main():   
    asyncio.run(scan())

main()

# log"
# Name: TACW2243223T0001, MAC Address: C9:2B:AF:90:38:16
# Advertisement data: {'uuids': [], 'manufacturer_data': {0: b'', 510: b'\x1f\xa8V'}}


