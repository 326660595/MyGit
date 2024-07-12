hex_value = 0xa800
byte_value = (hex_value >> 8) & 0xFF


print("a--",byte_value)

hex_string = format(byte_value, '02x')

print(hex_string)
