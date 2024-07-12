import asyncio

async def wait_for_60_seconds():
    print("开始等待60秒...")
    await asyncio.sleep(60)
    print("等待60秒结束！")

# 创建一个事件循环
loop = asyncio.get_event_loop()

# 使用事件循环运行异步函数
loop.run_until_complete(wait_for_60_seconds())

# 关闭事件循环
loop.close()
