//
// Created by koncord on 19.03.16.
//

#include "Script.hpp"
#include "LangNative/LangNative.hpp"

#if defined (ENABLE_LUA)
#include "LangLua/LangLua.hpp"
#endif

#ifdef ENABLE_MONO
#include "LangMono/LangMono.hpp"
#endif

using namespace std;

Script::ScriptList Script::scripts;
bool Script::debugMode = false;

inline bool Load(Language *lang, const std::string &path)
{
    try
    {
        lang->LoadProgram(path.c_str());
    }
    catch (...)
    {
        lang->FreeProgram();
        throw std::runtime_error("Failed to load: " + path);
    }
}

Script::Script(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (!file)
        throw runtime_error("Script not found: " + string(path));

    fclose(file);

    if (strstr(path, ".dll"))
    {
#ifdef ENABLE_MONO
        script_type = SCRIPT_MONO;
        try
        {
            lang = new LangMono();
            Load(lang, path);
        }
        catch(...)
        {
#endif
#ifdef _WIN32
        script_type = SCRIPT_CPP;
        lang = new LangNative();
        Load(lang, path);
#endif
#ifdef ENABLE_MONO
        }
#endif
    }
#ifndef _WIN32
    else if (strstr(path, ".so"))
    {
        script_type = SCRIPT_CPP;
        lang = new LangNative();
        Load(lang, path);
    }
#endif
#if defined (ENABLE_LUA)
    else if (strstr(path, ".lua") || strstr(path, ".t"))
    {
        script_type = SCRIPT_LUA;
        lang = new LangLua();
        Load(lang, path);
    }
#endif
    else
        throw runtime_error("Script type not recognized: " + string(path));
}


Script::~Script()
{
    lang->FreeProgram();

    delete lang;
}

void Script::LoadScripts(char *scripts, const char *base)
{
    char *token = strtok(scripts, ",");

    try
    {
        while (token)
        {
            char path[4096];
            snprintf(path, sizeof(path), Utils::convertPath("%s/%s/%s").c_str(), base, "scripts", token);
            Script::scripts.emplace_back(new Script(path));
            token = strtok(nullptr, ",");
        }
    }
    catch (...)
    {
        UnloadScripts();
        throw;
    }
}

void Script::UnloadScripts()
{
    //Public::DeleteAll();
    scripts.clear();
}

void Script::LoadScript(const char *script, const char *base)
{
    char path[4096];
    snprintf(path, sizeof(path), Utils::convertPath("%s/%s/%s").c_str(), base, "scripts", script);
    Script::scripts.emplace_back(new Script(path));
}


bool Script::IsDebugMode()
{
    return debugMode;
}

void Script::EnableDebugMode()
{
    debugMode = true;
}

void Script::Init()
{
#ifdef ENABLE_MONO
    LangMono::Init();
#endif
#ifdef ENABLE_LUA
    LangLua::Init();
#endif
    LangNative::Init();
}

void Script::Free()
{
#ifdef ENABLE_MONO
    LangMono::Free();
#endif
#ifdef ENABLE_LUA
    LangLua::Free();
#endif
    LangNative::Free();
}
