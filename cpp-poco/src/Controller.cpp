///
/// @author     Arun Chandrasekaran <arun.chandrasekaran@necam.com>
/// @copyright  NEC Corporation of America
///

#include "Controller.hpp"
#include "RestHandler.hpp"

Controller* Controller::_instance{NULL};
ExitApp Controller::_ex;

Controller::Controller()
{
    try
    {
        initialize();
    }
    catch (const std::exception& e)
    {
        throw ControllerException(e.what());
    }
}

Controller::~Controller()
{
    if (_httpServer != nullptr)
        _httpServer->stopAll();
}

void Controller::initialize()
{
    using namespace Poco::Net;
    auto* factory = new ESRequestHandlerFactory;
    auto* params = new HTTPServerParams;
    int backlog = 128;
    char* bk = std::getenv("AIMES_TCP_BACKLOG");
    if (bk != NULL)
        backlog = std::stoi(bk, NULL, 0);
    // This is a memory leak.
    // It is one time memory allocation that is never deallocated.
    // Other design is to have this variable as class member and that will complicate things further.
    auto* serverSock = new ServerSocket(8080, backlog);

    params->setMaxThreads(8);

    try
    {
        _httpServer = std::make_unique<HTTPServer>(factory, *serverSock, params);
        _httpServer->start();

    }
    catch (Poco::Net::NetException& e)
    {
        throw std::runtime_error(e.displayText());
    }
}
