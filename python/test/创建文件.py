from datetime import datetime
import os

current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")

def creat_log_file():
    # 获取当前时间并格式化为字符串
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")

    # 创建文件名
    filename = current_time + '.txt'

    # 使用 'x' 参数打开文件，以便在文件已经存在的情况下抛出异常
    try:
        with open(filename, 'x') as f:
            print('File created successfully')
    except FileExistsError:
        print('File already exists')


def text_create(name, msg):
    desktop_path = ""  # 新创建的txt文件的存放路径
    full_path = desktop_path + name + '.txt'  # 也可以创建一个.doc的word文档
    file = open(full_path, 'w')
    file.write(msg)   #msg也就是下面的Hello world!
    # file.close()


import subprocess

def out_print():
    # 调用 Python 脚本并捕获输出
    command = ['python', 'test_bin\\ppt.py']
    output = subprocess.check_output(command, text=True)

    filename = current_time + '.txt'
    # 写入输出到 txt 文件
    with open(filename, 'w') as f:
        f.write(output)

 
if __name__ == '__main__':
    # text_create('mytxtfile', 'Hello world!')
    # 调用函数创建一个名为mytxtfile的.txt文件，并向其写入Hello world!


    # creat_log_file()
    out_print()