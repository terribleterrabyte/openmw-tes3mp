#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <fstream>

#include "Worldstate.hpp"

using namespace std;
using namespace mwmp;

BaseWorldstate *WorldstateFunctions::readWorldstate;
BaseWorldstate WorldstateFunctions::writeWorldstate;

extern "C" void WorldstateFunctions::ReadReceivedWorldstate() noexcept
{
    readWorldstate = mwmp::Networking::getPtr()->getReceivedWorldstate();
}

extern "C" void WorldstateFunctions::CopyReceivedWorldstateToStore() noexcept
{
    writeWorldstate = *readWorldstate;
}

extern "C" void WorldstateFunctions::ClearMapChanges() noexcept
{
    writeWorldstate.mapTiles.clear();
}

extern "C" unsigned int WorldstateFunctions::GetMapChangesSize() noexcept
{
    return readWorldstate->mapTiles.size();
}

extern "C" const char *WorldstateFunctions::GetWeatherRegion() noexcept
{
    return readWorldstate->weather.region.c_str();
}

extern "C" int WorldstateFunctions::GetWeatherCurrent() noexcept
{
    return readWorldstate->weather.currentWeather;
}

extern "C" int WorldstateFunctions::GetWeatherNext() noexcept
{
    return readWorldstate->weather.nextWeather;
}

extern "C" int WorldstateFunctions::GetWeatherQueued() noexcept
{
    return readWorldstate->weather.queuedWeather;
}

extern "C" double WorldstateFunctions::GetWeatherTransitionFactor() noexcept
{
    return readWorldstate->weather.transitionFactor;
}

extern "C" int WorldstateFunctions::GetMapTileCellX(unsigned int index) noexcept
{
    return readWorldstate->mapTiles.at(index).x;
}

extern "C" int WorldstateFunctions::GetMapTileCellY(unsigned int index) noexcept
{
    return readWorldstate->mapTiles.at(index).y;
}

extern "C" void WorldstateFunctions::SetAuthorityRegion(const char* authorityRegion) noexcept
{
    writeWorldstate.authorityRegion = authorityRegion;
}

extern "C" void WorldstateFunctions::SetWeatherRegion(const char* region) noexcept
{
    writeWorldstate.weather.region = region;
}

extern "C" void WorldstateFunctions::SetWeatherForceState(bool forceState) noexcept
{
    writeWorldstate.forceWeather = forceState;
}

extern "C" void WorldstateFunctions::SetWeatherCurrent(int currentWeather) noexcept
{
    writeWorldstate.weather.currentWeather = currentWeather;
}

extern "C" void WorldstateFunctions::SetWeatherNext(int nextWeather) noexcept
{
    writeWorldstate.weather.nextWeather = nextWeather;
}

extern "C" void WorldstateFunctions::SetWeatherQueued(int queuedWeather) noexcept
{
    writeWorldstate.weather.queuedWeather = queuedWeather;
}

extern "C" void WorldstateFunctions::SetWeatherTransitionFactor(double transitionFactor) noexcept
{
    writeWorldstate.weather.transitionFactor = transitionFactor;
}

extern "C" void WorldstateFunctions::SetHour(double hour) noexcept
{
    writeWorldstate.time.hour = hour;
}

extern "C" void WorldstateFunctions::SetDay(int day) noexcept
{
    writeWorldstate.time.day = day;
}

extern "C" void WorldstateFunctions::SetMonth(int month) noexcept
{
    writeWorldstate.time.month = month;
}

extern "C" void WorldstateFunctions::SetYear(int year) noexcept
{
    writeWorldstate.time.year = year;
}

extern "C" void WorldstateFunctions::SetDaysPassed(int daysPassed) noexcept
{
    writeWorldstate.time.daysPassed = daysPassed;
}

extern "C" void WorldstateFunctions::SetTimeScale(double timeScale) noexcept
{
    writeWorldstate.time.timeScale = timeScale;
}

extern "C" void WorldstateFunctions::SetPlayerCollisionState(bool state) noexcept
{
    writeWorldstate.hasPlayerCollision = state;
}

extern "C" void WorldstateFunctions::SetActorCollisionState(bool state) noexcept
{
    writeWorldstate.hasActorCollision = state;
}

extern "C" void WorldstateFunctions::SetPlacedObjectCollisionState(bool state) noexcept
{
    writeWorldstate.hasPlacedObjectCollision = state;
}

extern "C" void WorldstateFunctions::UseActorCollisionForPlacedObjects(bool useActorCollision) noexcept
{
    writeWorldstate.useActorCollisionForPlacedObjects = useActorCollision;
}

extern "C" void WorldstateFunctions::AddEnforcedCollisionRefId(const char *refId) noexcept
{
    writeWorldstate.enforcedCollisionRefIds.push_back(refId);
}

extern "C" void WorldstateFunctions::ClearEnforcedCollisionRefIds() noexcept
{
    writeWorldstate.enforcedCollisionRefIds.clear();
}

extern "C" void WorldstateFunctions::SaveMapTileImageFile(unsigned int index, const char *filePath) noexcept
{
    if (index >= readWorldstate->mapTiles.size())
        return;

    const std::vector<char>& imageData = readWorldstate->mapTiles.at(index).imageData;

    std::ofstream outputFile(filePath, std::ios::binary);
    std::ostream_iterator<char> outputIterator(outputFile);
    std::copy(imageData.begin(), imageData.end(), outputIterator);
}

extern "C" void WorldstateFunctions::LoadMapTileImageFile(int cellX, int cellY, const char* filePath) noexcept
{
    mwmp::MapTile mapTile;
    mapTile.x = cellX;
    mapTile.y = cellY;

    std::ifstream inputFile(filePath, std::ios::binary);
    mapTile.imageData = std::vector<char>(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());

    if (mapTile.imageData.size() > mwmp::maxImageDataSize)
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Error loading image file for map tile: "
            "%s has a size of %i, which is over the maximum allowed of %i!",
            filePath, mapTile.imageData.size(), mwmp::maxImageDataSize);
    }
    else
    {
        writeWorldstate.mapTiles.push_back(mapTile);
    }
}

extern "C" void WorldstateFunctions::SendWorldMap(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_MAP);
    packet->setWorldstate(&writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void WorldstateFunctions::SendWorldTime(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_TIME);
    packet->setWorldstate(&writeWorldstate);
    
    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void WorldstateFunctions::SendWorldWeather(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_WEATHER);
    packet->setWorldstate(&writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void WorldstateFunctions::SendWorldCollisionOverride(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_COLLISION_OVERRIDE);
    packet->setWorldstate(&writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void WorldstateFunctions::SendWorldRegionAuthority(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_REGION_AUTHORITY);
    packet->setWorldstate(&writeWorldstate);

    packet->Send(false);

    // This packet should always be sent to all other players
    packet->Send(true);
}

extern "C" 
// All methods below are deprecated versions of methods from above

void WorldstateFunctions::ReadLastWorldstate() noexcept
{
    ReadReceivedWorldstate();
}

extern "C" void WorldstateFunctions::CopyLastWorldstateToStore() noexcept
{
    CopyReceivedWorldstateToStore();
}
