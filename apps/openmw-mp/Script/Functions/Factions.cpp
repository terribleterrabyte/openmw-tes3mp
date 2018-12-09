#include "Factions.hpp"

#include <components/misc/stringops.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

using namespace mwmp;

Faction tempFaction;
const Faction emptyFaction = {};

extern "C" void FactionFunctions::ClearFactionChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->factionChanges.factions.clear();
}

extern "C" unsigned int FactionFunctions::GetFactionChangesSize(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->factionChanges.count;
}

extern "C" unsigned char FactionFunctions::GetFactionChangesAction(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->factionChanges.action;
}

extern "C" const char *FactionFunctions::GetFactionId(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->factionChanges.count)
        return "invalid";

    return player->factionChanges.factions.at(index).factionId.c_str();
}

extern "C" int FactionFunctions::GetFactionRank(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->factionChanges.factions.at(index).rank;
}

extern "C" bool FactionFunctions::GetFactionExpulsionState(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, false);

    return player->factionChanges.factions.at(index).isExpelled;
}

extern "C" int FactionFunctions::GetFactionReputation(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->factionChanges.factions.at(index).reputation;
}

extern "C" void FactionFunctions::SetFactionChangesAction(unsigned short pid, unsigned char action) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->factionChanges.action = action;
}

extern "C" void FactionFunctions::SetFactionId(const char* factionId) noexcept
{
    tempFaction.factionId = factionId;
}

extern "C" void FactionFunctions::SetFactionRank(unsigned int rank) noexcept
{
    tempFaction.rank = rank;
}

extern "C" void FactionFunctions::SetFactionExpulsionState(bool expulsionState) noexcept
{
    tempFaction.isExpelled = expulsionState;
}

extern "C" void FactionFunctions::SetFactionReputation(int reputation) noexcept
{
    tempFaction.reputation = reputation;
}

extern "C" void FactionFunctions::AddFaction(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->factionChanges.factions.push_back(tempFaction);

    tempFaction = emptyFaction;
}

extern "C" void FactionFunctions::SendFactionChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_FACTION);
    packet->setPlayer(player);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" // All methods below are deprecated versions of methods from above

void FactionFunctions::InitializeFactionChanges(unsigned short pid) noexcept
{
    ClearFactionChanges(pid);
}
