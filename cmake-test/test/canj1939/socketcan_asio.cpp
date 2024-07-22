#include "socketcan_asio.h"

using namespace boost;

AsioSocketCanChannel::AsioSocketCanChannel(asio::io_context& io_context)
    : _stream { io_context }
{            
}

bool AsioSocketCanChannel::Open(const std::string& device)
{
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    // 初始化 J1939 协议特定的地址信息
    addr.can_addr.j1939.addr = J1939_NO_ADDR;
    addr.can_addr.j1939.name = J1939_NO_NAME;
    addr.can_addr.j1939.pgn = J1939_NO_PGN;
    struct ifreq ifr;

    // int sock = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
    int sock = ::socket(PF_CAN, SOCK_DGRAM, CAN_J1939);
    if (sock < 0)
    {
        perror("create socket");
        return false;
    }

    strcpy(ifr.ifr_name, device.c_str());
    if (ioctl(sock, SIOCGIFINDEX, &ifr))
    {
        perror("get interface");
        ::close(sock);
        return false;
    }

    {
        std::lock_guard guard(_subscriptionLock);
        UpdateFilters(sock);
    }

    addr.can_ifindex = ifr.ifr_ifindex;
    if (::bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        perror("Error in socket bind");
        ::close(sock);
        return false;
    }
    _stream.assign(sock);

    AsyncRead();

    return true;
}

void AsioSocketCanChannel::Close()
{
    _stream.close();
}

void AsioSocketCanChannel::Write(unsigned canId, bool isExtendedId, unsigned dlc, const void* data)
{
    struct can_frame txFrame;
    if (isExtendedId)
    {
        txFrame.can_id = canId | CAN_EFF_FLAG;
    }
    else
    {
        txFrame.can_id = canId;
    }
    txFrame.can_dlc = dlc;
    ::memcpy(txFrame.data, data, std::min(sizeof(txFrame.data), static_cast<size_t>(dlc)));
    _stream.write_some(asio::buffer(&txFrame, sizeof(can_frame)));
}

// void AsioSocketCanChannel::WriteJ1939(unsigned canId, bool isExtendedId, unsigned dlc, const void* data)
// {
//     struct can_frame txFrame;
//     if (isExtendedId)
//     {
//         txFrame.can_id = canId | CAN_EFF_FLAG;
//     }
//     else
//     {
//         txFrame.can_id = canId;
//     }
//     txFrame.can_dlc = dlc;
//     ::memcpy(txFrame.data, data, std::min(sizeof(txFrame.data), static_cast<size_t>(dlc)));
//     _stream.write_some(asio::buffer(&txFrame, sizeof(can_frame)));
// }

AsioSocketCanChannel::SubscriptionId AsioSocketCanChannel::Subscribe(unsigned canId, bool isExtendedId, const FrameReceivedCallback& callback)
{
    Subscription sub;
    sub.Id = GenerateSubscriptionId();
    sub.CanId = canId;
    if (isExtendedId)
    {
        sub.CanId = canId | CAN_EFF_FLAG;
        sub.FilterFlags = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);
    }
    else
    {
        sub.CanId = canId;
        sub.FilterFlags = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_SFF_MASK);
    }
    sub.Callback = callback;
    
    std::lock_guard guard(_subscriptionLock);
    _subscriptions.push_back(sub);

    // 不再更新过滤器
    // if (_stream.is_open())
    // {
    //     UpdateFilters(_stream.native_handle());
    // }

    return sub.Id;
}


void AsioSocketCanChannel::Unsubscribe(SubscriptionId id)
{
    std::lock_guard guard(_subscriptionLock);
    _subscriptions.erase(
        std::remove_if(
            _subscriptions.begin(),
            _subscriptions.end(),
            [id](const Subscription& sub)
            {
                return sub.Id == id;
            }
        ),
        _subscriptions.end()
    );
    if (_stream.is_open())
    {
        UpdateFilters(_stream.native_handle());
    }
}


AsioSocketCanChannel::SubscriptionId AsioSocketCanChannel::GenerateSubscriptionId()
{
    return _nextSubscriptionId.fetch_add(1, std::memory_order_relaxed);
}

void AsioSocketCanChannel::AsyncRead()
{
    printf("AsyncRead start\n");
    _stream.async_read_some(
        asio::buffer(&_recvFrame, sizeof(_recvFrame)),
        std::bind(&AsioSocketCanChannel::OnFrameReceived, this, std::placeholders::_1)
    );
}

void AsioSocketCanChannel::OnFrameReceived(boost::system::error_code ec)
{
    printf("OnFrameReceived:\n");
    if (ec) { return; }

    auto canId = _recvFrame.can_id & CAN_EFF_MASK;
    printf("canId:%d\n",canId);

    std::lock_guard guard(_subscriptionLock);
    for (auto& sub: _subscriptions)
    {
        // if ((sub.CanId & sub.FilterFlags) == (canId & sub.FilterFlags))
        // {
            sub.Callback(*this, canId, (_recvFrame.can_id & CAN_EFF_FLAG) != 0, _recvFrame.can_dlc, _recvFrame.data);
        // }
    }

    AsyncRead();
}

// void AsioSocketCanChannel::UpdateFilters(int sock)
// {
//     std::vector<can_filter> filters;
//     filters.reserve(_subscriptions.size());
//     for (auto &sub: _subscriptions)
//     {
//         filters.push_back({ sub.CanId, sub.FilterFlags});
//     }
//     int err = ::setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, filters.data(), sizeof(can_filter)*filters.size());
//     if (err)
//     {
//         perror("filters");
//     }
// }

void AsioSocketCanChannel::UpdateFilters(int sock)
{
    // 清空过滤器列表，以确保接收所有帧
    can_filter filter = {0, 0}; // 接收所有帧
    int err = ::setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(filter));
    if (err)
    {
        perror("filters");
    }
}


#if 1
int main()
{
    printf("hello can\n");
    boost::asio::io_service ios;
    AsioSocketCanChannel can(ios);

    // AsioSocketCanChannel::SubscriptionId sub_id;
    // sub_id = can.Subscribe(0x123, false, [&sub_id](auto& sender, unsigned canId, bool isExtendedId, unsigned dlc, const unsigned char* data) {
    //     printf("frame received! id=0x%x\n", canId);
    //     sender.Unsubscribe(sub_id);
    // });

    // can.Subscribe(0x345, false, [&sub_id](auto& sender, unsigned canId, bool isExtendedId, unsigned dlc, const unsigned char* data) {
    //     printf("frame received! id=0x%x\n", canId);
    // });

    can.Open("can0");
    can.Write(0x123, false, 8, "11111111");

    ios.run();
    return 0;
}
#endif