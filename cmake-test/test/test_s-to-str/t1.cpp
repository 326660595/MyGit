#include <boost/asio.hpp>
#include <iostream>

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

AppTimer* CreateAppTimer(boost::asio::io_context &io_context) {
    return new AppTimer(io_context);
}

int main() {
    boost::asio::io_context io_context;

    AppTimer* timer = CreateAppTimer(io_context);
    timer->SetInterval(1000); // 1000 ms interval
    timer->SetType(GenericTimer::PERIODIC);
    timer->SetHandler([](GenericTimer* pTimer) {
        std::cout << "Timer expired!" << std::endl;
    });
    timer->Start();

    // Run the io_context in a separate thread
    std::thread io_thread([&io_context]() {
        io_context.run();
    });

    // Simulate work
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Stop the timer and delete it
    timer->Stop();
    delete timer;

    // Stop the io_context
    io_context.stop();
    io_thread.join();

    return 0;
}
