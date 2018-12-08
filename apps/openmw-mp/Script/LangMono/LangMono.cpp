//
// Created by koncord on 08.12.18.
//

#include <cstdarg>
#include <mono/metadata/appdomain.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include "LangMono.hpp"

static MonoDomain *domain = nullptr; // shared domain


lib_t LangMono::GetInterface()
{
    return nullptr;
}

LangMono::LangMono()
{
    instance = new MonoInstance;

    Init();
}

LangMono::LangMono(MonoInstance *instance) : instance(instance)
{
    Init();
}

LangMono::~LangMono()
{
    delete instance;
}

void LangMono::Init()
{
    if (domain != nullptr)
        return;

    domain = mono_jit_init("TES3MP Mono VM"); // will leak :P
}

std::vector<MonoClass *> getInstanceClassList(MonoImage *image, const std::string &parentName)
{
    std::vector<MonoClass *> classes;

    const MonoTableInfo *tableInfo = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);

    int rows = mono_table_info_get_rows(tableInfo);

    for (int i = 0; i < rows; i++)
    {
        MonoClass *klass = nullptr;
        uint32_t cols[MONO_TYPEDEF_SIZE];
        mono_metadata_decode_row(tableInfo, i, cols, MONO_TYPEDEF_SIZE);
        const char *name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
        const char *nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
        klass = mono_class_from_name(image, nameSpace, name);

        if (klass == nullptr)
            continue;

        MonoClass *parent = mono_class_get_parent(klass);
        if (parent != nullptr && parentName == mono_class_get_name(parent))
            classes.push_back(klass);
    }
    return classes;
}

void LangMono::LoadProgram(const char *filename)
{
    instance->assembly = mono_domain_assembly_open(domain, filename);
    instance->image = mono_assembly_get_image(instance->assembly);

    std::vector<MonoClass *> list = getInstanceClassList(instance->image, "Instance");
    for (auto &&klass : list)
    {
        instance->object = mono_object_new(domain, klass);
        mono_runtime_object_init(instance->object); // call default ctor

        instance->klass = klass;
    }
}

int LangMono::FreeProgram()
{
    for(auto &&method : methodsCache)
        mono_free_method(method.second);

    return 0;
}

bool LangMono::IsCallbackPresent(const char *name)
{
    return true;
}

boost::any LangMono::Call(const char *name, const char *argl, int buf, ...)
{
    va_list vargs;
    va_start(vargs, buf);

    int n_args = (int) (strlen(argl));

    std::vector<void *> vec;
    vec.reserve(n_args);

    for (int index = 0; index < n_args; index++)
    {
        switch (argl[index])
        {
            case 'i':
            {
                auto val = va_arg(vargs, unsigned int);
                vec.push_back((void *) &val);
                break;
            }
            case 'q':
            {
                auto val = va_arg(vargs, signed int);
                vec.push_back((void *) &val);
                break;
            }
            case 'l':
            {
                auto val = va_arg(vargs, unsigned long long);
                vec.push_back((void *) &val);
                break;
            }
            case 'w':
            {
                auto val = va_arg(vargs, signed long long);
                vec.push_back((void *) &val);
                break;
            }
            case 'f':
            {
                auto val = va_arg(vargs, double);
                vec.push_back((void *) &val);
                break;
            }
            case 'p':
            {
                auto val = va_arg(vargs, void*);
                vec.push_back((void *) &val);
                break;
            }
            case 's':
            {
                vec.push_back(mono_string_new(mono_domain_get(), va_arg(vargs, const char*)));
                break;
            }
            case 'b':
            {
                auto val = va_arg(vargs, int);
                vec.push_back((void *) &val);
                break;
            }

            default:
                throw std::runtime_error("Mono call: Unknown argument identifier " + argl[index]);
        }
    }

    va_end(vargs);

    MonoMethod *method;
    auto it = methodsCache.find({name, n_args});
    if (it != methodsCache.end())
    {
        method = it->second;
    } else
    {
        method = mono_class_get_method_from_name(instance->klass, name, n_args);
        methodsCache[{name, n_args}] = method;
    }

    MonoObject *ret = mono_runtime_invoke(method, instance->object, vec.data(), nullptr);
    if (ret)
        return boost::any(mono_object_unbox(ret));
    else
        return boost::any();
}

boost::any LangMono::Call(const char *name, const char *argl, const std::vector<boost::any> &args)
{
    int n_args = args.size();

    std::vector<void *> vec(n_args);

    for (int index = 0; index < n_args; index++)
    {
        switch (argl[index])
        {
            case 'i':
            {
                auto val = boost::any_cast<unsigned int>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }
            case 'q':
            {
                auto val = boost::any_cast<signed int>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }
            case 'l':
            {
                auto val = boost::any_cast<unsigned long long>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }
            case 'w':
            {
                auto val = boost::any_cast<signed long long>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }
            case 'f':
            {
                auto val = boost::any_cast<double>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }
            case 'p':
            {
                auto val = boost::any_cast<void *>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }
            case 's':
            {
                auto val = mono_string_new(mono_domain_get(), boost::any_cast<const char *>(args.at(index)));
                vec[index] = (val);
                break;
            }
            case 'b':
            {
                auto val = boost::any_cast<int>(args.at(index));
                vec[index] = ((void *) &val);
                break;
            }

            default:
                throw std::runtime_error("Mono call: Unknown argument identifier " + argl[index]);
        }
    }

    MonoMethod *method;
    auto it = methodsCache.find({name, n_args});
    if (it != methodsCache.end())
    {
        method = it->second;
    }
    else
    {
        method = mono_class_get_method_from_name(instance->klass, name, n_args);
        methodsCache[{name, n_args}] = method;
    }

    MonoObject *ret = mono_runtime_invoke(method, instance->object, vec.data(), nullptr);
    if (ret)
        return boost::any(mono_object_unbox(ret));
    else
        return boost::any();
}
