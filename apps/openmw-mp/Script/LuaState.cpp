//
// Created by koncord on 01.08.17.
//

#include <iostream>
#include <cstdlib>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/tokenizer.hpp>

#include <components/misc/stringops.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Version.hpp>

#include <apps/openmw/mwworld/inventorystore.hpp>

#include "LuaState.hpp"
#include "luaUtils.hpp"
#include "EventController.hpp"
#include "CommandController.hpp"

#include "../Networking.hpp"
#include "../MasterClient.hpp"

#include "../Dialogue.hpp"
#include "../Factions.hpp"
#include "../GUI.hpp"
#include "../Inventory.hpp"
#include "../Players.hpp"
#include "../Quests.hpp"
#include "../Settings.hpp"
#include "../Spells.hpp"
#include "../Weather.hpp"

using namespace std;


#if defined(SOL_SAFE_FUNCTIONS)
inline int errHandler(lua_State *L)
{
    string msg = "An unknown error has triggered the default error handler";
    auto maybetopmsg = sol::stack::check_get<sol::string_view>(L, 1);
    if (maybetopmsg)
    {
        const sol::string_view &topmsg = maybetopmsg.value();
        msg.assign(topmsg.data(), topmsg.size());
    }
    luaL_traceback(L, L, msg.c_str(), 1);
    auto maybetraceback = sol::stack::check_get<sol::string_view>(L, -1);
    if (maybetraceback)
    {
        const sol::string_view &traceback = maybetraceback.value();
        msg.assign(traceback.data(), traceback.size());
    }
    LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, msg.c_str());
    abort();
    return 0; // Not used because the server is already terminated
}
#endif

