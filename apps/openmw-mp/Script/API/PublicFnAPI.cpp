//
// Created by koncord on 14.05.16.
//

#include <Script/ScriptFunction.hpp>
#include "PublicFnAPI.hpp"

using namespace std;

unordered_map<string, Public *> Public::publics;

Public::~Public()
{

}

Public::Public(ScriptFunc _public, const std::string &name, char ret_type, const std::string &def) : ScriptFunction(_public, ret_type, def)
{
    publics.emplace(name, this);
}

#ifdef ENABLE_LUA
Public::Public(ScriptFuncLua _public, lua_State *lua, const std::string &name, char ret_type, const std::string &def) : ScriptFunction(
        _public, lua, ret_type, def)
{
    publics.emplace(name, this);
}
#endif

#ifdef ENABLE_MONO
Public::Public(MonoObject *delegate, const std::string &name, char ret_type, const std::string &def) :
    ScriptFunction(delegate, ret_type, def)
{
    publics.emplace(name, this);
}
#endif

boost::any Public::Call(const std::string &name, const std::vector<boost::any> &args)
{
    auto it = publics.find(name);
    if (it == publics.end())
        throw runtime_error("Public with name \"" + name + "\" does not exist");

    return it->second->ScriptFunction::Call(args);
}


const std::string &Public::GetDefinition(const std::string &name)
{
    auto it = publics.find(name);

    if (it == publics.end())
        throw runtime_error("Public with name \"" + name + "\" does not exist");

    return it->second->def;
}

Public *Public::GetPublic(const std::string &name)
{
    auto it = publics.find(name);

    if (it == publics.end())
        throw runtime_error("Public with name \"" + name + "\" does not exist");
    return it->second;
}


bool Public::IsLua(const std::string &name)
{
#if !defined(ENABLE_LUA)
    return false;
#else
    auto it = publics.find(name);
    if (it == publics.end())
        throw runtime_error("Public with name \"" + name + "\" does not exist");

    return it->second->script_type == SCRIPT_LUA;
#endif
}

void Public::DeleteAll()
{
    for (auto it = publics.begin(); it != publics.end(); it++)
    {
        Public *_public = it->second;
        delete _public;
        publics.erase(it);
    }
}
