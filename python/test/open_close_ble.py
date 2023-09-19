import subprocess
import platform

def restart_bluetooth():
    if platform.system() == "Windows":
        # 关闭蓝牙
        subprocess.run(["net", "stop", "bthserv"])
        
        # 启动蓝牙
        subprocess.run(["net", "start", "bthserv"])
        
        print("Bluetooth restarted.")
    else:
        print("Unsupported operating system.")

# 重新启动蓝牙，调用这个函数
restart_bluetooth()


print("start sssss")
input()




























# 要在 Python 中打开和关闭 Windows 10 上的蓝牙，你可以使用 subprocess 模块运行一些系统命令。以下是示例代码：
# import subprocess
# import time

# def enable_bluetooth():
#     # 执行打开蓝牙的命令
#     subprocess.run('reg add HKLM\SYSTEM\CurrentControlSet\Services\BthEnum /v Start /t REG_DWORD /d 3 /f', shell=True)
#     subprocess.run('reg add HKLM\SYSTEM\CurrentControlSet\Services\BthHfAudiotGatewayService /v Start /t REG_DWORD /d 3 /f', shell=True)
#     subprocess.run('reg add HKLM\SYSTEM\CurrentControlSet\Services\BthAvctpSvc /v Start /t REG_DWORD /d 3 /f', shell=True)
#     subprocess.run('net start bthserv', shell=True)

# def disable_bluetooth():
#     # 执行关闭蓝牙的命令
#     subprocess.run('reg add HKLM\SYSTEM\CurrentControlSet\Services\BthEnum /v Start /t REG_DWORD /d 4 /f', shell=True)
#     subprocess.run('reg add HKLM\SYSTEM\CurrentControlSet\Services\BthHfAudiotGatewayService /v Start /t REG_DWORD /d 4 /f', shell=True)
#     subprocess.run('reg add HKLM\SYSTEM\CurrentControlSet\Services\BthAvctpSvc /v Start /t REG_DWORD /d 4 /f', shell=True)
#     subprocess.run('net stop bthserv', shell=True)

# # 打开蓝牙
# enable_bluetooth()

# # 暂停一段时间，让蓝牙启动
# # 可根据实际情况进行调整，保证蓝牙完全启动
# time.sleep(5)

# # 关闭蓝牙
# disable_bluetooth()

# 上述代码定义了两个函数 enable_bluetooth() 和 disable_bluetooth()，分别用于启用和禁用蓝牙。这些函数使用 subprocess.run() 方法来运行系统命令。
# 在 enable_bluetooth() 中，使用了一系列的命令来修改 Windows 注册表 (reg)，并启动 Bluetooth 相关的服务 (net start bthserv)，以打开蓝牙。
# 在 disable_bluetooth() 中，使用了相应的命令来修改注册表和停止 Bluetooth 服务 (net stop bthserv)，以关闭蓝牙。
# 请注意，修改注册表需要管理员权限，因此建议以管理员权限运行 Python 脚本。此外，关闭蓝牙后，可能需要一段时间进行反应和关闭。
# 在使用此代码时，请确保你以管理员权限运行 Python 环境。此外，还可能需要在代码中适当地延长启动和关闭之间的等待时间，以确保蓝牙服务完全启动或关闭。