#include <iostream>
#include <Kbhit.h>
#include <RakSleep.h>
#include <extern/sol/sol.hpp>
#include "MasterServer.hpp"
#include "RestServer.hpp"

using namespace RakNet;
using namespace std;

unique_ptr<RestServer> restServer;
shared_ptr<MasterServer> masterServer;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    string luaScript(argv[1]);

    masterServer = make_shared<MasterServer>(luaScript);
    masterServer->luaStuff([](sol::state &state)
    {
        sol::table config = state["config"];
        sol::object restPort = config["restPort"];
        if (restPort.get_type() != sol::type::number)
            throw runtime_error("config.restPort is not correct");


        restServer = make_unique<RestServer>(restPort.as<unsigned short>(), masterServer->GetServers());
    });

    auto onExit = [](int /*sig*/){
        restServer->stop();
        masterServer->luaStuff([](sol::state &state) {
            sol::protected_function func = state["OnExit"];
            if (func.valid())
                func.call();
        });
        masterServer->Stop(false);
        masterServer->Wait();
    };

    signal(SIGINT, onExit);
    signal(SIGTERM, onExit);

    masterServer->Start();

    thread rest_thread([]() { restServer->start();});

    rest_thread.join();
    masterServer->Wait();

    return 0;
}
