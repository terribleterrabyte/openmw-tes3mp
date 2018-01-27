//
// Created by koncord on 17.08.17.
//

#pragma once

#include <string>
#include <components/openmw-mp/Base/BasePlayer.hpp>
#include "BaseMgr.hpp"

class LuaState;
class Player;

class Faction
{
    friend class Factions;
public:
    static void Init(LuaState &lua);
public:
    explicit Faction(mwmp::Faction &faction);

    std::string getFactionId() const;
    void setFactionId(const std::string &factionId);

    int getFactionRank() const;
    void setFactionRank(unsigned int rank);

    bool getFactionExpulsionState() const;
    void setFactionExpulsionState(bool expulsionState);

    int getFactionReputation() const;
    void setFactionReputation(int reputation);

    mwmp::Faction faction;
};

class Factions final: public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:
    explicit Factions(Player *player);
    ~Factions();

    void addFaction(const Faction &faction);
    Faction getFaction(int id) const;
    void setFaction(int id, const Faction &faction);
    size_t size() const;
    void clear();

private:
    void processUpdate() final;
};
