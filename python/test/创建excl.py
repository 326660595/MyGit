import openpyxl

# 创建一个新的工作簿
workbook = openpyxl.Workbook()

# 选择默认的工作表
sheet = workbook.active

# 在第一列的第二行（B2）设置值为 "aaa"
sheet['A2'] = "aaa"

# 保存工作簿到指定文件
workbook.save("example.xlsx")
