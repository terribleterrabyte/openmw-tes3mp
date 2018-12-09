#include "Mechanics.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

static std::string tempCellDescription;

extern "C" unsigned char MechanicsFunctions::GetMiscellaneousChangeType(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->miscellaneousChangeType;
}

extern "C" const char *MechanicsFunctions::GetMarkCell(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    tempCellDescription = player->cell.getDescription().c_str();
    return tempCellDescription.c_str();
}

extern "C" double MechanicsFunctions::GetMarkPosX(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->markPosition.pos[0];
}

extern "C" double MechanicsFunctions::GetMarkPosY(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->markPosition.pos[1];
}

extern "C" double MechanicsFunctions::GetMarkPosZ(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->markPosition.pos[2];
}

extern "C" double MechanicsFunctions::GetMarkRotX(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->markPosition.rot[0];
}

extern "C" double MechanicsFunctions::GetMarkRotZ(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->markPosition.rot[2];
}

extern "C" bool MechanicsFunctions::DoesPlayerHavePlayerKiller(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, false);

    return player->killer.isPlayer;
}

extern "C" int MechanicsFunctions::GetPlayerKillerPid(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    Player *killer = Players::getPlayer(player->killer.guid);

    if (killer != nullptr)
        return killer->getId();

    return -1;
}

extern "C" const char *MechanicsFunctions::GetPlayerKillerRefId(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->killer.refId.c_str();
}

extern "C" unsigned int MechanicsFunctions::GetPlayerKillerRefNum(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->killer.refNum;
}

extern "C" unsigned int MechanicsFunctions::GetPlayerKillerMpNum(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->killer.mpNum;
}

extern "C" const char *MechanicsFunctions::GetPlayerKillerName(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->killer.name.c_str();
}

extern "C" const char *MechanicsFunctions::GetSelectedSpellId(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->selectedSpellId.c_str();
}

extern "C" unsigned int MechanicsFunctions::GetDrawState(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, false);

    return player->drawState;
}

extern "C" bool MechanicsFunctions::GetSneakState(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, false);

    // TODO: Avoid having to use a magic number here
    return (player->movementFlags & 8) != 0;
}

extern "C" void MechanicsFunctions::SetMarkCell(unsigned short pid, const char *cellDescription) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->markCell = Utils::getCellFromDescription(cellDescription);
}

extern "C" void MechanicsFunctions::SetMarkPos(unsigned short pid, double x, double y, double z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->markPosition.pos[0] = x;
    player->markPosition.pos[1] = y;
    player->markPosition.pos[2] = z;
}

extern "C" void MechanicsFunctions::SetMarkRot(unsigned short pid, double x, double z) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->markPosition.rot[0] = x;
    player->markPosition.rot[2] = z;
}

extern "C" void MechanicsFunctions::SetSelectedSpellId(unsigned short pid, const char *spellId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->selectedSpellId = spellId;
}

extern "C" void MechanicsFunctions::SendMarkLocation(unsigned short pid)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->miscellaneousChangeType = mwmp::MISCELLANEOUS_CHANGE_TYPE::MARK_LOCATION;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_MISCELLANEOUS);
    packet->setPlayer(player);
    
    packet->Send(false);
}

extern "C" void MechanicsFunctions::SendSelectedSpell(unsigned short pid)
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->miscellaneousChangeType = mwmp::MISCELLANEOUS_CHANGE_TYPE::SELECTED_SPELL;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_MISCELLANEOUS);
    packet->setPlayer(player);
    
    packet->Send(false);
}

extern "C" void MechanicsFunctions::Jail(unsigned short pid, int jailDays, bool ignoreJailTeleportation, bool ignoreJailSkillIncreases,
                              const char* jailProgressText, const char* jailEndText) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->jailDays = jailDays;
    player->ignoreJailTeleportation = ignoreJailTeleportation;
    player->ignoreJailSkillIncreases = ignoreJailSkillIncreases;
    player->jailProgressText = jailProgressText;
    player->jailEndText = jailEndText;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_JAIL);
    packet->setPlayer(player);
    
    packet->Send(false);
}

extern "C" void MechanicsFunctions::Resurrect(unsigned short pid, unsigned int type) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->resurrectType = type;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_RESURRECT);
    packet->setPlayer(player);

    packet->Send(false);
    packet->Send(true);
}

// All methods below are deprecated versions of methods from above

extern "C" const char *MechanicsFunctions::GetDeathReason(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (player->killer.isPlayer)
    {
        Player *killerPlayer = Players::getPlayer(player->killer.guid);

        if (killerPlayer != nullptr)
            return killerPlayer->npc.mName.c_str();
    }
    else if (!player->killer.name.empty())
        return player->killer.name.c_str();

    return "suicide";
}

extern "C" unsigned int MechanicsFunctions::GetPlayerKillerRefNumIndex(unsigned short pid) noexcept
{
    return GetPlayerKillerRefNum(pid);
}
