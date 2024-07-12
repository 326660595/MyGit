import threading

def delayed_function():
    print("This function will be delayed by 3 seconds.")

def main_function():
    print("Start of the program.")
    
    # 创建一个延时为3秒的定时器，并调用delayed_function函数
    timer = threading.Timer(3, delayed_function)
    timer.start()

    print("Main program continues to run.")

if __name__ == "__main__":
    main_function()
