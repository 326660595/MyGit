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

#include <boost/asio.hpp>

using namespace boost;

class AsioSocketCanChannel
{
    public:
        AsioSocketCanChannel(asio::io_context& io_context);
        bool Open(const std::string& device);        
        void Close();        
        void Write(unsigned canId, bool isExtendedId, unsigned dlc, const void* data);
        
        using FrameReceivedCallback = std::function<void(AsioSocketCanChannel& channel, unsigned canId, bool isExtendedId, unsigned dlc, const unsigned char* data)>;
        using SubscriptionId = int;

        SubscriptionId Subscribe(unsigned canId, bool isExtendedId, const FrameReceivedCallback& callback);
        
        void Unsubscribe(SubscriptionId id);
        
    private:
        struct Subscription 
        {
            SubscriptionId Id;
            unsigned CanId;
            unsigned FilterFlags;
            FrameReceivedCallback Callback;
        };

        std::mutex _subscriptionLock;
        std::atomic<SubscriptionId> _nextSubscriptionId { 0 };
        std::vector<Subscription> _subscriptions;

        asio::posix::stream_descriptor _stream;
        struct can_frame _recvFrame;
        struct canfd_frame _recvFdFrame;

        SubscriptionId GenerateSubscriptionId();        
        void AsyncRead();        
        void OnFrameReceived(boost::system::error_code ec);        
        void UpdateFilters(int sock);
        
};

