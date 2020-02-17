import vibe.vibe;
import std;
import std.experimental.logger: FileLogger, MultiLogger;

__gshared MultiLogger _log;
__gshared FileLogger onScreen;

void main()
{
    auto settings = new HTTPServerSettings;
    settings.port = 3000;
    settings.bindAddresses = ["::1", "127.0.0.1"];
    listenHTTP(settings, &hello);

    _log = new MultiLogger();
    onScreen = new FileLogger(stdout);
    _log.insertLogger("stdout", onScreen);

    runApplication();
}

void hello(HTTPServerRequest req, HTTPServerResponse res)
{
    _log.info("Hello, world!");
    res.writeBody("Hello World");
}
