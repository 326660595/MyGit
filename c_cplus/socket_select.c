#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>
#include <algorithm>
#include <csignal>
#include <atomic>

constexpr int BUF_LEN = 1024;
#define EXP_FD -1
#define ETHIP "10.100.16.43"//"192.168.42.10"

int main()
{
    // 创建监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == EXP_FD)
    {
        std::cerr << "listen socket not create." << std::endl;
        return -1;
    }

    // 绑定地址和端口
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(20000);


    /*TIME_WAIT 状态：
    当 TCP 连接关闭时，端口会进入 TIME_WAIT 状态，持续一段时间（通常是 2 分钟）。
    在这段时间内，端口无法被重新绑定。*/
    int opt = 1;
    //在绑定端口之前，设置 SO_REUSEADDR 选项，允许端口在 TIME_WAIT 状态下被重新绑定。
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        std::cerr << "设置 SO_REUSEADDR 失败: " << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    // 设置特定IP地址
    const char *bind_ip = ETHIP; // 替换为你的IP地址
    if (inet_pton(AF_INET, bind_ip, &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid IP address: " << bind_ip << std::endl;
        close(listenfd);
        return -1;
    }

    if (bind(listenfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "bind error: " << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    // 监听连接
    if (listen(listenfd, 3) == -1)
    {
        std::cerr << "listen error: " << strerror(errno) << std::endl;
        close(listenfd);
        return -1;
    }

    std::vector<int> cliFds;
    int maxfd;
    while (true)
    {
        fd_set recvSet;
        FD_ZERO(&recvSet);
        FD_SET(listenfd, &recvSet);
        maxfd = listenfd;

        // 添加客户端套接字到fd_set
        for (int i = 0; i < cliFds.size(); ++i)
        {
            if (cliFds[i] != EXP_FD)
            {
                FD_SET(cliFds[i], &recvSet);
                if (maxfd < cliFds[i])
                {
                    maxfd = cliFds[i];
                }
            }
        }

        // 设置超时时间
        timeval tmv;
        tmv.tv_sec = 2;
        tmv.tv_usec = 0;

        // 调用select
        int ret = select(maxfd + 1, &recvSet, NULL, NULL, &tmv);
        if (ret == -1)
        {
            if (errno == EINTR)
            {
                continue; // 忽略信号中断
            }
            std::cerr << "select error: " << strerror(errno) << std::endl;
            break;
        }
        else if (ret == 0)
        {
            std::cerr << "timeout!" << std::endl;
            continue;
        }

        // 处理新连接
        if (FD_ISSET(listenfd, &recvSet))
        {
            struct sockaddr_in cliaddr;
            socklen_t cliaddrlen = sizeof(cliaddr);
            int clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
            if (clifd == EXP_FD)
            {
                std::cerr << "accept error: " << strerror(errno) << std::endl;
                continue;
            }
            std::cout << "New client connected, fd: " << clifd << std::endl;
            cliFds.emplace_back(clifd);
        }

        // 处理客户端数据
        for (int i = 0; i < cliFds.size(); ++i)
        {
            if (cliFds[i] != EXP_FD && FD_ISSET(cliFds[i], &recvSet))
            {
                char recvbuf[BUF_LEN];
                memset(recvbuf, 0, sizeof(recvbuf));
                int count = recv(cliFds[i], recvbuf, BUF_LEN, 0);
                if (count <= 0)
                {
                    std::cout << "Client disconnected, fd: " << cliFds[i] << std::endl;
                    close(cliFds[i]);
                    cliFds[i] = EXP_FD;
                }
                else
                {
                    std::cout << "Received from fd " << cliFds[i] << ": " << recvbuf << std::endl;
                }
            }
        }
        std::string input = "aaaabbbccc";
        if (send(cliFds[0], input.c_str(), input.size(), 0) == -1) {
                            std::cerr << "发送消息失败，fd: " << cliFds[0] << "，错误: " << strerror(errno) << std::endl;
                        }

        // 清理无效套接字
        cliFds.erase(std::remove(cliFds.begin(), cliFds.end(), EXP_FD), cliFds.end());
        // cliFds.erase(0);
    }

    // 清理资源
    for (int fd : cliFds)
    {
        if (fd != EXP_FD)
        {
            close(fd);
        }
    }
    close(listenfd);
    return 0;
}