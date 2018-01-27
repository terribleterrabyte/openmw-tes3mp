//
// Created by koncord on 17.08.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>

#include "Script/LuaState.hpp"
#include "Networking.hpp"

#include "Factions.hpp"
#include "Player.hpp"

void Factions::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Factions>("Factions",
                                           "addFaction", &Factions::addFaction,
                                           "getFaction", &Factions::getFaction,
                                           "setFaction", &Factions::setFaction,
                                           "clear", &Factions::clear,
                                           "size", &Factions::size
    );
}

Factions::Factions(Player *player): BaseMgr(player)
{

}

Factions::~Factions()
{

}

void Factions::processUpdate()
{
    auto packet =mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_FACTION);
    packet->setPlayer(player);
    packet->Send(/*toOthers*/ false);
    clear();
}

void Factions::addFaction(const Faction &faction)
{
    player->factionChanges.factions.emplace_back(faction.faction);
    setChanged();
}


Faction Factions::getFaction(int id) const
{
    return Faction(player->factionChanges.factions.at(id));
}

void Factions::setFaction(int id, const Faction &faction)
{
    player->factionChanges.factions.at(id) = faction.faction;
    setChanged();
}

void Factions::clear()
{
    player->factionChanges.factions.clear();
    setChanged();
}

size_t Factions::size() const
{
    return player->factionChanges.factions.size();
}

void Faction::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Faction>("Faction",
                                          "factionId", sol::property(&Faction::getFactionId, &Faction::setFactionId),
                                          "rank", sol::property(&Faction::getFactionRank, &Faction::setFactionRank),
                                          "isExpelled", sol::property(&Faction::getFactionExpulsionState, &Faction::setFactionExpulsionState),
                                          "reputation", sol::property(&Faction::getFactionReputation, &Faction::setFactionReputation)
    );
}

Faction::Faction(mwmp::Faction &faction): faction(faction)
{

}

std::string Faction::getFactionId() const
{
    return faction.factionId;
}

void Faction::setFactionId(const std::string &factionId)
{
    faction.factionId = factionId;
}

int Faction::getFactionRank() const
{
    return faction.rank;
}

void Faction::setFactionRank(unsigned int rank)
{
    faction.rankChanged();
    faction.rank = rank;
}

bool Faction::getFactionExpulsionState() const
{
    return faction.isExpelled;
}

void Faction::setFactionExpulsionState(bool expulsionState)
{
    faction.expulsionChanged();
    faction.isExpelled = expulsionState;
}

int Faction::getFactionReputation() const
{
    return faction.reputation;
}

void Faction::setFactionReputation(int reputation)
{
    faction.reputationChanged();
    faction.reputation = reputation;
}
