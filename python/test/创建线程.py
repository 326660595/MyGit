import threading

# 定义一个函数，作为线程的执行体
def print_numbers():
    for i in range(1, 6):
        print(f"Number {i}")

def print_letters():
    for letter in 'abcde':
        print(f"Letter {letter}")

# 创建两个线程
thread1 = threading.Thread(target=print_numbers)
thread2 = threading.Thread(target=print_letters)

# 启动线程
thread1.start()
thread2.start()

# 等待两个线程完成
thread1.join()
thread2.join()

print("Both threads have finished.")
