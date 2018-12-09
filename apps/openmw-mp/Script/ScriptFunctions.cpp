#include "ScriptFunctions.hpp"
#include "API/PublicFnAPI.hpp"
#include <cstdarg>
#include <iostream>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Networking.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

template<typename... Types>
constexpr char TypeString<Types...>::value[];
constexpr ScriptFunctionData ScriptFunctions::functions[];
constexpr ScriptCallbackData ScriptFunctions::callbacks[];

using namespace std;

void ScriptFunctions::GetArguments(std::vector<boost::any> &params, va_list args, const std::string &def)
{
    params.reserve(def.length());

    try
    {
        for (char c : def)
        {
            switch (c)
            {
                case 'i':
                    params.emplace_back(va_arg(args, unsigned int));
                    break;

                case 'q':
                    params.emplace_back(va_arg(args, signed int));
                    break;

                case 'l':
                    params.emplace_back(va_arg(args, unsigned long long));
                    break;

                case 'w':
                    params.emplace_back(va_arg(args, signed long long));
                    break;

                case 'f':
                    params.emplace_back(va_arg(args, double));
                    break;

                case 'p':
                    params.emplace_back(va_arg(args, void*));
                    break;

                case 's':
                    params.emplace_back(va_arg(args, const char*));
                    break;

                case 'b':
                    params.emplace_back(va_arg(args, int));
                    break;

                default:
                    throw runtime_error("C++ call: Unknown argument identifier " + c);
            }
        }
    }

    catch (...)
    {
        va_end(args);
        throw;
    }
    va_end(args);
}
