///
/// @author     Arun Chandrasekaran <arun.chandrasekaran@necam.com>
/// @copyright  NEC Corporation of America
///

#include <cstdio>
#include <iostream>

#include "Controller.hpp"

void registerSignals()
{
#ifdef __linux__
    {
        struct sigaction sa;
        sa.sa_flags = 0;            // to init signal flags
        sa.sa_handler = SIG_IGN;    // to ignore signal
        ::sigemptyset(&sa.sa_mask); // zero out sa_mask

        for (int i = 1; i < NSIG; i++)
        {
            // ignore all signals bug TERM, INT and CHLD
            if (i != SIGTERM && i != SIGINT && i != SIGCHLD)
                ::sigaction(i, &sa, NULL);
        }
    }

    {
        struct sigaction sa;
        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);
        sa.sa_sigaction = Controller::terminationHandler;
        sigaction(SIGTERM, &sa, NULL);
        sigaction(SIGINT, &sa, NULL);
    }
#else
    signal(SIGINT, Controller::terminationHandler);
    signal(SIGTERM, Controller::terminationHandler);
#endif
}

int main(int argc, char** argv)
{
    try
    {
        registerSignals();
        Controller::exec();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
