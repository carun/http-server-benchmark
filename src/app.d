import vibe.vibe;
import std;
import std.experimental.logger: FileLogger, MultiLogger;

__gshared MultiLogger _log;
__gshared FileLogger onScreen;

import core.time;
import core.thread;

alias sleep = compose!(Thread.sleep, dur!("seconds"));

void main()
{
    _log = new MultiLogger();
    _log.insertLogger("stdout", new FileLogger(stdout));
    writefln("Master %d is running", getpid());
    setupWorkerThreads(logicalProcessorCount);
    runWorkerTaskDist(&runServer);
    runApplication();
}

void runServer()
{
    auto settings = new HTTPServerSettings;
    settings.options |= HTTPServerOption.reusePort;
    settings.port = 8080;
    settings.bindAddresses = ["127.0.0.1"];
    listenHTTP(settings, &handleRequest);
}

void handleRequest(HTTPServerRequest req, HTTPServerResponse res)
{
    // _log.info("Hello, world!");
    // sleep(1);
    res.writeBody("Hello World");
}
