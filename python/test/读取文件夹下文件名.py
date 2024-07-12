import os
import queue

def get_files_in_folder(folder_path):
    file_queue = queue.Queue()

    # 遍历文件夹中的所有文件
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            file_queue.put(file_path)

    return file_queue

# 使用示例
folder_path = 'win_bat'  # 替换为你的文件夹路径
files_queue = get_files_in_folder(folder_path)

# 打印队列中的文件路径
while not files_queue.empty():
    file_path = files_queue.get()
    print(file_path)
