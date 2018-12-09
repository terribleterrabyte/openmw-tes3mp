//
// Created by koncord on 15.03.16.
//

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <Player.hpp>
#include <Networking.hpp>
#include <Script/API/TimerAPI.hpp>

using namespace std;
using namespace mwmp;

extern "C" int TimerFunctions::CreateTimer(ScriptFunc callback, int msec) noexcept
{
    return mwmp::TimerAPI::CreateTimer(callback, msec, "", vector<boost::any>());
}

extern "C" int TimerFunctions::CreateTimerEx(ScriptFunc callback, int msec, const char *types, va_list args) noexcept
{
    try
    {
        vector<boost::any> params;
        ScriptFunctions::GetArguments(params, args, types);

        return mwmp::TimerAPI::CreateTimer(callback, msec, types, params);
    }
    catch (...)
    {
        return -1;
    }

}

extern "C" void TimerFunctions::StartTimer(int timerId) noexcept
{
    TimerAPI::StartTimer(timerId);
}

extern "C" void TimerFunctions::StopTimer(int timerId) noexcept
{
    TimerAPI::StopTimer(timerId);
}

extern "C" void TimerFunctions::RestartTimer(int timerId, int msec) noexcept
{
    TimerAPI::ResetTimer(timerId, msec);
}

extern "C" void TimerFunctions::FreeTimer(int timerId) noexcept
{
    TimerAPI::FreeTimer(timerId);
}

extern "C" bool TimerFunctions::IsTimerElapsed(int timerId) noexcept
{
    return TimerAPI::IsEndTimer(timerId);
}
