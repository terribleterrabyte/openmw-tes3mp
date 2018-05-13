//
// Created by koncord on 18.02.17.
//

#include <iostream>
#include <components/openmw-mp/NetworkMessages.hpp>

#include "Script/EventController.hpp"
#include "Networking.hpp"

#include "Cell.hpp"
#include "Player.hpp"

using namespace std;

Cell::Cell(const ESM::Cell &cell) : cell(cell)
{

}

Cell::Iterator Cell::begin() const
{
    return players.begin();
}

Cell::Iterator Cell::end() const
{
    return players.end();
}

void Cell::addPlayer(Player *player)
{
    // Ensure the player hasn't already been added
    auto it = find(begin(), end(), player);

    if (it != end())
    {
        LOG_APPEND(Log::LOG_INFO, "- Attempt to add %s to Cell %s again was ignored", player->npc.mName.c_str(), getDescription().c_str());
        return;
    }

    auto it2 = find(player->cells.begin(), player->cells.end(), this);
    if (it2 == player->cells.end())
    {
        LOG_APPEND(Log::LOG_INFO, "- Adding %s to Player %s", getDescription().c_str(), player->npc.mName.c_str());

        player->cells.push_back(this);
    }

    LOG_APPEND(Log::LOG_INFO, "- Adding %s to Cell %s", player->npc.mName.c_str(), getDescription().c_str());


    mwmp::Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_CELL_LOAD>(player, getDescription());

    players.push_back(player);
}

void Cell::removePlayer(Player *player)
{
    for (auto it = begin(); it != end(); it++)
    {
        if (*it == player)
        {
            auto it2 = find(player->cells.begin(), player->cells.end(), this);
            if (it2 != player->cells.end())
            {
                LOG_APPEND(Log::LOG_INFO, "- Removing %s from Player %s", getDescription().c_str(), player->npc.mName.c_str());

                player->cells.erase(it2);
            }

            LOG_APPEND(Log::LOG_INFO, "- Removing %s from Cell %s", player->npc.mName.c_str(), getDescription().c_str());


            mwmp::Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_CELL_UNLOAD>(player, getDescription());

            players.erase(it);
            return;
        }
    }
}

void Cell::readActorList(unsigned char packetID, const mwmp::BaseActorList *newActorList)
{
    for (auto &newActor : newActorList->baseActors)
    {

        if (containsActor(newActor->refNumIndex, newActor->mpNum))
        {
            mwmp::BaseActor *cellActor = getActor(newActor->refNumIndex, newActor->mpNum);

            switch (packetID)
            {
            case ID_ACTOR_POSITION:

                cellActor->hasPositionData = true;
                cellActor->position = newActor->position;
                break;

            case ID_ACTOR_STATS_DYNAMIC:

                cellActor->hasStatsDynamicData = true;
                cellActor->creatureStats.mDynamic[0] = newActor->creatureStats.mDynamic[0];
                cellActor->creatureStats.mDynamic[1] = newActor->creatureStats.mDynamic[1];
                cellActor->creatureStats.mDynamic[2] = newActor->creatureStats.mDynamic[2];
                break;
            }
        }
        else
            cellActorList.baseActors.push_back(newActor);
    }
}

bool Cell::containsActor(unsigned refNumIndex, unsigned mpNum)
{
    for (const auto &actor : cellActorList.baseActors)
    {
        if (actor->refNumIndex == refNumIndex && actor->mpNum == mpNum)
            return true;
    }
    return false;
}

mwmp::BaseActor *Cell::getActor(unsigned refNumIndex, unsigned mpNum)
{
    for (const auto &actor : cellActorList.baseActors)
    {
        if (actor->refNumIndex == refNumIndex && actor->mpNum == mpNum)
            return actor.get();
    }
    return nullptr;
}

void Cell::removeActors(const mwmp::BaseActorList &newActorList)
{
    for (auto it = cellActorList.baseActors.begin(); it != cellActorList.baseActors.end();)
    {
        unsigned refNumIndex = (*it)->refNumIndex;
        unsigned mpNum = (*it)->mpNum;

        bool foundActor = false;

        for (const auto &newActor : newActorList.baseActors)
        {
            if (newActor->refNumIndex == refNumIndex && newActor->mpNum == mpNum)
            {
                it = cellActorList.baseActors.erase(it);
                foundActor = true;
                break;
            }
        }

        if (!foundActor)
            it++;
    }
}

RakNet::RakNetGUID *Cell::getAuthority()
{
    return &authorityGuid;
}

void Cell::setAuthority(const RakNet::RakNetGUID& guid)
{
    authorityGuid = guid;
}

mwmp::BaseActorList *Cell::getActorList()
{
    return &cellActorList;
}

Cell::TPlayers Cell::getPlayers() const
{
    return players;
}

void Cell::sendToLoaded(mwmp::ActorPacket *actorPacket, mwmp::BaseActorList *baseActorList) const
{
    if (players.empty())
        return;

    std::list <Player*> plList;

    for (auto &pl : players)
    {
        if (pl != nullptr && !pl->npc.mName.empty())
            plList.push_back(pl);
    }

    plList.sort();
    plList.unique();

    for (auto &pl : plList)
    {
        if (pl->guid == baseActorList->guid) continue;

        actorPacket->setActorList(baseActorList);

        // Send the packet to this eligible guid
        actorPacket->Send(pl->guid);
    }
}

void Cell::sendToLoaded(mwmp::ObjectPacket *objectPacket, mwmp::BaseObjectList *baseObjectList) const
{
    if (players.empty())
        return;

    std::list <Player*> plList;

    for (auto &pl : players)
    {
        if (pl != nullptr && !pl->npc.mName.empty())
            plList.push_back(pl);
    }

    plList.sort();
    plList.unique();

    for (auto &pl : plList)
    {
        if (pl->guid == baseObjectList->guid) continue;

        objectPacket->setObjectList(baseObjectList);

        // Send the packet to this eligible guid
        objectPacket->Send(pl->guid);
    }
}

std::string Cell::getDescription() const
{
    return cell.getDescription();
}
