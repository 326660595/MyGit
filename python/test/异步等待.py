import asyncio

async def wait_for_three_seconds():
    await asyncio.sleep(3)
    print("Three seconds have passed.")

async def main():
    print("Start")
    await wait_for_three_seconds()
    print("End")

async def test():  # 将test()函数改为异步函数
    print("hello world")
    await main()  # 使用await来等待main()协程完成
    print("next")
    await wait_for_three_seconds()  # 使用await来等待wait_for_three_seconds()协程完成
    print("end---")

asyncio.run(test())  # 使用asyncio.run()来运行异步函数
