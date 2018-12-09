#include "Settings.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

extern "C" void SettingFunctions::SetDifficulty(unsigned short pid, int difficulty)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->difficulty = difficulty;
}

extern "C" void SettingFunctions::SetEnforcedLogLevel(unsigned short pid, int enforcedLogLevel)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->enforcedLogLevel = enforcedLogLevel;
}

extern "C" void SettingFunctions::SetPhysicsFramerate(unsigned short pid, double physicsFramerate)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->physicsFramerate = physicsFramerate;
}

extern "C" void SettingFunctions::SetConsoleAllowed(unsigned short pid, bool state)
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->consoleAllowed = state;
}

extern "C" void SettingFunctions::SetBedRestAllowed(unsigned short pid, bool state)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->bedRestAllowed = state;
}

extern "C" void SettingFunctions::SetWildernessRestAllowed(unsigned short pid, bool state)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->wildernessRestAllowed = state;
}

extern "C" void SettingFunctions::SetWaitAllowed(unsigned short pid, bool state)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->waitAllowed = state;
}

extern "C" void SettingFunctions::SendSettings(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_SETTINGS);
    packet->setPlayer(player);

    packet->Send(false);
}
