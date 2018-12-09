#include "Positions.hpp"
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

extern "C" void PositionFunctions::GetPos(unsigned short pid, float *x, float *y, float *z) noexcept
{
    *x = 0.00;
    *y = 0.00;
    *z = 0.00;

    Player *player;
    GET_PLAYER(pid, player,);

    *x = player->position.pos[0];
    *y = player->position.pos[1];
    *z = player->position.pos[2];
}

extern "C" double PositionFunctions::GetPosX(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->position.pos[0];
}

extern "C" double PositionFunctions::GetPosY(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->position.pos[1];
}

extern "C" double PositionFunctions::GetPosZ(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->position.pos[2];
}

extern "C" double PositionFunctions::GetPreviousCellPosX(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->previousCellPosition.pos[0];
}

extern "C" double PositionFunctions::GetPreviousCellPosY(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->previousCellPosition.pos[1];
}

extern "C" double PositionFunctions::GetPreviousCellPosZ(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->previousCellPosition.pos[2];
}

extern "C" void PositionFunctions::GetRot(unsigned short pid, float *x, float *y, float *z) noexcept
{
    *x = 0.00;
    *y = 0.00;
    *z = 0.00;

    Player *player;
    GET_PLAYER(pid, player, );

    *x = player->position.rot[0];
    *y = player->position.rot[1];
    *z = player->position.rot[2];
}

extern "C" double PositionFunctions::GetRotX(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->position.rot[0];
}

extern "C" double PositionFunctions::GetRotZ(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->position.rot[2];
}

extern "C" void PositionFunctions::SetPos(unsigned short pid, double x, double y, double z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->position.pos[0] = x;
    player->position.pos[1] = y;
    player->position.pos[2] = z;
}

extern "C" void PositionFunctions::SetRot(unsigned short pid, double x, double z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->position.rot[0] = x;
    player->position.rot[2] = z;
}

extern "C" void PositionFunctions::SetMomentum(unsigned short pid, double x, double y, double z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->momentum.pos[0] = x;
    player->momentum.pos[1] = y;
    player->momentum.pos[2] = z;
}

extern "C" void PositionFunctions::SendPos(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_POSITION);
    packet->setPlayer(player);

    packet->Send(false);
}

extern "C" void PositionFunctions::SendMomentum(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_MOMENTUM);
    packet->setPlayer(player);

    packet->Send(false);
}
