//
// Created by Mask on 2022/5/16.
//

#ifndef SOCKETCAN_SOCKETCAN_H
#define SOCKETCAN_SOCKETCAN_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/j1939.h>

class SocketCanJ1939
{
private:
    int sock; // socket 套接字
    int sockW,sockR; // socket 套接字
    // struct sockaddr_can addr;
    struct sockaddr_can sockname,peername;
    socklen_t peernamelen;
    uint8_t dat[2046];


    int valid_peername = 0;
    unsigned int todo_send = 0;
    int todo_recv = 0, todo_echo = 0, todo_prio = -1;
    int todo_connect = 0, todo_names = 0, todo_wait = 0, todo_rebind = 0;
    int todo_broadcast = 0, todo_promisc = 0;
    int no_bind = 0;

    std::string device;

    bool creatSockWrite(void);
    bool creatSockRead(void);

public:
    SocketCanJ1939();
    bool Open(const std::string &device);
    void Close();

    bool setBroadcast(bool broadcastE);

    // 通过socket向内核j1939发送数据
    int sendData(__u32 pgn, int dlc, const void *data);

    // 读取数据
    int readData(void);

    int setSendTimeOut(int sec, int sec_ms);
    int setReadTimeOut(int sec, int sec_ms);
};

#endif // SOCKETCAN_SOCKETCAN_H
