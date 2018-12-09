//
// Created by koncord on 09.12.18.
//

#include "Public.hpp"

#include <Script/ScriptFunctions.hpp>
#include <Script/API/PublicFnAPI.hpp>

extern "C" void PublicFunctions::MakePublic(ScriptFunc _public, const char *name, char ret_type, const char *def) noexcept
{
    Public::MakePublic(_public, name, ret_type, def);
}

extern "C" boost::any PublicFunctions::CallPublic(const char *name, va_list args) noexcept
{
    std::vector<boost::any> params;

    try
    {
        std::string def = Public::GetDefinition(name);
        ScriptFunctions::GetArguments(params, args, def);

        return Public::Call(name, params);
    }
    catch (...) {}

    return 0;
}
