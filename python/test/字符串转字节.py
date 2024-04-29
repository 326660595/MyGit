def string_to_hex_bytes(input_string):
    # 将字符串编码为字节序列
    bytes_sequence = input_string.encode("utf-8")
    
    # 将字节序列转换为16进制字符串
    hex_string = " ".join(["{:02x}".format(byte) for byte in bytes_sequence])
    
    return hex_string

# 输入字符串
input_string = "Z#ocpp16j000"

# 调用函数并打印结果
hex_bytes = string_to_hex_bytes(input_string)
print(hex_bytes)
