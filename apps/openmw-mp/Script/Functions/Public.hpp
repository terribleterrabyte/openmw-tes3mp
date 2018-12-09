//
// Created by koncord on 09.12.18.
//

#ifndef OPENMW_PUBLIC_HPP
#define OPENMW_PUBLIC_HPP

#include <apps/openmw-mp/Script/ScriptFunction.hpp>

namespace PublicFunctions
{
    extern "C" void MakePublic(ScriptFunc _public, const char *name, char ret_type, const char *def) noexcept;
    extern "C" boost::any CallPublic(const char *name, va_list args) noexcept;
}

#endif
