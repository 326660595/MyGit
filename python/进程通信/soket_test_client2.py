import socket
import threading
import uuid
import json
 
HOST = '127.0.0.1'
PORT = 8888
 
# 随机生成一个唯一 ID
UID = str(uuid.uuid4())
# 创建一个 TCP 协议的套接字对象
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 连接指定主机和端口
client_socket.connect((HOST, PORT))
 
# 将UID发送给服务端
client_socket.sendall(UID.encode('utf-8'))
 
 
def receive_message():
    while True:
        data = client_socket.recv(1024)
        if data:
            # 解析消息
            msg_dict = json.loads(data.decode('utf-8'))
            if 'sender_id' in msg_dict:
                sender_id = msg_dict['sender_id']
                message = msg_dict['message']
                print(f"{sender_id}: {message}")
            elif 'error' in msg_dict:
                error = msg_dict['error']
                print(f"Error: {error}")
 
        else:
            # 服务端关闭了连接
            print('服务器已下线...')
            break
 
    # 关闭客户端连接
    client_socket.close()
 
 
def send_message(receiver_id):
    while True:
        message = input()
 
        # 构造消息字典
        msg_dict = {
            'sender_id': UID,
            'receiver_id': receiver_id,
            'message': message
        }
 
        # 将消息字典序列化为JSON格式字符串
        json_str = json.dumps(msg_dict)
 
        # 将消息发送给服务端
        client_socket.sendall(json_str.encode('utf-8'))
 
 
if __name__ == '__main__':
    print(f'你的ID: {UID}')
    receiver_id = input('输入对方的ID接收对方消息或者输入"all"接收广播消息: ')
 
    # 启动接收消息的线程
    t1 = threading.Thread(target=receive_message)
    t1.daemon = True
    t1.start()
 
    # 启动发送消息的线程
    t2 = threading.Thread(target=send_message, args=(receiver_id,))
    t2.daemon = True
    t2.start()
 
    # 等待发送线程结束，结束接收线程
    t2.join()
    t1.join()