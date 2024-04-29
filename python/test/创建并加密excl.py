import openpyxl

# 创建一个新的 Excel 工作簿
workbook = openpyxl.Workbook()
worksheet = workbook.active

# 在工作表中添加一些数据
worksheet['A1'] = 'Name'
worksheet['B1'] = 'Age'
worksheet['A2'] = 'Alice'
worksheet['B2'] = 25
worksheet['A3'] = 'Bob'
worksheet['B3'] = 30

# 设置密码保护
password = "123"  # 将 "your_password" 替换为你想要设置的密码
workbook.security.set_workbook_password(password)

# 保存 Excel 文件
workbook.save('example.xlsx')
