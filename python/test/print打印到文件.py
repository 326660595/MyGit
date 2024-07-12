import sys

# # 打开一个文件以供写入
# with open('output.txt', 'w') as file:
#     sys.stdout = file
    
#     # 使用print输出到文件
#     print("aaaaaaaaaaa")
#     print("bbbbbbbbbbbbbb")
#     print("cccccccccccccccccc")

# # 恢复sys.stdout到默认值
# sys.stdout = sys.__stdout__

# 文件将在退出“with”块后自动关闭
 

a = "abb"

b = "ccc"

a = b+a

print(a)
