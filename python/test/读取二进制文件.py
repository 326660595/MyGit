
# file_name = "C:\\Users\\l3266\\Downloads\\TACW2266788G0001.bin"
# file_name = "C:\\Users\\l3266\\Desktop\\TACW7412345G0001.bin"
# file_name = "/home/russell/work/DC/bf/charger_number_example/TAS121CN40124011.bin"
file_name = "/home/russell/work/DC/bf/charger_number_example/THPP00222211222.bin"
# 54485050303032323232313132323200000000000000000000000000000000009d6f011f2d19ab2d437d2d9eb22d3eb23be4cce3000000000000000000000000e2f4ca3400

with open(file_name, 'rb') as file:
    binary_data = file.read()

# print(binary_data)

hex_data = binary_data.hex()
print(hex_data)

# ee96e2142d5aa82d417d2dacbe2d8a4bb48dbc7d

# 544153313231434e343031323430313100000000000000000000000000000000cad1a3f12dda272d4c8d2d85232d7f6a34cb9b3d00000000000000000000000088040d2f00

# 要将十六进制（hex）字符串转换为ASCII码，我们需要将每两个十六进制数字转换为对应的ASCII字符。下面是您提供的十六进制字符串转换为ASCII码的过程：

# 十六进制字符串：544153313231434e343031323430313100000000000000000000000000000000cad1a3f12dda272d4c8d2d85232d7f6a34cb9b3d00000000000000000000000088040d2f00

# 转换为ASCII码：

#     54 -> T

#     41 -> A

#     53 -> S

#     31 -> 1

#     32 -> 2

#     31 -> 1

#     34 -> 4

#     34 -> 4

#     6e -> n

#     34 -> 4

#     30 -> 0

#     31 -> 1

#     32 -> 2

#     34 -> 4

#     30 -> 0

#     31 -> 1

#     00 -> (空字符)

#     之后的一串 00 都是空字符，直到遇到非零的十六进制数。

#     cad1a3f12dda272d4c8d2d85232d7f6a34cb9b3d 这部分是十六进制数，但没有对应的ASCII字符，它们看起来像是一个文件的MD5校验码或者是某种二进制数据。

#     00000000000000000000000088040d2f00 这部分的 88040d2f00 转换为ASCII码是：
#         88 -> X
#         04 -> `` (这是一个不可打印的控制字符)
#         0d -> `` (回车符)
#         2f -> /
#         00 -> (空字符)

# 因此，转换结果为：TAS1214n40401... 后面跟着一串空字符，然后是 X/。由于十六进制字符串中包含不可打印的控制字符和可能的二进制数据，所以转换结果中包含一些无法显示的字符和乱码。