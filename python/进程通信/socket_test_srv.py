import socket
import threading
import json
 
HOST = '127.0.0.1'
PORT = 8888
 
# 存储客户端的 uid 和 socket 对象的映射关系
clients = {}
 
# 创建一个 TCP 协议的套接字对象
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 绑定并监听一个指定的地址和端口号
server_socket.bind((HOST, PORT))
# 开始监听客户端对指定 IP 地址和端口号的连接请求,当有客户端发送连接请求时，
# 服务端可以接受客户端连接，并创建一个新的套接字对象以处理客户端与服务端之间的通信。
server_socket.listen()
 
def handle_client(client_socket, client_address):
    uid = client_socket.recv(1024).decode('utf-8')
    print('uid:{}已上线'.format(uid))
    clients[uid] = client_socket
 
    while True:
        try:
            data = client_socket.recv(1024)
            if data:
                # 解析消息
                msg_dict = json.loads(data.decode('utf-8'))
                sender_id = msg_dict['sender_id']
                receiver_id = msg_dict['receiver_id']
                message = msg_dict['message']
                print('用户 {} 发送给用户 {} 的消息: {}'.format(sender_id, receiver_id, message))
 
                if receiver_id == 'all':
                    # 广播消息给所有客户端
                    for uid, client in clients.items():
                        if uid != sender_id:
                            client.sendall(data)
                elif receiver_id in clients and receiver_id != sender_id:
                    # 发送消息给指定客户端
                    client_socket = clients[receiver_id]
                    client_socket.sendall(data)
                else:
                    # 接收到的消息有误，回复错误信息
                    error = {
                        '错误': f'对方ID无效: {receiver_id}'
                    }
                    client_socket.sendall(json.dumps(error).encode('utf-8'))
            else:
                # 客户端关闭了连接
                print('客户端关闭了连接')
                break
        except:
            # 发送和接收消息时出现异常，可能是客户端关闭了连接
            print('发送和接收消息时出现异常，可能是客户端关闭了连接')
            break
 
    # 移除客户端连接
    print('用户:{}已离线'.format(uid))
    del clients[uid]
 
 
    # 关闭客户端连接
    client_socket.close()
 
if __name__ == '__main__':
    print(f'Server listening on {HOST}:{PORT}')
 
    while True:
        client_socket, client_address = server_socket.accept()
        print(f'{client_address[0]}:{client_address[1]} connected')
 
        # 生成客户端 UID，并存储客户端的 socket 对象和 UID 的映射关系
        thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
        thread.daemon = True
        thread.start()