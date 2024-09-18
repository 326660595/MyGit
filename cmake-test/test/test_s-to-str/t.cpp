#include <boost/asio.hpp>
#include <boost/bind/placeholders.hpp>
#include </usr/include/boost/asio/detail/reactive_socket_service.hpp>
#include <stdio.h>
#include <iostream>
#include <memory>

boost::asio::io_context io_context;
void OnTransmit(uint32_t PGN);

class GenericTimer {
public:
    enum TTimerType {
        SINGLE_SHOT,
        PERIODIC
    };
    typedef std::function<void (GenericTimer* pTimer)> TTimerHandler;

    GenericTimer()
        : m_IntervalMs(1000),
          m_eType(SINGLE_SHOT),
          m_fActive(false),
          m_pHandler(nullptr)
    {
    }

    virtual void SetInterval(int interval) { m_IntervalMs = interval; }
    virtual int GetInterval() { return m_IntervalMs; }

    virtual void SetType(TTimerType eType) { m_eType = eType; }
    virtual TTimerType GetType() { return m_eType; }

    virtual void SetHandler(TTimerHandler pHandler) { m_pHandler = pHandler; }

    virtual bool IsRunning() { return m_fActive; }

    virtual void Start() { SetEnabled(true); }
    virtual void Stop() { SetEnabled(false); }
    virtual void SetEnabled(bool fEnabled) = 0;

protected:
    int m_IntervalMs;
    TTimerType m_eType;
    bool m_fActive;
    TTimerHandler m_pHandler;

    virtual void CallHandler() {
        if (m_pHandler) {
            m_pHandler(this);
        }
    }
};

class AppTimer: public GenericTimer {
public:
    AppTimer(boost::asio::io_context& io_context)
        : m_ioContext(io_context),
          m_timer(io_context)
    {
    }

    virtual ~AppTimer() { Stop(); }

    virtual void SetEnabled(bool fEnabled) override {
        if (fEnabled && !IsRunning()) {
            m_timer.expires_after(std::chrono::milliseconds(GetInterval()));
            m_timer.async_wait([this](const boost::system::error_code& error) { OnTimerExpired(error); });
            m_fActive = true;
        } else if (!fEnabled && IsRunning()){
            m_timer.cancel();
            m_fActive = false;
        }
    }

private:
    void OnTimerExpired(const boost::system::error_code& error) {
        if (!error) {
            CallHandler();
            if (m_eType == PERIODIC) {
                m_timer.expires_after(std::chrono::milliseconds(GetInterval()));
                m_timer.async_wait([this](const boost::system::error_code& error) { OnTimerExpired(error); });
            } else {
                m_fActive = false;
            }
        }
    }

    boost::asio::io_context& m_ioContext;
    boost::asio::steady_timer m_timer;
};

AppTimer *CreateAppTimer(boost::asio::io_context &io_context) {
    return new AppTimer(io_context);
}

void OnTransmit(GenericTimer* pTimer,uint32_t PGN)
{
  std::cout << "OnTransmit-----------------------\n"<< std::endl;

}
void run_timer(void)
{
    auto timer = std::shared_ptr<AppTimer>(CreateAppTimer(io_context));
    timer->SetInterval(1000); // 1000 ms interval
    timer->SetType(GenericTimer::PERIODIC);
    timer->SetHandler([](GenericTimer* pTimer) {
        std::cout << "Timer expired!" << std::endl;
    });
    timer->Start();
}

int main() {
    printf("tset start \n");

    // run_timer();
    int PGN = 1024;
    auto timer = std::shared_ptr<AppTimer>(CreateAppTimer(io_context));
    timer->SetInterval(1000); // 1000 ms interval
    timer->SetType(GenericTimer::PERIODIC);
    // timer->SetHandler([](GenericTimer* pTimer) {
    //     // std::cout << "Timer expired!" << std::endl;
    //     OnTransmit(1024);
    //     // printf("OnTransmit-----------------------%d",1024);
    // });
    // timer->SetHandler(boost::bind(&OnTransmit, PGN));
    timer->Start();

    io_context.run();

    return 0;
}
