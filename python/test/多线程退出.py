import threading
import signal

def signal_handler(sig, frame):
    print("Ctrl + C 被捕获，准备退出...")
    global exit_flag
    exit_flag = True

def worker_function():
    while not exit_flag:
        # 在这里执行线程的工作逻辑
        pass

exit_flag = False

# 注册信号处理程序
signal.signal(signal.SIGINT, signal_handler)

# 创建多个线程
num_threads = 5
threads = []
for _ in range(num_threads):
    thread = threading.Thread(target=worker_function)
    thread.start()
    threads.append(thread)

# 等待所有线程完成
for thread in threads:
    thread.join()

print("所有线程已退出，程序正常终止。")
