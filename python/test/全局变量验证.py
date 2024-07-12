 
a=1
b = None
 
def good():         #定义一个good函数,自定义函数内部的是局部变量
    global a
    a =2             #局部变量a=2
    print(a)        #print结果是2

    openDoor_send = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
    global b
    b = openDoor_send
    print(b)

good()              #调用good()函数
print(a)            #print结果是1

print(b)
openDoor_send1 = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff]
b = openDoor_send1
print(b)