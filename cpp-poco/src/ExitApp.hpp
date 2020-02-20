#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>

struct ExitApp final
{
public:
    void waitForExit()
    {
        std::unique_lock<std::mutex> lk(_mtx);
        _cnd.wait(lk, [&] {return _exitApp == true; });
    }

    void exitApp()
    {
        std::lock_guard<std::mutex> lk(_mtx);
        _exitApp = true;;
        _cnd.notify_all();
    }

private:
    std::atomic_bool _exitApp { false };
    std::condition_variable _cnd;
    std::mutex              _mtx;
};
