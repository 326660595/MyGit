#include <can_service.h>

CCanService::CCanService()
  :m_runningState(true)
{

}

CCanService::~CCanService()
{
  
}

int CCanService::Stop()
{
  m_runningState = false;
  return 0;
}

int CCanService::Init()
{

}
int CCanService::canJ1939SendLoop()
{

}
int CCanService::canJ1939ReadLoop()
{
  
}

void CCanService::recMessageHandler(uint32_t pgn, int dlc, const uint8_t *data)
{
    int i, j;
    printf("recMessageHandler:data_len:%d,pgn:%05x-", dlc, pgn);
    for (i = 0, j = 0; i < dlc; ++i, j++)
    {
        printf(" %02x", data[i]);
    }
}

#if 1
#include <thread>
int main()
{
    printf("hello can\n");
    CCanService can;

    can.Open("can0");

    printf("read can\n");
    // can.setSendTimeOut(1);
    can.sendData(0x1923, 13, "222222222222221111111111111111111111111111111133");
    // can.setReadTimeOut(2, 500);
    can.sendCanJ1939Message(0x1823, 8, (uint8_t *)"9999999999999999999999999999999",1,1);
    can.getQueueSend();

    auto running = std::atomic<bool>(true);

    auto polling_thread = std::thread{[&]
                                      {
                                          while (running)
                                          {
                                                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                                can.readData();
                                                can.readMessageQueue();

                                            //   can.sendCanJ1939Message(0x1823, 8, (uint8_t *)"9999999999999999999999999999999");
                                            //   can.getQueueSend();
                                          }
                                      }};

    polling_thread.join();

    return 0;
}

#endif