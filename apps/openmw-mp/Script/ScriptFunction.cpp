//
// Created by koncord on 23.01.16.
//

#include<iostream>
#include <stdexcept>
#include "ScriptFunction.hpp"

#if defined (ENABLE_LUA)
#include "LangLua/LangLua.hpp"
#endif

using namespace std;

ScriptFunction::ScriptFunction(ScriptFunc fCpp,char ret_type, const string &def) :
        fCpp(fCpp), ret_type(ret_type), def(def), script_type(SCRIPT_CPP)
{

}
#if defined (ENABLE_LUA)
ScriptFunction::ScriptFunction(const ScriptFuncLua &fLua, lua_State *lua, char ret_type, const std::string &def) :
        fLua({lua, fLua}), ret_type(ret_type), def(def), script_type(SCRIPT_LUA)
{

}
#endif
#if defined (ENABLE_MONO)
ScriptFunction::ScriptFunction(MonoObject *delegate, char ret_type, const std::string &def) :
        fMono({delegate}), ret_type(ret_type), def(def), script_type(SCRIPT_MONO)
{
}
#endif

ScriptFunction::~ScriptFunction()
{
#if defined (ENABLE_LUA)
    if (script_type == SCRIPT_LUA)
        fLua.name.~ScriptFuncLua();
#endif
}

boost::any ScriptFunction::Call(const vector<boost::any> &args)
{
    boost::any result = boost::any();

    if (def.length() != args.size())
        throw runtime_error("Script call: Number of arguments does not match definition");
#if defined (ENABLE_LUA)
    else if (script_type == SCRIPT_LUA)
    {
        LangLua langLua(fLua.lua);
        boost::any any = langLua.Call(fLua.name.c_str(), def.c_str(), args);

        switch (ret_type)
        {
            case 'i':
                result = boost::any_cast<luabridge::LuaRef>(any).cast<unsigned int>();
                break;
            case 'q':
                result = boost::any_cast<luabridge::LuaRef>(any).cast<signed int>();
                break;
            case 'f':
                result = boost::any_cast<luabridge::LuaRef>(any).cast<double>();
                break;
            case 's':
                result = boost::any_cast<luabridge::LuaRef>(any).cast<const char*>();
                break;
            case 'v':
                break;
            default:
                throw runtime_error("Lua call: Unknown return type" + ret_type);
        }
    }
#endif
#if defined (ENABLE_MONO)
    else if (script_type == SCRIPT_MONO)
    {
        std::vector<void*> argList;
        argList.resize(args.size());

        for (int index = 0; index < args.size(); index++)
        {
            switch (def[index])
            {
                case 'i':
                {
                    auto val = boost::any_cast<unsigned int>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }
                case 'q':
                {
                    auto val = boost::any_cast<signed int>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }
                case 'l':
                {
                    auto val = boost::any_cast<unsigned long long>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }
                case 'w':
                {
                    auto val = boost::any_cast<signed long long>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }
                case 'f':
                {
                    auto val = boost::any_cast<double>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }
                case 'p':
                {
                    auto val = boost::any_cast<void *>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }
                case 's':
                {
                    if (args.at(index).type() == typeid(std::string)) // mono to mono call
                        argList[index] = mono_string_new(mono_domain_get(), boost::any_cast<std::string>(args.at(index)).c_str());
                    else // lua to mono
                        argList[index] = mono_string_new(mono_domain_get(), boost::any_cast<const char *>(args.at(index)));
                    break;
                }
                case 'b':
                {
                    auto val = boost::any_cast<int>(args.at(index));
                    argList[index] = ((void *) &val);
                    break;
                }

                default:
                    throw std::runtime_error("Call: Unknown argument identifier " + def[index]);
            }
        }

        MonoObject *monoRet = mono_runtime_delegate_invoke(fMono.delegate, argList.data(), NULL);
        if (monoRet != nullptr)
            result = mono_object_unbox(monoRet); // todo cast

    }
#endif

    return result;
}
