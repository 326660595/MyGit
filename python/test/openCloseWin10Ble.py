import pyautogui
import time
#pyautogui使用例子

# 打开蓝牙
def enable_bluetooth():
    pyautogui.hotkey("win", "i")  # 打开 Windows 设置
    time.sleep(2)  # 等待设置窗口打开
    pyautogui.write("Bluetooth")  # 输入 Bluetooth
    time.sleep(2)  # 等待搜索结果
    pyautogui.press("down")
    pyautogui.press("down")
    time.sleep(1)
    pyautogui.press("enter")  # 进入蓝牙设置
    time.sleep(2)  # 等待蓝牙设置窗口打开
    # pyautogui.press("tab")  # 移动焦点到蓝牙开关
    pyautogui.press("space")  # 切换蓝牙开关状态
    time.sleep(2)  # 等待操作完成
    pyautogui.hotkey("alt", "f4")  # 关闭窗口

# 关闭蓝牙
def disable_bluetooth():
    pyautogui.hotkey("win", "i")  # 打开 Windows 设置
    time.sleep(2)  # 等待设置窗口打开
    pyautogui.write("Bluetooth")  # 输入 Bluetooth
    time.sleep(2)  # 等待搜索结果
    pyautogui.press("enter")  # 进入蓝牙设置
    time.sleep(2)  # 等待蓝牙设置窗口打开
    pyautogui.press("tab")  # 移动焦点到蓝牙开关
    pyautogui.press("space")  # 切换蓝牙开关状态
    time.sleep(2)  # 等待操作完成
    pyautogui.hotkey("alt", "f4")  # 关闭窗口

# 打开蓝牙
enable_bluetooth()
# 等待片刻
time.sleep(5)
# 关闭蓝牙
disable_bluetooth()
