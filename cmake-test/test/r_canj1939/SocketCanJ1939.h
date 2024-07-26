//
// Created by Mask on 2022/5/16.
//

#ifndef SOCKETCANJ1939_H
#define SOCKETCANJ1939_H
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
#include <deque>

#define USE_SEND_CANJ1939_ADDR 0xf5
#define USE_SEND_CANJ1939_DEFAULT_RETRY 3
#define USE_CANJ1939_DEFAULT_TIMEOUT 250 // 250*1000
#define BCU_CAN_ADDR 0x80

struct canJ1939Data
{
    uint32_t timeoutMs = USE_CANJ1939_DEFAULT_TIMEOUT; // 发送超时，单位ms
    __u8 addr = USE_SEND_CANJ1939_ADDR;
    __u32 pgn;                                         // PGN（Parameter Group Number）
    int dlc;                                           // Data Length Code
    uint8_t *data;                                     // 可变长数组
    uint8_t ifSendFailRetry = USE_SEND_CANJ1939_DEFAULT_RETRY;

    // 构造函数
    canJ1939Data(__u32 pgn, int dlc, const uint8_t *initData = nullptr,
                    uint8_t ifSendFailRetry = USE_CANJ1939_DEFAULT_TIMEOUT,
                    uint32_t timeoutMs = USE_SEND_CANJ1939_DEFAULT_RETRY,
                    __u8 addr = USE_SEND_CANJ1939_ADDR)
        : pgn(pgn), dlc(dlc), ifSendFailRetry(ifSendFailRetry), timeoutMs(timeoutMs), addr(addr)
    {
        // 使用 memcpy 来初始化 data 数组，如果提供了 initData
        if ((dlc > 0) && (initData != nullptr))
        {
            data = new uint8_t[dlc];
            memcpy(data, initData, dlc);
        }
    }
    // 析构函数
    ~canJ1939Data()
    {
        // printf("delete data-\n");
        if (data != nullptr)
            delete[] data;
    }
};

class SocketCanJ1939
{
private:
    int sock;         // socket 套接字
    int sockW, sockR; // socket 套接字
    // struct sockaddr_can addr;
    struct sockaddr_can sockname, peername;
    socklen_t peernamelen;
    uint8_t dat[2046];

    uint32_t timeoutW = USE_CANJ1939_DEFAULT_TIMEOUT;
    uint32_t timeoutR = USE_CANJ1939_DEFAULT_TIMEOUT;

    unsigned int sendNum = 0; // 统计发送成功消息条数
    int todo_broadcast = 0;

    int valid_peername = 0;
    unsigned int todo_send = 0;
    int todo_recv = 0, todo_echo = 0, todo_prio = -1;
    int todo_connect = 0, todo_names = 0, todo_wait = 0, todo_rebind = 0;
    int no_bind = 0;

    std::string device;

    bool creatSockWrite(void);
    bool creatSockRead(void);

public:
    SocketCanJ1939();

    // 其他成员函数和私有成员
    std::deque<std::shared_ptr<canJ1939Data>> m_TxQueue;
    std::deque<std::shared_ptr<canJ1939Data>> m_RxQueue;

    bool Open(const std::string &device);
    void Close();

    bool setBroadcast(bool broadcastE);

    // 通过socket向内核j1939发送数据
    int sendData(__u8 addr, __u32 pgn, int dlc, const void *data);

    // 读取数据
    int readData(void);

    int setSendTimeOut(uint32_t sec_ms);
    int setReadTimeOut(uint32_t sec_ms);

    void sendCanJ1939Message(__u8 addr, uint32_t pgn, int dlc, const uint8_t *data, uint8_t ifSendFailRetry,
                             uint32_t timeoutMs);
    void getQueueSend(void);
    void readCanJ1939MessageToQueue(uint32_t pgn, int dlc, const uint8_t *data, __u8 addr);
    void readMessageQueue(void);
    virtual void recMessageHandler(__u8 addr, uint32_t pgn, int dlc, const uint8_t *data);
        
};

#endif // SOCKETCAN_SOCKETCAN_H
