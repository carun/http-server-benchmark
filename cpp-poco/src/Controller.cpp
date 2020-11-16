///
/// @author     Arun Chandrasekaran <arun.chandrasekaran@necam.com>
/// @copyright  NEC Corporation of America
///

#include <Poco/Net/SSLManager.h>
#include <Poco/SharedPtr.h>
#include <Poco/Net/KeyConsoleHandler.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/SecureServerSocket.h>
#include <Poco/Net/HTTPServerRequestImpl.h>

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
    using namespace Poco;
    auto* factory = new ESRequestHandlerFactory;
    auto* params = new HTTPServerParams;
    int backlog = 128;
    params->setMaxThreads(8);

    try
    {
        SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new KeyConsoleHandler(true);
        SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new ConsoleCertificateHandler(true);
        Context::Ptr pContext = new Context(Context::SERVER_USE, "privatekey.pem", "privatekey.pem", "rootcert.pem", Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        pContext->disableProtocols(Poco::Net::Context::PROTO_SSLV2 | Poco::Net::Context::PROTO_SSLV3);
        SSLManager::instance().initializeServer(pConsoleHandler, pInvalidCertHandler, pContext);

        // This is a memory leak.
        // It is one time memory allocation that is never deallocated.
        // Other design is to have this variable as class member and that will complicate things further.
        auto* serverSock = new SecureServerSocket(5050, backlog, pContext);
        _httpServer = std::make_unique<HTTPServer>(factory, *serverSock, params);
        _httpServer->start();

    }
    catch (Poco::Net::NetException& e)
    {
        std::cout << "HTTPS server exception: " <<  e.displayText() << std::endl;
        throw std::runtime_error(e.displayText());
    }
}
