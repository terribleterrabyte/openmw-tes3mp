#include "Shapeshift.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

extern "C" double ShapeshiftFunctions::GetScale(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->scale;
}

extern "C" bool ShapeshiftFunctions::IsWerewolf(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->isWerewolf;
}

extern "C" const char *ShapeshiftFunctions::GetCreatureRefId(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->creatureRefId.c_str();
}

extern "C" bool ShapeshiftFunctions::GetCreatureNameDisplayState(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->displayCreatureName;
}

extern "C" void ShapeshiftFunctions::SetScale(unsigned short pid, double scale) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->scale = scale;
}

extern "C" void ShapeshiftFunctions::SetWerewolfState(unsigned short pid, bool isWerewolf) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->isWerewolf = isWerewolf;
}

extern "C" void ShapeshiftFunctions::SetCreatureRefId(unsigned short pid, const char *refId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->creatureRefId = refId;
}

extern "C" void ShapeshiftFunctions::SetCreatureNameDisplayState(unsigned short pid, bool displayState) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->displayCreatureName = displayState;
}

extern "C" void ShapeshiftFunctions::SendShapeshift(unsigned short pid)
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_SHAPESHIFT);
    packet->setPlayer(player);

    packet->Send(false);
    packet->Send(true);
}