LuaState::LuaState()
{
    lua = make_shared<sol::state>();
    lua->open_libraries();
    LuaUtils::Init(*this);

    actorCtrl = make_unique<ActorController>();
    ActorController::Init(*this);

    eventCtrl = make_unique<EventController>(this);
    EventController::Init(*this);

    objectCtrl = make_unique<ObjectController>();
    ObjectController::Init(*this);

    cmdCtrl = make_unique<CommandController>();
    Player::Init(*this);
    Cells::Init(*this);
    CharClass::Init(*this);
    Inventory::Init(*this);
    GameSettings::Init(*this);
    Books::Init(*this);
    GUI::Init(*this);
    Dialogue::Init(*this);
    Factions::Init(*this);
    Faction::Init(*this);
    JournalItem::Init(*this);
    Quests::Init(*this);
    Effect::Init(*this);
    Spell::Init(*this);
    Spells::Init(*this);
    WeatherMgr::Init(*this);

    Players::Init(*this);

    timerCtrl = make_unique<TimerController>();
    TimerController::Init(*this);
    Timer::Init(*this);

    CommandController::Init(*this);

    dataEnv = sol::environment(*lua, sol::create, lua->globals());
    lua->set("Data", dataEnv); // plain global environment for communicating between modules
    auto coreTable = dataEnv.create("Core");
    coreTable["VERSION"] = TES3MP_VERSION;
    coreTable["PROTOCOL"] = TES3MP_PROTO_VERSION;
    coreTable["loadedModules"] = coreTable.create();

    configEnv = sol::environment(*lua, sol::create, lua->globals());
    lua->set("Config", configEnv); // plain global environment for module configuration

    // Enable a special Sol error handler for Windows, because exceptions aren't caught properly
    // in main.cpp for it
#if defined(SOL_SAFE_FUNCTIONS)
    lua_CFunction f = sol::c_call<decltype(&errHandler), &errHandler>;
    sol::protected_function::set_default_handler(sol::object(lua->lua_state(), sol::in_place, f));
#endif

    sol::table Constants = lua->create_named_table("Constants");
    
    Constants.set_function("getAttributeCount", []() {
        return ESM::Attribute::Length;
    });
    
    Constants.set_function("getSkillCount", []() {
        return ESM::Skill::Length;
    });

    Constants.set_function("getAttributeId", [](const string &name) {
        for (int x = 0; x < ESM::Attribute::Length; x++)
            if (Misc::StringUtils::ciEqual(name, ESM::Attribute::sAttributeNames[x]))
                return x;
        return -1;
    });

    Constants.set_function("getSkillId", [](const string &name) {
        for (int x = 0; x < ESM::Skill::Length; x++)
            if (Misc::StringUtils::ciEqual(name, ESM::Skill::sSkillNames[x]))
                return x;
        return -1;
    });

    Constants.set_function("getAttributeName", [](unsigned short attribute) -> const string {
        if (attribute >= ESM::Attribute::Length)
            return "invalid";

        return ESM::Attribute::sAttributeNames[attribute];
    });

    Constants.set_function("getSkillName", [](unsigned short skill)  -> const string {
        if (skill >= ESM::Skill::Length)
            return "invalid";

        return ESM::Skill::sSkillNames[skill];
    });

    Constants.set_function("getEquipmentSize", []() {
        return MWWorld::InventoryStore::Slots;
    });


    lua->set_function("getCurrentMpNum", []() {
        return mwmp::Networking::getPtr()->getCurrentMpNum();
    });

    lua->set_function("setCurrentMpNum", [](int num) {
        mwmp::Networking::getPtr()->setCurrentMpNum(num);
    });

    lua->set_function("getPluginEnforcementState", []() {
        return mwmp::Networking::getPtr()->getPluginEnforcementState();
    });

    lua->set_function("setPluginEnforcementState", [](bool state) {
        mwmp::Networking::getPtr()->setPluginEnforcementState(state);
    });

    lua->set_function("doesFileExist", [](const char *filePath) {
        return boost::filesystem::exists(filePath);
    });

    lua->set_function("getCaseInsensitiveFilename", [](const char *folderPath, const char *filename) {
        if (!boost::filesystem::exists(folderPath)) return "invalid";

        static std::string foundFilename;
        boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end

        for (boost::filesystem::directory_iterator itr(folderPath); itr != end_itr; ++itr)
        {
            if (Misc::StringUtils::ciEqual(itr->path().filename().string(), filename))
            {
                foundFilename = itr->path().filename().string();
                return foundFilename.c_str();
            }
        }
        return "invalid";
    });

    lua->set_function("logMessage", [](unsigned short level, const char *message) {
        LOG_MESSAGE_SIMPLE(level, "[Script]: %s", message);
    });
    lua->set_function("logAppend", [](unsigned short level, const char *message) {
        LOG_APPEND(level, "%s", message);
    });

    lua->new_enum("Log",
                "LOG_FATAL", Log::LOG_FATAL,
                "LOG_ERROR", Log::LOG_ERROR,
                "LOG_WARN", Log::LOG_WARN,
                "LOG_INFO", Log::LOG_INFO,
                "LOG_VERBOSE", Log::LOG_VERBOSE,
                "LOG_TRACE", Log::LOG_TRACE);

    lua->set_function("stopServer", [](int code) {
        mwmp::Networking::getPtr()->stopServer(code);
    });

    lua->set_function("banAddress", [](const char *ipAddress) {
        mwmp::Networking::getPtr()->banAddress(ipAddress);
    });

    lua->set_function("unbanAddress", [](const char *ipAddress) {
        mwmp::Networking::getPtr()->unbanAddress(ipAddress);
    });

    lua->set_function("setRuleValue", [](const std::string &key, sol::object value) {
        if (!value.valid())
            return;

        auto mc = mwmp::Networking::getPtr()->getMasterClient();
        if (mc)
        {
            sol::type type = value.get_type();
            if (type == sol::type::string)
                mc->SetRuleString(key, value.as<string>());
            if (type == sol::type::number)
                mc->SetRuleValue(key, value.as<double>());
        }
    });

    lua->set_function("setGameModeName", [](const std::string &modeName) {
        auto mc = mwmp::Networking::getPtr()->getMasterClient();
        if (mc)
            mc->SetGameModeName(modeName);
    });

    lua->set_function("setHostname", [](const std::string &hostname) {
        auto mc = mwmp::Networking::getPtr()->getMasterClient();
        if (mc)
            mc->SetHostname(hostname);
    });

    lua->set_function("setServerPassword", [](const std::string &passw) {
        mwmp::Networking::getPtr()->setServerPassword(passw);
    });

    lua->set_function("setHour", [](double hour) {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_TIME);
        Players::for_each([&hour, &packet](Player *player){
            player->hour = hour;
            player->month = -1;
            player->day = -1;

            packet->setPlayer(player);
            packet->Send(false);
        });
    });

    lua->set_function("setMonth", [](int month) {

        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_TIME);
        Players::for_each([&month, &packet](Player *player){
            player->hour = -1;
            player->month = month;
            player->day = -1;

            packet->setPlayer(player);
            packet->Send(false);
        });
    });

    lua->set_function("setDay", [](int day) {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_TIME);
        Players::for_each([&day, &packet](Player *player){
            player->hour = -1;
            player->month = -1;
            player->day = day;

            packet->setPlayer(player);
            packet->Send(false);
        });
    });

    lua->set_function("createChannel", [](){
        return mwmp::Networking::get().createChannel();
    });
}

