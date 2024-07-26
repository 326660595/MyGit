#pragma once
#include <atomic>
#include "SocketCanJ1939.h"

class CObject
{
};

class CCanService : public SocketCanJ1939
{
public:
  CCanService();
  virtual ~CCanService();
  int Stop();
  int Init();
  int canJ1939SendLoop();
  int canJ1939ReadLoop();
  void recMessageHandler(uint32_t pgn, int dlc, const uint8_t *data) override;

private:
  std::atomic<bool> m_runningState;
};