#pragma once
#include <atomic>
#include "SocketCanJ1939.h"

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
  int Stop();
  int canJ1939SendLoop();
  int canJ1939ReadLoop();
  void recMessageHandler(uint32_t pgn, int dlc, const uint8_t *data) override;

private:
  std::atomic<bool> m_runningState;
};