sol::environment LuaState::openModule(std::string homePath, std::string moduleName)
{
    cout << "Loading module: " << homePath + "/modules/" + moduleName + "/main.lua" << endl;

    sol::environment env(*lua, sol::create, lua->globals());
    std::string package_path = env["package"]["path"];
    env["package"]["path"] = Utils::convertPath(homePath + "/modules/" + moduleName + "/?.lua") + ";" + package_path;
    package_path = env["package"]["path"];

    env.set_function("getDataFolder", [homePath, moduleName]() -> const string {
        return homePath + "/data/" + moduleName + '/';
    });

    env.set_function("getModuleFolder", [homePath, moduleName]() -> const string {
        return homePath + "/modules/" + moduleName + '/';
    });

    lua->script_file(homePath + "/modules/" + moduleName + "/main.lua", env);

    return env;
}

void LuaState::addGlobalPackagePath(const std::string &path)
{
    std::string package_path = (*lua)["package"]["path"];
    (*lua)["package"]["path"] = Utils::convertPath(path) + ";" + package_path;
}

void LuaState::addGlobalCPath(const std::string &path)
{
    std::string cpath = (*lua)["package"]["cpath"];
    (*lua)["package"]["cpath"] = Utils::convertPath(path) + ";" + cpath;
}

CommandController &LuaState::getCmdCtrl()
{
    return *cmdCtrl;
}

EventController &LuaState::getEventCtrl()
{
    return *eventCtrl;
}

TimerController &LuaState::getTimerCtrl()
{
    return *timerCtrl;
}

ActorController &LuaState::getActorCtrl()
{
    return *actorCtrl;
}

ObjectController &LuaState::getObjectCtrl()
{
    return *objectCtrl;
}

int compareVersion(const string &wishVersion, const string &depVersionFound)
{
    unsigned startVer = 0;

    if (wishVersion[0] == '>')
    {
        startVer = 1;

        if (wishVersion[1] == '=')
            startVer = 2;
    }

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(".");
    tokenizer tokensWish(wishVersion.begin() + startVer, wishVersion.end(), sep), tokensFound(depVersionFound, sep);

    auto wishIter = tokensWish.begin();
    auto founditer = tokensFound.begin();
    int belowExpected = 0;

    for (int i = 0; i < 3; ++i)
    {
        auto v1 = boost::lexical_cast<int>(*(wishIter++));
        auto v2 = boost::lexical_cast<int>(*(founditer++));

        if (v2 > v1 && startVer > 0)
            return 0; // found applicable version

        if (v2 <= v1)
        {
            if (v2 == v1 && startVer == 1)
                belowExpected++;
            else if (v2 < v1)
                return -1; // found version below expected
            continue;
        }

        return 1; // version higher than expected
    }

    if (belowExpected == 3)
        return -1; // found version below expected

    return 0;
}

void checkDependencies(const vector<ServerModuleInfo> &modules, const ServerModuleInfo &smi, bool fatal = true)
{
    for (auto &dependency : smi.dependencies)
    {
        const std::string &depNameRequest = dependency.first;
        const std::string &depVersionRequest = dependency.second;

        const auto &depEnvIt = find_if(modules.begin(), modules.end(), [&depNameRequest](const auto &val) {
            return val.name == depNameRequest;
        });

        if (depEnvIt != modules.end())
        {
            const string &depVersionFound = depEnvIt->version;
            if (compareVersion(depVersionRequest, depVersionFound) != 0)
            {
                stringstream sstr;
                sstr << depNameRequest << ": version \"" << depVersionFound << "\" is not applicable for \""
                     << smi.name << "\" expected \"" << depVersionRequest + "\"";
                if (fatal)
                    Utils::throwError(sstr.str());
                else
                    LOG_MESSAGE_SIMPLE(Log::LOG_WARN, "%s", sstr.str().c_str());
            }
        }
        else // dependency not found.
        {
            stringstream sstr;
            sstr << depNameRequest + " \"" << depVersionRequest << "\" not found.";
            if (fatal)
                Utils::throwError(sstr.str());
            else
                LOG_MESSAGE_SIMPLE(Log::LOG_WARN, "%s", sstr.str().c_str());
        }
    }
}

