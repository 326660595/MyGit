
#比较文件是不是一样
def compare_hex_files(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        if f1.read() == f2.read():
            print("Files are the same.")
        else:
            print("Files are different.")

#比较打印那几行不一样
def compare_files(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        lines1 = f1.readlines()
        lines2 = f2.readlines()

    for i, (line1, line2) in enumerate(zip(lines1, lines2)):
        if line1 != line2:
            print(f"Line {i + 1} is different:")
            print(f"{file1}: {line1.strip()}")
            print(f"{file2}: {line2.strip()}")
            print()

file1 = 'NovaX_P.hex'
file2 = 'NovaX_P (1).hex'

#   16:00         135674 NovaX_P (2).hex
# -a----          2023/7/7     16:00         135674 NovaX_P (3).hex

compare_hex_files(file1, file2)
compare_files(file1, file2)

print("程序执行完毕，按下回车键继续...")
input()
print("继续执行其他操作")

# NovaX_P.hex 1NovaX_P.hex 