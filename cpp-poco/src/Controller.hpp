///
/// @author     Arun Chandrasekaran <arun.chandrasekaran@necam.com>
/// @copyright  NEC Corporation of America
///

#include <csignal>
#include <Poco/Net/HTTPServer.h>

#include "ExitApp.hpp"

struct ControllerException : public std::runtime_error
{
    ControllerException(const std::string err)
        : std::runtime_error(err)
    {
    }
};

struct Controller final
{
public:
#ifdef __linux__
    static void terminationHandler(int signum, siginfo_t*, void*)
#else
    static void terminationHandler(int signum)
#endif
    {
        if (signum == SIGTERM || signum == SIGINT)
        {
            _ex.exitApp();
        }
    }

    static void exec()
    {
        createInstance();

        _ex.waitForExit();

        destroy();
    }

    static void shutdown()
    {
        _ex.exitApp();
    }

private:

    Controller();
    ~Controller();

    static Controller* _instance;

    void initialize();
    
    static Controller& createInstance()
    {
        if (!_instance)
            _instance = new Controller();

        return *(_instance);
    }

    static void destroy()
    {
        if (_instance)
            delete _instance;
        _instance = nullptr;
    }

    std::unique_ptr<Poco::Net::HTTPServer> _httpServer{nullptr};
    static ExitApp _ex;
};
