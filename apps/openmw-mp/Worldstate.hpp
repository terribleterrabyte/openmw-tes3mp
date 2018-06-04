#pragma once

#include <RakNetTypes.h>

#include <components/openmw-mp/Log.hpp>
#include <components/openmw-mp/Base/BaseWorldstate.hpp>
#include <components/openmw-mp/Packets/Worldstate/WorldstatePacket.hpp>

class LuaState;


class Worldstate : public mwmp::BaseWorldstate
{
public:

    static void Init(LuaState &lua);

    void update();

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

};
