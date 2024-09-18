


// #include <iostream>
// #include <sstream>
// #include <iomanip>

// // 将字节数组转换为十六进制字符串
// std::string bytesToHexString(const uint8_t *data, size_t size) {
//     std::stringstream ss;
//     // 设置为十六进制输出，并且使用填充0来保持一致性
//     ss << std::hex << std::setfill('0');
    
//     for (size_t i = 0; i < size; ++i) {
//         // 对每个字节进行格式化输出，每个字节两个十六进制数字
//         ss << std::setw(2) << static_cast<int>(data[i]);
//     }

//     return ss.str();
// }

// #define BYTES_TO_HEX_STRING(data,size) \
//   bytesToHexString(data,size)

// int main() {
//     uint8_t myArray[] = {0xde, 0xad, 0xbe, 0xef,0x00,0x09};
//     size_t size = sizeof(myArray) / sizeof(myArray[0]);
//     // std::string hexString = bytesToHexString(myArray, size);

//     std::string hexString = BYTES_TO_HEX_STRING(myArray, size);

//     std::cout << hexString << std::endl; // 输出 "deadbeef"
//     return 0;
// }

// #include <iostream>
// #include <sstream>
// #include <iomanip>

// // 将整数转换为十六进制字符串
// std::string toHexString(int number,int kuandu) {
//     std::stringstream ss;
//     ss << std::hex << std::setfill('0');
//     // 假设我们想要至少2位十六进制数，对于更大的数字，可以适当增加std::setw的参数
//     ss << std::setw(kuandu) << number;
//     return ss.str();
// }

// int main() {
//     int number = 6666;
//     std::string hexNumber = toHexString(number,4);
//     std::cout << "The number in hexadecimal: " << hexNumber << std::endl;
//     return 0;
// }

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

class MyTimer
{
public:
    MyTimer(boost::asio::io_context& io_context, int interval_ms)
        : m_ioContext(io_context),
          m_timer(io_context),
          m_interval(interval_ms)
    {
    }

    void Start()
    {
        m_timer.expires_after(std::chrono::milliseconds(m_interval));
        m_timer.async_wait(std::bind(&MyTimer::OnTimerExpired, this, std::placeholders::_1));
    }

    void Stop()
    {
        m_timer.cancel();
    }

private:
    void OnTimerExpired(const boost::system::error_code& error)
    {
        if (!error)
        {
            std::cout << "Timer expired!" << std::endl;
            // Restart the timer
            Start();
        }
        else
        {
            std::cout << "Timer error: " << error.message() << std::endl;
        }
    }

    boost::asio::io_context& m_ioContext;
    boost::asio::steady_timer m_timer;
    int m_interval;
};

int main()
{
    boost::asio::io_context io_context;

    auto timer = std::make_shared<MyTimer>(io_context, 1000); // 1000 ms interval
    timer->Start();

    io_context.run();

    return 0;
}
