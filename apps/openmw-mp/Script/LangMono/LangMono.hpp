//
// Created by koncord on 08.12.18.
//

#pragma once

#include <Script/Language.hpp>
#include <Script/SystemInterface.hpp>
#include <unordered_map>
#include <mono/metadata/object.h>

struct MethodKey
{
    inline bool operator==(const MethodKey &other) const
    {
        return other.paramsCnt == paramsCnt && other.name == name;
    }

    MethodKey(const std::string &name, int paramsCnt)
    {
        this->name = name;
        this->paramsCnt = paramsCnt;
    }

    std::string name;
    int paramsCnt;
};


namespace std
{
    template<>
    struct hash<MethodKey>
    {
        std::size_t operator()(const MethodKey &key) const
        {
            return hash<string>()(key.name)
                   ^ (hash<uint32_t>()(key.paramsCnt) >> 1);
        }
    };
}

struct MonoInstance
{
    MonoObject *object;
    MonoClass *klass;
    MonoAssembly *assembly;
    MonoImage *image;
};

class LangMono: public Language
{
    MonoInstance *instance;
    std::unordered_map<MethodKey, MonoMethod *> methodsCache;
public:
    virtual lib_t GetInterface() override;
    LangMono();
    LangMono(MonoInstance *instance);
    ~LangMono();
    virtual void LoadProgram(const char *filename) override;
    virtual int FreeProgram() override;
    virtual bool IsCallbackPresent(const char *name) override;
    virtual boost::any Call(const char *name, const char *argl, int buf, ...) override;
    virtual boost::any Call(const char *name, const char *argl, const std::vector<boost::any> &args) override;

private:
    void Init();
};
