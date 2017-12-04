//
// Created by koncord on 01.08.17.
//

#pragma once

#include "sol.hpp"
#include "CommandController.hpp"
#include "Timer.hpp"
#include <unordered_map>
#include <memory>
#include <apps/openmw-mp/Actors.hpp>
#include <apps/openmw-mp/Object.hpp>

//class CommandController;
class EventController;
//class TimerController;

struct ServerModuleInfo
{
    std::string name;
    std::pair<std::string, std::string> path; // homePath, moduleName
    std::string version;
    std::string author;
    std::vector<std::pair<std::string, std::string>> dependencies; // name, requestedVersion
    sol::environment env;
};

class LuaState
{
public:
    LuaState();
    ~LuaState() = default;
    std::shared_ptr<sol::state> getState() { return lua; }
    void addGlobalPackagePath(const std::string &path);
    void addGlobalCPath(const std::string &path);
    sol::table getCoreTable() { return dataEnv["Core"]; }
    sol::environment &getDataEnv(){ return dataEnv; }
    void loadModules(const std::string &path, std::vector<std::string> *list = nullptr);

    CommandController &getCmdCtrl();
    EventController &getEventCtrl();
    TimerController &getTimerCtrl();
    ObjectController &getObjectCtrl();

    ActorController &getActorCtrl();

private:
    sol::environment openScript(std::string path, std::string moduleName);
private:
    std::shared_ptr<sol::state> lua;
    sol::environment dataEnv;
    sol::environment configEnv;
    std::unique_ptr<CommandController> cmdCtrl;
    std::unique_ptr<EventController> eventCtrl;
    std::unique_ptr<TimerController> timerCtrl;
    std::unique_ptr<ActorController> actorCtrl;
    std::unique_ptr<ObjectController> objectCtrl;

    std::vector<ServerModuleInfo> modules;
};
