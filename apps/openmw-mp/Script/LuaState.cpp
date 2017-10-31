//
// Created by koncord on 01.08.17.
//

#include <iostream>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <components/misc/stringops.hpp>
#include <apps/openmw/mwworld/inventorystore.hpp>
#include <apps/openmw-mp/Networking.hpp>
#include <components/openmw-mp/Version.hpp>
#include <apps/openmw-mp/GUI.hpp>
#include <apps/openmw-mp/Dialogue.hpp>
#include <apps/openmw-mp/Factions.hpp>
#include <apps/openmw-mp/Quests.hpp>
#include <apps/openmw-mp/Spells.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "LuaState.hpp"
#include "EventController.hpp"
#include "luaUtils.hpp"
#include "CommandController.hpp"
#include "../Inventory.hpp"
#include "../Settings.hpp"
#include "../Players.hpp"
#include "../Networking.hpp"
#include "../MasterClient.hpp"

using namespace std;


#if defined(SOL_SAFE_FUNCTIONS) && defined(WIN32)
inline int errHandler(lua_State *L)
{
    string msg = "An unknown error has triggered the default error handler";
    auto maybetopmsg = sol::stack::check_get<sol::string_view>(L, 1);
    if (maybetopmsg)
    {
        const sol::string_view &topmsg = maybetopmsg.value();
        msg.assign(topmsg.data(), topmsg.size());
    }
    luaL_tramceback(L, L, msg.c_str(), 1);
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

    Players::Init(*this);

    timerCtrl = make_unique<TimerController>();
    TimerController::Init(*this);
    Timer::Init(*this);

    CommandController::Init(*this);

    dataEnv = sol::environment(*lua, sol::create, lua->globals());
    lua->set("Data", dataEnv); // plain global environment for communicating between mods
    auto coreTable = dataEnv.create("Core");
    coreTable["VERSION"] = TES3MP_VERSION;
    coreTable["PROTOCOL"] = TES3MP_PROTO_VERSION;
    coreTable["loadedMods"] = coreTable.create();

    configEnv = sol::environment(*lua, sol::create, lua->globals());
    lua->set("Config", configEnv); // plain global environment for mod configuration

    // Enable a special Sol error handler for Windows, because exceptions aren't caught properly
    // in main.cpp for it
#if defined(SOL_SAFE_FUNCTIONS) && defined(WIN32)
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

    lua->set_function("setModname", [](const std::string &modname) {
        auto mc = mwmp::Networking::getPtr()->getMasterClient();
        if (mc)
            mc->SetModname(modname);
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
        Players::for_each([&hour, &packet](std::shared_ptr<Player> player){
            player->hour = hour;
            player->month = -1;
            player->day = -1;

            packet->setPlayer(player.get());
            packet->Send(false);
        });
    });

    lua->set_function("setMonth", [](int month) {

        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_TIME);
        Players::for_each([&month, &packet](std::shared_ptr<Player> player){
            player->hour = -1;
            player->month = month;
            player->day = -1;

            packet->setPlayer(player.get());
            packet->Send(false);
        });
    });

    lua->set_function("setDay", [](int day) {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_TIME);
        Players::for_each([&day, &packet](std::shared_ptr<Player> player){
            player->hour = -1;
            player->month = -1;
            player->day = day;

            packet->setPlayer(player.get());
            packet->Send(false);
        });
    });
}

sol::environment LuaState::openScript(std::string homePath, std::string modname)
{
    cout << "Loading file: " << homePath + "/mods/" + modname + "/main.lua" << endl;

    sol::environment env(*lua, sol::create, lua->globals());
    std::string package_path = env["package"]["path"];
    env["package"]["path"] = Utils::convertPath(homePath + "/mods/" + modname + "/?.lua") + ";" + package_path;
    package_path = env["package"]["path"];

    lua->set_function("getDataFolder", [homePath, modname]() -> const string {
        return homePath + "/data/" + modname + '/';
    });

    lua->set_function("getModFolder", [homePath, modname]() -> const string{
        return homePath + "/mods/" + modname + '/';
    });

    lua->script_file(homePath + "/mods/" + modname + "/main.lua", env);

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

int CompVersion(const string &wishVersion, const string &depVersionFound)
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
    int bellowExpected = 0;

    for (int i = 0; i < 3; ++i)
    {
        auto v1 = boost::lexical_cast<int>(*(wishIter++));
        auto v2 = boost::lexical_cast<int>(*(founditer++));

        if (v2 > v1 && startVer > 0)
            return 0; // found applicable version

        if (v2 <= v1)
        {
            if (v2 == v1 && startVer == 1)
                bellowExpected++;
            else if (v2 < v1)
                return -1; // found version below expected
            continue;
        }

        return 1; // version higher than expected
    }

    if (bellowExpected == 3)
        return -1; // found version below expected

    return 0;
}

