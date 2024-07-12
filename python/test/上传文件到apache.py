import ftplib  
import os
import requests 
# # 服务器信息  
# server_address = '20.167.40.51'  
# # server_address = 'http://20.167.40.51/russell_up/'
# username = 'Juno02'  
# password = 'Juno&123456789'  
# remote_directory = '/russell_up/'  
# #   python\test\config_log_check.xlsx
# # 本地文件路径  
# local_file_path = 'C:\\code\\MyGit\\python\\test\\config_log_check.xlsx' 

# os.system("scp C:\\code\\MyGit\\python\\test\\config_log_check.xlsx")
  
# # # 连接到FTP服务器  
# ftp = ftplib.FTP(server_address)  
# # ftp.login(username, password)  
# print(1)
# # 进入远程目录  
# ftp.cwd(remote_directory)  
# print(2)
# # 上传文件  
# with open(local_file_path, 'rb') as file:  
#     ftp.storbinary('STOR ' + os.path.basename(local_file_path), file)  
# print(3)
# # 关闭FTP连接  
# ftp.quit()

 
  
# 服务器地址  
# server_address = 'http://example.com'  
  
# 文件路径  
# local_file_path = '/path/to/local/file.txt'  
  
# # 构建上传请求的URL  
# upload_url = server_address
  
# # 读取本地文件内容  
# with open(local_file_path, 'rb') as file:  
#     file_content = file.read()  
  
# # 发送文件上传请求  
# response = requests.post(upload_url, data=file_content)  
  
# # 检查响应状态码  
# if response.status_code == 200:  
#     print('文件上传成功！')  
# else:  
#     print('文件上传失败，状态码：', response.status_code)


import paramiko  
from scp import SCPClient

# # 创建SSH客户端  
# ssh = paramiko.SSHClient()  
# ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())  
# ssh.connect('20.167.40.51', username='Juno02', password='Juno&123456789')  
  
# # 创建SCP客户端  
# scp = SCP.Client(ssh.get_transport())  
  
# 上传本地文件到远程主机  
local_file_path = 'C:\\code\\MyGit\\python\\test\\config_log_check.xlsx' 
remote_file_path = '/var/www/html/russell_up/config_log_check.xlsx'  
# scp.put(local_file_path, remote_file_path)  
  
# # # 下载远程文件到本地主机  
# # remote_file_path = '/path/to/remote/file.txt'  
# # local_file_path = '/path/to/local/directory/file.txt'  
# # scp.get(remote_file_path, local_file_path)  
  
# # 关闭SCP客户端和SSH客户端连接  
# scp.close()  
# ssh.close()
host = '20.167.40.51'
port = 22
username = 'Juno02'
ssh_client = paramiko.SSHClient()
password = 'Juno&123456789'
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy)
ssh_client.connect(host, port, username, password)
scpclient = SCPClient(ssh_client.get_transport(),socket_timeout=15.0)
local_path = local_file_path
try:
    scpclient.put(local_path, remote_file_path)
except FileNotFoundError as e:
    print(e)
    print("系统找不到指定文件" + local_path)
else:
    print("文件上传成功")
ssh_client.close()