vector<vector<ServerModuleInfo>::iterator> loadOrderSolver(vector<ServerModuleInfo> &modules)
{
    vector<vector<ServerModuleInfo>::iterator> notResolved;
    vector<vector<ServerModuleInfo>::iterator> result;

    int currentIndex = 1;
    LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Using automated order for server modules:");

    for (auto it = modules.begin(); it != modules.end(); ++it)
    {
        checkDependencies(modules, *it);

        if (it->dependencies.empty()) // if the server module doesn't have any dependencies, we can safely add it to the result
        {
            LOG_APPEND(Log::LOG_INFO, "- %i) %s", currentIndex, it->name.c_str());
            currentIndex++;

            result.push_back(it);
        }
        else
            notResolved.push_back(it);
    }

    while (true) // Iterate notResolved until it becomes empty
    {
        for (auto it = notResolved.begin(); it != notResolved.end();)
        {
            bool resolved = true;
            for (auto &dep : (*it)->dependencies)
            {
                auto found = find_if(result.begin(), result.end(), [&dep](auto &a) {
                    return dep.first == a->name;
                });
                if (found != result.end())
                    continue; // if the dependency is already in the correct order, otherwise hold it among the unresolved ones

                // check if any module depends on this one
                found = find_if(notResolved.begin(), notResolved.end(), [&dep](auto &a) {
                    return dep.first == a->name;
                });

                if (found != result.end()) // check for circular dependency
                {

                    auto checkCircularDep = find_if((*found)->dependencies.begin(),
                                                    (*found)->dependencies.end(), [&it](auto &a) {
                                return (*it)->name == a.first; // found circular dependency
                            });
                    if (checkCircularDep != (*found)->dependencies.end())
                    {
                        stringstream sstr;
                        sstr << "Found circular dependency: \"" << (*it)->name << "\" and \"" << (*found)->name
                             << "\" depend on each other" << endl;
                        Utils::throwError(sstr.str());
                    }
                }

                resolved = false;
                break;
            }
            if (resolved)
            {
                LOG_APPEND(Log::LOG_INFO, "- %i) %s", currentIndex, (*it)->name.c_str());
                currentIndex++;

                result.push_back(*it);
                it = notResolved.erase(it);
            }
            else
                ++it;
        }
        if (notResolved.empty())
            break;
    }

    return result;
}

void LuaState::loadModules(const std::string &moduleDir, std::vector<std::string> *list)
{
    using namespace boost::filesystem;

    auto readConfig = [this](path homePath){
        const auto mainScript = "main.lua";
        if (!is_directory(homePath / "modules"))
            Utils::throwError(homePath.string() + ": No such directory.");
        for (const auto &moduleDir : directory_iterator(homePath / "modules"))
        {
            if (is_directory(moduleDir.status()) && exists(moduleDir.path() / mainScript))
            {
                boost::property_tree::ptree pt;
                auto _path = homePath.string() + "/modules/" + moduleDir.path().filename().string();
                boost::property_tree::read_json(_path + "/moduleInfo.json", pt);

                ServerModuleInfo moduleInfo;

                moduleInfo.path = make_pair(homePath.string(), moduleDir.path().filename().string());
                moduleInfo.author = pt.get<string>("author");
                moduleInfo.version = pt.get<string>("version");

                for (const auto &v : pt.get_child("dependencies"))
                    moduleInfo.dependencies.emplace_back(v.first, v.second.get_value<string>());

                auto name = pt.get<string>("name");

                moduleInfo.name = name;
                modules.push_back(move(moduleInfo));
            }
        }
    };


#ifdef _WIN32
    const char* libExt = ".dll";
#else
    const char* libExt = ".so";
#endif


    path envServerDir = moduleDir;

    if (envServerDir.empty())
        envServerDir = current_path();

    addGlobalPackagePath(envServerDir.string() + "/lib/lua/?/init.lua;" + envServerDir.string() + "/lib/lua/?.lua");
    addGlobalCPath(envServerDir.string() + "/lib/?" + libExt);
    readConfig(envServerDir);

    vector<vector<ServerModuleInfo>::iterator> sortedModuleList;
    if (list != nullptr && !list->empty()) // manual sorted list
    {
        int currentIndex = 1;

        LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Using manual order for server modules:");

        for (const auto &mssp : *list)
        {
            bool found = false;
            for (auto it = modules.begin(); it != modules.end(); ++it)
            {
                if (it->name == mssp)
                {
                    checkDependencies(modules, *it, false); // check dependencies, but do not throw exceptions

                    LOG_APPEND(Log::LOG_INFO, "- %i) %s", currentIndex, mssp.c_str());
                    currentIndex++;

                    sortedModuleList.push_back(it);
                    
                    found = true;
                    break;
                }
            }
            if (!found)
                Utils::throwError("Module: \"" + mssp + "\" not found");
        }
    }
    else
        sortedModuleList = loadOrderSolver(modules);

    for (auto &&module : sortedModuleList)
    {
        module->env = openModule(module->path.first, module->path.second);

        sol::table loaded = dataEnv["Core"]["loadedModules"];
        loaded.add(module->name);
        cout << "moduleName: " << module->name << endl;
    }

    dataEnv["Core"]["LOADED_MODULES"] = modules.size();
}
