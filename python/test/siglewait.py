import signal
import threading
import time

def signal_handler(signum, frame):
    """信号处理函数"""
    print('Received signal %d' % signum)

def wait_for_signal(signum):
    """等待信号的线程函数"""
    signal.sigwait([signum])

# 注册信号处理函数
signal.signal(signal.SIGINT, signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

# 创建等待信号的线程
signal_thread = threading.Thread(target=wait_for_signal, args=(signal.SIGINT,))
signal_thread.start()

# 主线程继续执行其他操作
while True:

    print('Doing something...')

