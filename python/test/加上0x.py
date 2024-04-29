hex_string = "fefe00003200005d0000000000000000300067af6cc47cb79927feb139802abab48f7f2348081b5413e1a876d56bd019c7bf30e92572a20ee12e7f1c9201cdba101d"

# 将字符串切割为每两个字符的列表
hex_bytes = [hex_string[i:i+2] for i in range(0, len(hex_string), 2)]

# 添加"0x"前缀并以逗号分隔
formatted_bytes = [f"0x{byte}" for byte in hex_bytes]

# 将列表转换为字符串
formatted_string = ", ".join(formatted_bytes)

print(formatted_string)
