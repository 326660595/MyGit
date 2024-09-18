#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> running(true);  // 使用原子变量控制异步任务的停止
int i = 0;

void async_operation() {
    // 模拟异步操作
    std::async(std::launch::async, []() {
        while (running)  // 通过外部的条件控制循环
        {
            std::cout << "---- " << i++ << "\n" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "异步任务结束" << std::endl;
    });
}

int main() {
    async_operation();  // 启动异步操作
    std::cout << "异步操作正在运行..." << std::endl;

    // 模拟运行一段时间后停止
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 停止异步任务
    running = false;
    
    // 主线程等待一小段时间以确保异步任务结束
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}






















///////////////////////////////////////////////////////////
// #include <boost/asio.hpp>
// #include <iostream>
// #include <memory>
// #include <thread>
// #include <chrono>

// int i = 0;
// class CCanService
// {
// public:
//     CCanService(boost::asio::io_context &io_context)
//         : m_ioContext(io_context), m_running(true) {}

//     // 异步开始 CAN 数据读取
//     void StartReading()
//     {
//         ScheduleRead();
//     }

//     // 停止 CAN 数据读取
//     void StopReading()
//     {
//         m_running = false;
//     }

// private:
//     boost::asio::io_context &m_ioContext;
//     std::atomic<bool> m_running;

//     // 模拟 CAN 数据读取函数
//     void readData()
//     {
//         std::cout << "Reading CAN data..." << i++ <<std::endl;
//         // 模拟实际的 CAN 数据读取，可以替换为你的实际逻辑
//     }

//     void ScheduleRead()
//     {
//         // 使用 boost::asio::post 来调度下一个读取操作
//         boost::asio::post(m_ioContext, [this]() {
//             if (m_running) {
//                 readData();
//                 ScheduleRead();  // 递归调度下一个异步操作
//             }
//         });
//     }
// };

// int main()
// {
//     std::cout << "Reading CAN start..." << std::endl;
//     boost::asio::io_context io_context;

//     CCanService canService(io_context);

//     // 在独立的线程中运行 io_context 事件循环
//     std::thread io_thread([&io_context]() {
//         io_context.run();
//     });

//     // 开始异步读取 CAN 数据
//     canService.StartReading();

//     // 模拟运行一段时间后停止
//     std::this_thread::sleep_for(std::chrono::seconds(5));
//     canService.StopReading();

//     io_thread.join();  // 等待 io_context 线程结束

//     return 0;
// }
//、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
// #include <iostream>
// #include <functional>

// void async_operation(std::function<void(int)> callback) {
//     // 模拟异步操作
//     int result = 42;
//     callback(result);
// }

// int main() {
//     async_operation([](int result) {
//         std::cout << "异步操作完成，结果为: " << result << std::endl;
//     });

//     return 0;
// }