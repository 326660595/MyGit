#include <can_service.h>

CCanService::CCanService()
    : m_runningState(true)
{
  int ret;
  ret = CCanService::Open(CAN_DEV_NAME);
  // printf("ret %d \n",ret);
  if (ret < 0)
  {
    printf("CCanService open err:%d\n",ret);
  }
}

CCanService::~CCanService()
{
  if (canSendThread_.joinable())
    canSendThread_.join();
  if (canReadThread_.joinable())
    canReadThread_.join();
}

int CCanService::Stop()
{
  m_runningState = false;
  return 0;
}

int CCanService::configCan(char *canName)
{
}

int CCanService::Init()
{
  int ret = 1;
  
  // printf("ret %d \n",ret);
  // ret = 1;
  // if (ret == 1)
  // {
  //   printf("CCanService Init ok:%d\n",ret);
  //   return -1;
  // }
  // if (ret == 0)
  // {
  //   printf("CCanService Init err:%d\n",ret);
  //   return -1;
  // }
  // m_runningState = true;
  // canJ1939SendLoop();
  // printf("canJ1939ReadLoop\n");
  // canJ1939ReadLoop();
}

int CCanService::canJ1939SendLoop()
{
  canSendThread_ = std::thread{[&]
                               {
                                 while (m_runningState)
                                 {
                                   std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                   CCanService::getQueueSend();
                                 }
                               }};
  return 0;
}

int CCanService::canJ1939ReadLoop()
{
  canReadThread_ = std::thread{[&]
                               {
                                 while (m_runningState)
                                 {
                                   std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                   CCanService::readData();
                                 }
                               }};
  return 0;
}

void CCanService::recMessageHandler(__u8 addr, uint32_t pgn, int dlc, const uint8_t *data)
{
    int i, j;
    printf("recMessageHandler:data_len:%d,addr:%02x-pgn:%05x-",dlc,addr,  pgn);
    for (i = 0, j = 0; i < dlc; ++i, j++)
    {
        printf(" %02x", data[i]);
    }
}

uint32_t CCanService::GetTimeoutMs(uint32_t PGN)
{
    switch ( PGN )
    {
        case CANj1939::Message::PGN::SYNC_TIME:
        case CANj1939::Message::PGN::BCU_HEART_BEAT: return CANj1939::Message::TimeoutMsDefault0;
        case CANj1939::Message::PGN::START_CHARGING: return CANj1939::Message::TimeoutMsDefault2;
        default: return CANj1939::Message::TimeoutMsDefault1;
    }
}

#if 1
#include <thread>
int main()
{
    printf("hello can\n");
    CCanService can;

    // can.Open("can0");
    // can.Init();
    can.canSendThread_ = std::thread{[&]
                              {
                                while (can.m_runningState)
                                {
                                  std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                  can.getQueueSend();
                                }
                              }};

    can.canReadThread_ = std::thread{[&]
                              {
                                while (can.m_runningState)
                                {
                                  std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                  can.readData();
                                  can.readMessageQueue();
                                }
                              }};

    printf("read can\n");
    // can.setSendTimeOut(1);
    can.sendData(0xf5, 0x4700, 13, "222222222222221111111111111111111111111111111133");
    // can.setReadTimeOut(2, 500);
    can.sendCanJ1939Message(0x88, 0x0100, 8, (uint8_t *)"9999999999999999999999999999999",1,1);
    // can.getQueueSend();
    while (1)
    {
      /* code */
    }
    


    // auto running = std::atomic<bool>(true);

    // auto polling_thread = std::thread{[&]
    //                                   {
    //                                       while (running)
    //                                       {
    //                                             std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //                                             can.readData();
    //                                             can.readMessageQueue();

    //                                         //   can.sendCanJ1939Message(0x1823, 8, (uint8_t *)"9999999999999999999999999999999");
    //                                         //   can.getQueueSend();
    //                                       }
    //                                   }};

    // polling_thread.join();

    return 0;
}

#endif