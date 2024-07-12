import subprocess

# 执行命令以同步网络时间
subprocess.run(["w32tm", "/resync"], capture_output=True, text=True)
