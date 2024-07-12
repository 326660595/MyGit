

def load_file_to_buffer(file_path):
    with open(file_path, 'r') as file:
        buf = file.read()
    return buf

# 用法示例
file_path = 'path/to/your/file.txt'  # 替换成你的本地文件路径
file_buffer = load_file_to_buffer(file_path)
print(file_buffer)
