//
// Created by Mask on 2022/5/16.
//

#include "SocketCanJ1939.h"
// #include "can_message.h"
#include <thread>
#include <cstring>

SocketCanJ1939::SocketCanJ1939()
{
    printf("creat canj1939\n");
}

bool SocketCanJ1939::Open(const std::string &device)
{
    bool ret;
    SocketCanJ1939::device = device;
    ret = SocketCanJ1939::creatSockWrite();
    ret = SocketCanJ1939::creatSockRead();
    return ret;
}

bool SocketCanJ1939::creatSockWrite(void)
{
    int ret;
    sockW = ::socket(PF_CAN, SOCK_DGRAM, CAN_J1939);
    if (sockW < 0)
    {
        printf("create socket err\n");
        return false;
    }
    if (sockW != -1)
    {
        do
        {
            // 设置过滤规则
            //   setsockopt(sockW, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
            // 设置回环功能
            // int loopback = 0; // 0 表示关闭, 1 表示开启( 默认)
            // ret = setsockopt(sockW, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback));
            // if (ret < 0)
            // {
            //     close(sockW);
            //     sockW = -1;
            //     break;
            // }

            sockname.can_family = AF_CAN;
            sockname.can_ifindex = if_nametoindex(device.c_str());
            sockname.can_addr.j1939.addr = 0x80;
            sockname.can_addr.j1939.name = J1939_NO_NAME;
            sockname.can_addr.j1939.pgn = 0x0100;

            // 设置广播模式
            todo_broadcast = 1;
            if (todo_broadcast)
            {
                printf("todo_broadcast --\n");
                ret = setsockopt(sockW, SOL_SOCKET, SO_BROADCAST,
                                 &todo_broadcast, sizeof(todo_broadcast));
                if (ret < 0)
                    printf("setsockopt: filed to set broadcast");
            }

            // sockname.can_family = AF_CAN;
            // // sockname.can_ifindex = if_nametoindex("can0");
            // sockname.can_ifindex = if_nametoindex(device.c_str());
            // sockname.can_addr.j1939.addr = J1939_NO_ADDR;
            // sockname.can_addr.j1939.name = J1939_NO_NAME;
            // sockname.can_addr.j1939.pgn = J1939_NO_PGN;

            // peername.can_family = AF_CAN;
            // peername.can_addr.j1939.addr = 0xff;
            // peername.can_addr.j1939.name = J1939_NO_NAME;
            // peername.can_addr.j1939.pgn = J1939_NO_PGN;
            // 将套接字与can0绑定
            ret = bind(sockW, (struct sockaddr *)&sockname, sizeof(sockname));
            if (ret < 0)
            {
                close(sockW);
                sockW = -1;
                break;
            }

        } while (0);
    }
    return true;
}

bool SocketCanJ1939::creatSockRead(void)
{
    int ret;
    sockR = ::socket(PF_CAN, SOCK_DGRAM, CAN_J1939);
    if (sockR < 0)
    {
        printf("create socket err\n");
        return false;
    }
    if (sockR != -1)
    {
        do
        {
            // 设置广播模式
            todo_broadcast = 1;
            if (todo_broadcast)
            {
                printf("todo_broadcast --\n");
                ret = setsockopt(sockR, SOL_SOCKET, SO_BROADCAST,
                                 &todo_broadcast, sizeof(todo_broadcast));
                if (ret < 0)
                    printf("setsockopt: filed to set broadcast");
            }

            struct sockaddr_can addr;
            addr.can_family = AF_CAN;
            // addr.can_ifindex = if_nametoindex("can0");
            addr.can_ifindex = if_nametoindex(device.c_str());
            addr.can_addr.j1939.addr = 0xf5; // J1939_NO_ADDR;
            addr.can_addr.j1939.name = J1939_NO_NAME;
            addr.can_addr.j1939.pgn = J1939_NO_PGN;

            // 将套接字与can0绑定
            ret = bind(sockR, (struct sockaddr *)&addr, sizeof(addr));
            if (ret < 0)
            {
                close(sockR);
                sockR = -1;
                printf("bind socket err\n");
                break;
            }

        } while (0);
    }

    return ret;
}

void SocketCanJ1939::Close()
{
    close(sockR);
    close(sockW);
}

// 通过socket向can总线发送数据
int SocketCanJ1939::sendData(__u32 pgn, int data_len, const void *data)
{
    // ::memcpy(dat, data, data_len);
    printf("sendData-%d\n", sendNum);
    // sockname.can_family = AF_CAN;
    // sockname.can_ifindex = if_nametoindex("can0");
    sockname.can_addr.j1939.addr = 0xf5; // 目标 CAN 设备的地址
    // sockname.can_addr.j1939.name = J1939_NO_NAME;
    sockname.can_addr.j1939.pgn = 0x0100;
    // russell:在这里发送数据
    // int ret = sendto(sockW, dat, data_len, 0,
    //                  (const struct sockaddr *)&sockname, sizeof(sockname));
    int ret = sendto(sockW, data, data_len, 0,
                     (const struct sockaddr *)&sockname, sizeof(sockname));
    if (ret < 0)
    {
        printf("sendData err, ret:%d\n", ret);
        return ret;
    }
    sendNum++;
    return ret;
}

