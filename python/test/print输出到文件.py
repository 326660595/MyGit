import  os
import sys
temp = sys.stdout
f = open('test.txt','w')
print('1111111111')  # 打印到终端
 
# 之后使用print函数，都将内容打印到test.txt 文件中
sys.stdout = f 
print('222222222')  # 打印到文件中
 
# 恢复print函数打印到终端上
sys.stdout = temp
print('333333333')  # 打印到终端
f.close()