void checkDependencies(const vector<ServerPluginInfo> &mods, const ServerPluginInfo &spi, bool fatal = true)
{
    for (auto &dependency : spi.dependencies)
    {
        const std::string &depNameRequest = dependency.first;
        const std::string &depVersionRequest = dependency.second;

        const auto &depEnvIt = find_if(mods.begin(), mods.end(), [&depNameRequest](const auto &val) {
            return val.name == depNameRequest;
        });

        if (depEnvIt != mods.end())
        {
            const string &depVersionFound = depEnvIt->version;
            if (CompVersion(depVersionRequest, depVersionFound) != 0)
            {
                stringstream sstr;
                sstr << depNameRequest << ": version \"" << depVersionFound << "\" is not applicable for \""
                     << spi.name << "\" expected \"" << depVersionRequest + "\"";
                if(fatal)
                    throw runtime_error(sstr.str());
                else
                    LOG_MESSAGE_SIMPLE(Log::LOG_WARN, "%s", sstr.str().c_str());
            }
        }
        else // dependency not found.
        {
            stringstream sstr;
            sstr << depNameRequest + " \"" << depVersionRequest << "\" not found.";
            if(fatal)
                throw runtime_error(sstr.str());
            else
                LOG_MESSAGE_SIMPLE(Log::LOG_WARN, "%s", sstr.str().c_str());
        }
    }
}

vector<vector<ServerPluginInfo>::iterator> loadOrderSolver(vector<ServerPluginInfo> &mods)
{
    vector<vector<ServerPluginInfo>::iterator> notResolved;
    vector<vector<ServerPluginInfo>::iterator> result;

    for (auto it = mods.begin(); it != mods.end(); ++it)
    {
        checkDependencies(mods, *it);

        if (it->dependencies.empty()) // if server plugin doesn't have any dependencies we can safely put it on result
            result.push_back(it);
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
                    continue; // if dependency already in correct order, otherwise hold plugin in unresolved

                // check if someone depends on this plugin
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
                        throw runtime_error(sstr.str());
                    }
                }

                resolved = false;
                break;
            }
            if (resolved)
            {
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

void LuaState::loadMods(const std::string &modDir, std::vector<std::string> *list)
{
    using namespace boost::filesystem;

    auto readConfig = [this](path homePath){
        const auto mainScript = "main.lua";
        if (!is_directory(homePath / "mods"))
            throw runtime_error(homePath.string() + ": No such directory.");
        for (const auto &modDir : directory_iterator(homePath / "mods"))
        {
            if (is_directory(modDir.status()) && exists(modDir.path() / mainScript))
            {
                boost::property_tree::ptree pt;
                auto _path = homePath.string() + "/mods/" + modDir.path().filename().string();
                boost::property_tree::read_json(_path + "/modinfo.json", pt);

                ServerPluginInfo modInfo;

                modInfo.path = make_pair(homePath.string(), modDir.path().filename().string());
                modInfo.author = pt.get<string>("author");
                modInfo.version = pt.get<string>("version");

                for(const auto &v : pt.get_child("dependencies"))
                    modInfo.dependencies.emplace_back(v.first, v.second.get_value<string>());

                auto name = pt.get<string>("name");

                modInfo.name = name;
                mods.push_back(move(modInfo));
            }
        }
    };


#ifdef _WIN32
    const char* libExt = ".dll";
#else
    const char* libExt = ".so";
#endif


    path envServerDir = modDir;

    if (envServerDir.empty())
        envServerDir = current_path();

    addGlobalPackagePath(envServerDir.string() + "/lib/lua/?/init.lua;" + envServerDir.string() + "/lib/lua/?.lua");
    addGlobalCPath(envServerDir.string() + "/lib/?" + libExt);
    readConfig(envServerDir);

    vector<vector<ServerPluginInfo>::iterator> sortedPluginList;
    if (list != nullptr && !list->empty()) // manual sorted list
    {
        for (const auto &mssp : *list)
        {
            bool found = false;
            for (auto it = mods.begin(); it != mods.end(); ++it)
            {
                if (it->name == mssp)
                {
                    checkDependencies(mods, *it, false); // check dependencies, but do not throw exceptions
                    sortedPluginList.push_back(it);
                    found = true;
                    break;
                }
            }
            if (!found)
                throw runtime_error("Plugin: \"" + mssp + "\" not found");
        }
    }
    else
        sortedPluginList = loadOrderSolver(mods);

    for (auto &&mod : sortedPluginList)
    {
        mod->env = openScript(mod->path.first, mod->path.second);

        sol::table loaded = dataEnv["Core"]["loadedMods"];
        loaded.add(mod->name);
        cout << "modname: " << mod->name << endl;
    }

    dataEnv["Core"]["LOADED_MODS"] = mods.size();
}