// 将数据保存至缓冲区
int SocketCanJ1939::readData(void)
{
    int i, j, ret;
    peernamelen = sizeof(peername);
    printf("\nreadData:\n");
    peername.can_addr.j1939.addr = 0xff;
    peername.can_addr.j1939.name = J1939_NO_NAME;
    peername.can_addr.j1939.pgn = J1939_NO_PGN;
    ret = recvfrom(SocketCanJ1939::sockR, dat, sizeof(dat), 0,
                   (struct sockaddr *)&peername, &peernamelen);
    if (ret < 0)
    {
        printf("recvfrom err, ret:%d\n", ret);
        return ret;
    }
    printf("name:%016llx-", peername.can_addr.j1939.name);
    printf("addr:%02x-pgn:%05x-", peername.can_addr.j1939.addr,
           peername.can_addr.j1939.pgn);
    // for (i = 0, j = 0; i < ret; ++i, j++)
    // {
    //     printf(" %02x", dat[i]);
    // }
    // russell:将读取的数据放入队列。
    readCanJ1939MessageToQueue(peername.can_addr.j1939.pgn, ret, dat);

    return ret;
}

int SocketCanJ1939::setSendTimeOut(uint32_t sec_ms)
{
    int ret;
    // uint64_t timeOutUs = sec_ms * 1000;
    if(sec_ms == SocketCanJ1939::timeoutW)
        return 0;
    timeoutW = sec_ms;
    printf("setSendTimeOut ms:%d\n", timeoutW);
    struct timeval timeout
    {
        (timeoutW/1000), ((timeoutW%1000)*1000)
    };
    // 设置发送超时
    ret = setsockopt(sockW, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeoutW, sizeof(struct timeval));
    if (ret != 0)
    {
        printf("setSendTimeOut err, ret:%d\n", ret);
    }

    return ret;
}
// 大于1000毫秒，传参在sec，不然会有错误。
int SocketCanJ1939::setReadTimeOut(uint32_t sec_ms)
{
    int ret;
    if(sec_ms == SocketCanJ1939::timeoutR)
        return 0;

    struct timeval Rtimeout
    {
        (timeoutR/1000), ((timeoutR%1000)*1000)
    };
    // 设置接收超时
    ret = setsockopt(sockR, SOL_SOCKET, SO_RCVTIMEO, (char *)&Rtimeout, sizeof(struct timeval));
    if (ret != 0)
    {
        printf("setReadTimeOut err, ret:%d\n", ret);
    }

    return ret;
}

void SocketCanJ1939::sendCanJ1939Message(uint32_t pgn, int dlc, const uint8_t *data, uint8_t ifSendFailRetry,
                             uint32_t timeoutMs)
{
    auto msg = std::make_shared<canJ1939Data>(pgn, dlc, data, ifSendFailRetry, timeoutMs);
    m_TxQueue.push_back(msg);
}

void SocketCanJ1939::getQueueSend(void)
{
    int ret;
    // 检查队列是否不为空
    if (!m_TxQueue.empty())
    {
        auto frontData = m_TxQueue.front();

        SocketCanJ1939::setSendTimeOut(frontData->timeoutMs);
        
        // 处理数据...
        do
        {
            ret = sendData(frontData->pgn, frontData->dlc, frontData->data);
            if (ret < 0)
            {
                printf("getQueueSend err, ret:%d,retry\n", ret);
            }
        } while ((!ret)&&(frontData->ifSendFailRetry--));//russell:发送失败，重新发送
        printf("ifSendFailRetry :%d,retry\n", frontData->ifSendFailRetry);
        m_TxQueue.pop_front();
    }
}

void SocketCanJ1939::readCanJ1939MessageToQueue(uint32_t pgn, int dlc, const uint8_t *data)
{
    //russell：未传的参数使用默认值
    auto msg = std::make_shared<canJ1939Data>(pgn, dlc, data);
    m_RxQueue.push_back(msg);
}

void SocketCanJ1939::readMessageQueue(void)
{
    // printf("\n readMessageQueueHandler:\n");
    // 检查队列是否不为空
    if (!m_RxQueue.empty())
    {
        printf("\n not empty:\n");
        // 检查队列是否不为空
        auto frontData = m_RxQueue.front();
        // 处理数据...
        recMessageHandler(frontData->pgn, frontData->dlc, frontData->data);
        // 移出队列
        m_RxQueue.pop_front();
    }
}

void SocketCanJ1939::recMessageHandler(uint32_t pgn, int dlc, const uint8_t *data)
{
    int i, j;
    printf("data_len:%d,pgn:%05x-", dlc, pgn);
    for (i = 0, j = 0; i < dlc; ++i, j++)
    {
        printf(" %02x", data[i]);
    }
}

#if 0
int main()
{
    printf("hello can\n");
    SocketCanJ1939 can;

    can.Open("can0");

    printf("read can\n");
    // can.setSendTimeOut(1);
    can.sendData(0x1923, 13, "222222222222221111111111111111111111111111111133");
    // can.setReadTimeOut(2, 500);
    can.sendCanJ1939Message(0x1823, 8, (uint8_t *)"9999999999999999999999999999999");
    can.getQueueSend();

    auto running = std::atomic<bool>(true);

    auto polling_thread = std::thread{[&]
                                      {
                                          while (running)
                                          {
                                                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                                can.readData();
                                                can.readMessageQueueHandler();

                                            //   can.sendCanJ1939Message(0x1823, 8, (uint8_t *)"9999999999999999999999999999999");
                                            //   can.getQueueSend();
                                          }
                                      }};

    polling_thread.join();

    return 0;
}
#endif
