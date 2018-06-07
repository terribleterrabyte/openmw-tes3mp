#pragma once

#include <RakNetTypes.h>

#include <components/openmw-mp/Log.hpp>
#include <components/openmw-mp/Base/BaseWorldstate.hpp>
#include <components/openmw-mp/Packets/Worldstate/WorldstatePacket.hpp>

#include "BaseMgr.hpp"

class LuaState;


class MapTile
{
    friend class MapTiles;
public:
    static void Init(LuaState &lua);
public:
    explicit MapTile(mwmp::BaseMapTile &mapTile);

    int getCellX() const;
    void setCellX(int cellX);

    int getCellY() const;
    void setCellY(int cellY);

    void loadImageFile(const char* filePath);
    void saveImageFile(const char *filePath);

    mwmp::BaseMapTile mapTile;
};

class MapTiles final : public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:
    explicit MapTiles(Worldstate *worldstate);

    void addMapTile(const MapTile &mapTile);
    MapTile getMapTile(int id) const;
    void setMapTile(int id, const MapTile &mapTile);
    size_t size() const;
    void clear();

private:
    void processUpdate() final;
};

class Worldstate : public mwmp::BaseWorldstate
{
public:

    explicit Worldstate();

    static void Init(LuaState &lua);

    void update();

    MapTiles &getMapTiles();

    void setHour(double hour);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    void setDaysPassed(int daysPassed);
    void setTimeScale(float timeScale);

    void setPlayerCollisionState(bool state);
    void setActorCollisionState(bool state);
    void setPlacedObjectCollisionState(bool state);
    void setActorCollisionForPlacedObjects(bool state);

private:

    bool shouldUpdateTime, shouldUpdateCollisionOverrides;

    MapTiles mapTiles;

};

