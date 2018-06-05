//
// Created by koncord on 12.08.17.
//

#include "Players.hpp"
#include "Networking.hpp"

using namespace std;

Players::Store Players::store;
std::queue<Player*> Players::updateQueue;

void Players::Init(LuaState &lua)
{
    sol::table playersTable = lua.getState()->create_named_table("Players");
    playersTable.set_function("getByPID", [](int pid) { return Players::getPlayerByPID(pid).get(); });
    playersTable.set_function("getByGUID", [](RakNet::RakNetGUID guid) { return Players::getPlayerByGUID(guid).get(); });
    playersTable.set_function("for_each", [](sol::function func)
    {
        for (shared_ptr<Player> player : store)
            func(player);
    });

    playersTable.set_function("size", &Players::size);
}


std::shared_ptr<Player> Players::getPlayerByPID(int pid)
{
    const auto &ls = store.get<ByID>();
    auto it = ls.find(pid);
    if (it != ls.end())
        return *it;

    return nullptr;
}

std::shared_ptr<Player> Players::getPlayerByGUID(RakNet::RakNetGUID guid)
{
    const auto &ls = store.get<ByGUID>();
    auto it = ls.find(guid.g);
    if (it != ls.end())
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_TRACE, "%d references: %d", guid.g, it->use_count());
        return *it;
    }

    return nullptr;
}

void deleter(Player *pl)
{
    LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Player %lu deleted", pl->guid.g);
    delete pl;
}

std::shared_ptr<Player> Players::addPlayer(RakNet::RakNetGUID guid)
{
    const int maxConnections = 65535;
    LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Creating new player with guid %lu", guid.g);

    auto player = shared_ptr<Player>(new Player(guid), deleter);

    unsigned short findPid = 0;
    const auto &ls = store.get<ByID>();
    for (; findPid < maxConnections; ++findPid) // find empty slot
    {
        auto it = ls.find(findPid);
        if (it == ls.end())
            break;
    }

    if (findPid >= maxConnections)
        return nullptr;

    LOG_APPEND(Log::LOG_INFO, "- Storing in slot %i", findPid);
    player->id = findPid;
    player->guid = guid;
    store.push_back(player);
    return player;
}

void Players::deletePlayerByPID(int pid)
{
    LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Marking player (pid %i) for deletion", pid);
    auto &ls = store.get<ByID>();
    auto it = ls.find(pid);
    if (it != ls.end())
    {
        (*it)->markedForDeletion = true;
        mwmp::Networking::get().getState().getState()->collect_garbage();
        size_t useCount = it->use_count();
        ls.erase(it);
        LOG_APPEND(Log::LOG_TRACE, "- references: %d", useCount - 1);
    }
}

void Players::deletePlayerByGUID(RakNet::RakNetGUID guid)
{
    LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Marking player (guid %lu) for deletion", guid.g);
    auto &ls = store.get<ByGUID>();
    auto it = ls.find(guid.g);
    if (it != ls.end())
    {
        (*it)->markedForDeletion = true;
        mwmp::Networking::get().getState().getState()->collect_garbage();
        size_t useCount = it->use_count();
        ls.erase(it);
        LOG_APPEND(Log::LOG_TRACE, "- references: %d", useCount - 1);
    }
}

void Players::for_each(std::function<void (Player *)> func)
{
    for (auto &player : store)
        func(player.get());
}

Players::Store::const_iterator Players::begin()
{
    return store.cbegin();
}

Players::Store::const_iterator Players::end()
{
    return store.cend();
}

size_t Players::size()
{
    return store.size();
}

void Players::processUpdated()
{
    while (!updateQueue.empty())
    {
        Player *player = updateQueue.front();
        updateQueue.pop();
        player->update();
    }
}


void Players::addToQueue(Player *player)
{
    updateQueue.push(player);
}
