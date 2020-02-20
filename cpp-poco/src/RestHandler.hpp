#pragma once

#include <chrono>
#include <atomic>
#include <algorithm>

#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/NetException.h>
#include <Poco/URI.h>

#include <iostream>
#include <string>
#include <vector>

using namespace Poco::Net;

class RestHandler : public HTTPRequestHandler
{
public:
    virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& respBody);
};

class ESRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&)
    {
        // This is automatically deallocated by Poco
        return new RestHandler;
    }
};

inline void RestHandler::handleRequest(HTTPServerRequest& req, HTTPServerResponse& res)
{
    try
    {
        // Poco::URI uri{req.getURI()};
        // auto& dest = uri.getPath();
        // std::vector<std::string> pathList;
        // uri.getPathSegments(pathList);

        // auto& is = req.stream();
        // res.setKeepAlive(false);
        // res.setContentType("application/json");

        res.setStatusAndReason(HTTPResponse::HTTP_OK, HTTPResponse::HTTP_REASON_OK);
        res.send();
    }
    catch (Poco::Net::NetException& e)
    {
    }
    catch (const std::exception& e)
    {
    }
}

