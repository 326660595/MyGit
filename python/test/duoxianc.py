import threading
import time

def ddd():
    print(":ddd")
    time.sleep(3)
    print("d3")


def main():
    print("start ocpp main")
    # 创建一个新线程来处理 auto_upload 方法
    upload_thread = threading.Thread(target=ddd)
    upload_thread.start()
    # 主线程继续执行其他任务
    print("Doing other tasks in the main thread...")
    # 等待上传线程完成
    upload_thread.join()
    print("end")

main()