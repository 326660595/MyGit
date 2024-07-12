
file_name = "C:\\Users\\l3266\\Downloads\\TACW2266788G0001.bin"
# file_name = "C:\\Users\\l3266\\Desktop\\TACW7412345G0001.bin"

with open(file_name, 'rb') as file:
    binary_data = file.read()

# print(binary_data)

hex_data = binary_data.hex()
print(hex_data)

# ee96e2142d5aa82d417d2dacbe2d8a4bb48dbc7d