//
// Created by koncord on 08.12.18.
//

#include <cstdarg>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object-forward.h>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>
#include <Script/ScriptFunctions.hpp>
#include <Script/API/TimerAPI.hpp>
#include "LangMono.hpp"

static MonoDomain *domain = nullptr; // shared domain

std::string monoStringToStdString(MonoString *monoString)
{
    char *utf8 = mono_string_to_utf8(monoString);
    std::string str = utf8;
    mono_free(utf8);
    return str;
}

template<typename T>
T unbox(MonoObject *obj)
{
    return *(T *) mono_object_unbox(obj);
}

boost::any monoObjectToAny(MonoObject *obj)
{

    MonoClass *klass = mono_object_get_class(obj);
    MonoType *rawType = mono_class_get_type(klass);

    switch ((MonoTypeEnum) mono_type_get_type(rawType))
    {
        case MONO_TYPE_END:
        case MONO_TYPE_VOID:
            break;
        case MONO_TYPE_BOOLEAN:
            return (bool) unbox<MonoBoolean>(obj);
        case MONO_TYPE_CHAR:
            return unbox<uint16_t>(obj);
        case MONO_TYPE_I1:
            return unbox<int8_t>(obj);
        case MONO_TYPE_U1:
            return unbox<uint8_t>(obj);
        case MONO_TYPE_I2:
            return unbox<int16_t>(obj);
        case MONO_TYPE_U2:
            return unbox<uint16_t>(obj);
        case MONO_TYPE_I4:
            return unbox<int32_t>(obj);
        case MONO_TYPE_U4:
            return unbox<uint32_t>(obj);
        case MONO_TYPE_I8:
            return unbox<int64_t>(obj);
        case MONO_TYPE_U8:
            return unbox<uint64_t>(obj);
        case MONO_TYPE_R4:
            return unbox<float>(obj);
        case MONO_TYPE_R8:
            return unbox<double>(obj);
        case MONO_TYPE_STRING:
            return monoStringToStdString((MonoString *) obj);
        case MONO_TYPE_ARRAY:
        case MONO_TYPE_SZARRAY:
        {
            MonoArrayType *arrayType = mono_type_get_array_type(rawType);
        }
        default:
            return boost::any();
    }
    return boost::any();
}

int LangMono::CreateTimerEx(MonoObject *delegate, long msec, MonoString *monoStr, MonoArray *monoArgs)
{
    size_t argsLength = mono_array_length(monoArgs);
    std::vector<boost::any> params (argsLength);
    try
    {
        for(size_t i = 0; i < argsLength; ++i)
            params[i] = monoObjectToAny(mono_array_get(monoArgs, MonoObject*, i));

        char *types = mono_string_to_utf8(monoStr);
        int id = mwmp::TimerAPI::CreateTimerMono(delegate, msec, types, params);
        mono_free(types);
        return id;
    }
    catch (...)
    {
        return -1;
    }
}

void LangMono::MakePublic(MonoObject *delegate, const char *name) noexcept
{

}

MonoObject *LangMono::CallPublic(const char *name, MonoArray *args)
{
    return nullptr;
}

lib_t LangMono::GetInterface()
{
    return nullptr;
}

LangMono::LangMono()
{
    instance = new MonoInstance;
}

LangMono::LangMono(MonoInstance *instance) : instance(instance)
{
}

LangMono::~LangMono()
{
    delete instance;
}

void LangMono::Init()
{
    if (domain != nullptr)
        return;

    if (Script::IsDebugMode())
    {
        std::string debugServerAddress = "127.0.0.1:10000";
        LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Waiting for debugger on %s...", debugServerAddress.c_str());
        std::string connectionString = "--debugger-agent=transport=dt_socket,server=y,address=" + debugServerAddress;
        std::vector<const char*> options {
                "--soft-breakpoints",
                connectionString.c_str()
        };
        mono_jit_parse_options(options.size(), (char**) options.data());

        mono_debug_init(MONO_DEBUG_FORMAT_MONO);
    }

    domain = mono_jit_init("TES3MP Mono VM");

    if (Script::IsDebugMode())
    {
        mono_debug_domain_create(domain);
    }

    mono_add_internal_call("TES3MPSharp.TES3MP::CreateTimerEx", (void*) &LangMono::CreateTimerEx);
    mono_add_internal_call("TES3MPSharp.TES3MP::MakePublic", (void*) &LangMono::MakePublic);
    mono_add_internal_call("TES3MPSharp.TES3MP::CallPublic", (void*) &LangMono::CallPublic);
}

void LangMono::Free()
{
    mono_domain_free(domain, 0);
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
    MonoAssembly *assembly = mono_domain_assembly_open(domain, filename);

    if(!assembly)
        throw std::runtime_error("Cannot load: " + std::string(filename));

    instance->assembly = assembly;
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

    std::vector<void *> vec(n_args);

    for (int index = 0; index < n_args; index++)
    {
        switch (argl[index])
        {
            case 'i':
            {
                auto val = va_arg(vargs, unsigned int);
                vec[index] = (void *) &val;
                break;
            }
            case 'q':
            {
                auto val = va_arg(vargs, signed int);
                vec[index] = (void *) &val;
                break;
            }
            case 'l':
            {
                auto val = va_arg(vargs, unsigned long long);
                vec[index] = (void *) &val;
                break;
            }
            case 'w':
            {
                auto val = va_arg(vargs, signed long long);
                vec[index] = (void *) &val;
                break;
            }
            case 'f':
            {
                auto val = va_arg(vargs, double);
                vec[index] = (void *) &val;
                break;
            }
            case 'p':
            {
                auto val = va_arg(vargs, void*);
                vec[index] = (void *) &val;
                break;
            }
            case 's':
            {
                vec[index] = (mono_string_new(mono_domain_get(), va_arg(vargs, const char*)));
                break;
            }
            case 'b':
            {
                auto val = va_arg(vargs, int);
                vec[index] = (void *) &val;
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

    if (method == nullptr)
        return boost::any();

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
