#pragma once
#include <atomic>
// #include <app_timer.h>
#include <thread>
#include "SocketCanJ1939.h"
#include "can_message.h"

#define CAN_DEV_NAME "can0"
class CObject
{
};

class CCanService : public SocketCanJ1939
{
public:
  CCanService();
  virtual ~CCanService();
  int Init();
  int configCan(char *canName);
  int Stop();
  int canJ1939SendLoop();
  int canJ1939ReadLoop();
  void recMessageHandler(__u8 addr, uint32_t pgn, int dlc, const uint8_t *data) override;

  uint32_t GetTimeoutMs(uint32_t PGN);
  std::atomic<bool> m_runningState;
  std::thread canSendThread_;
  std::thread canReadThread_;

private:


};