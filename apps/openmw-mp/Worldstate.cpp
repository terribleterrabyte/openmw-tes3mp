#include <components/openmw-mp/NetworkMessages.hpp>

#include "Worldstate.hpp"
#include "Networking.hpp"

using namespace std;

Worldstate::Worldstate() : mapTiles(this)
{

}

void Worldstate::Init(LuaState &lua)
{
    sol::table worldstateTable = lua.getState()->create_named_table("Worldstate");

    //worldstateTable.set_function("getMapTiles", []() {
    //    mwmp::Networking::get().get().getServerWorldstate()->getMapTiles();
    //});

    worldstateTable.set_function("setHour", [](double hour) {
        mwmp::Networking::get().get().getServerWorldstate()->setHour(hour);
    });

    worldstateTable.set_function("setDay", [](int day) {
        mwmp::Networking::get().get().getServerWorldstate()->setDay(day);
    });

    worldstateTable.set_function("setMonth", [](int month) {
        mwmp::Networking::get().get().getServerWorldstate()->setMonth(month);
    });

    worldstateTable.set_function("setYear", [](int year) {
        mwmp::Networking::get().get().getServerWorldstate()->setYear(year);
    });

    worldstateTable.set_function("setDaysPassed", [](int daysPassed) {
        mwmp::Networking::get().get().getServerWorldstate()->setDaysPassed(daysPassed);
    });

    worldstateTable.set_function("setTimeScale", [](float timeScale) {
        mwmp::Networking::get().get().getServerWorldstate()->setTimeScale(timeScale);
    });

    worldstateTable.set_function("setPlayerCollisionState", [](bool state) {
        mwmp::Networking::get().get().getServerWorldstate()->setPlayerCollisionState(state);
    });

    worldstateTable.set_function("setActorCollisionState", [](bool state) {
        mwmp::Networking::get().get().getServerWorldstate()->setActorCollisionState(state);
    });

    worldstateTable.set_function("setPlacedObjectCollisionState", [](bool state) {
        mwmp::Networking::get().get().getServerWorldstate()->setPlacedObjectCollisionState(state);
    });

    worldstateTable.set_function("setActorCollisionForPlacedObjects", [](bool state) {
        mwmp::Networking::get().get().getServerWorldstate()->setActorCollisionForPlacedObjects(state);
    });
}

void Worldstate::update()
{
    auto worldstateController = mwmp::Networking::get().getWorldstatePacketController();

    if (shouldUpdateTime)
    {
        auto packet = worldstateController->GetPacket(ID_WORLD_TIME);
        packet->setWorldstate(this);
        packet->Send(true);

        shouldUpdateTime = false;
    }

    if (shouldUpdateCollisionOverrides)
    {
        auto packet = worldstateController->GetPacket(ID_WORLD_COLLISION_OVERRIDE);
        packet->setWorldstate(this);
        packet->Send(true);

        shouldUpdateCollisionOverrides = false;
    }

    //mapTiles.update();
}

MapTiles &Worldstate::getMapTiles()
{
    return mapTiles;
}

void Worldstate::setHour(double inputHour)
{
    hour = inputHour;
    shouldUpdateTime = true;
}

void Worldstate::setDay(int inputDay)
{
    day = inputDay;
    shouldUpdateTime = true;
}

void Worldstate::setMonth(int inputMonth)
{
    month = inputMonth;
    shouldUpdateTime = true;
}

void Worldstate::setYear(int inputYear)
{
    year = inputYear;
    shouldUpdateTime = true;
}

void Worldstate::setDaysPassed(int inputDaysPassed)
{
    daysPassed = inputDaysPassed;
    shouldUpdateTime = true;
}

void Worldstate::setTimeScale(float inputTimeScale)
{
    timeScale = inputTimeScale;
    shouldUpdateTime = true;
}

void Worldstate::setPlayerCollisionState(bool state)
{
    hasPlayerCollision = state;
    shouldUpdateCollisionOverrides = true;
}

void Worldstate::setActorCollisionState(bool state)
{
    hasActorCollision = state;
    shouldUpdateCollisionOverrides = true;
}
void Worldstate::setPlacedObjectCollisionState(bool state)
{
    hasPlacedObjectCollision = state;
    shouldUpdateCollisionOverrides = true;
}

void Worldstate::setActorCollisionForPlacedObjects(bool state)
{
    useActorCollisionForPlacedObjects = state;
    shouldUpdateCollisionOverrides = true;
}

void MapTiles::Init(LuaState &lua)
{
    lua.getState()->new_usertype<MapTiles>("MapTiles",
        "addMapTile", &MapTiles::addMapTile,
        "getMapTile", &MapTiles::getMapTile,
        "setMapTile", &MapTiles::setMapTile,
        "clear", &MapTiles::clear,
        "size", &MapTiles::size
        );
}

MapTiles::MapTiles(Worldstate *worldstate) : BaseMgr(worldstate)
{

}

void MapTiles::processUpdate()
{
    auto packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_WORLD_MAP);
    packet->Send(false);
    clear();
}

void MapTiles::addMapTile(const MapTile &mapTile)
{
    mwmp::Networking::get().get().getServerWorldstate()->mapChanges.mapTiles.push_back(mapTile.mapTile);
    setChanged();
}

MapTile MapTiles::getMapTile(int id) const
{
    return MapTile(mwmp::Networking::get().get().getServerWorldstate()->mapChanges.mapTiles.at(id));
}

void MapTiles::setMapTile(int id, const MapTile &mapTile)
{
    mwmp::Networking::get().get().getServerWorldstate()->mapChanges.mapTiles.at(id) = mapTile.mapTile;
    setChanged();
}

void MapTiles::clear()
{
    mwmp::Networking::get().get().getServerWorldstate()->mapChanges.mapTiles.clear();
    setChanged();
}

size_t MapTiles::size() const
{
    return mwmp::Networking::get().get().getServerWorldstate()->mapChanges.mapTiles.size();
}

void MapTile::Init(LuaState &lua)
{
    lua.getState()->new_usertype<MapTile>("MapTile",
        "cellX", sol::property(&MapTile::getCellX, &MapTile::setCellX),
        "cellY", sol::property(&MapTile::getCellY, &MapTile::setCellY),
        "loadImageFile", &MapTile::loadImageFile,
        "saveImageFile", &MapTile::saveImageFile
        );
}

MapTile::MapTile(mwmp::BaseMapTile &mapTile) : mapTile(mapTile)
{

}

int MapTile::getCellX() const
{
    return mapTile.x;
}

void MapTile::setCellX(int cellX)
{
    mapTile.x = cellX;
}

int MapTile::getCellY() const
{
    return mapTile.y;
}

void MapTile::setCellY(int cellY)
{
    mapTile.y = cellY;
}

void MapTile::loadImageFile(const char* filePath)
{
    std::ifstream inputFile(filePath, std::ios::binary);
    mapTile.imageData = std::vector<char>(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
}

void MapTile::saveImageFile(const char* filePath)
{
    std::ofstream outputFile(filePath, std::ios::binary);
    std::ostream_iterator<char> outputIterator(outputFile);
    std::copy(mapTile.imageData.begin(), mapTile.imageData.end(), outputIterator);
}

