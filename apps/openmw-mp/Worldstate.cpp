#include <components/openmw-mp/NetworkMessages.hpp>

#include "Worldstate.hpp"
#include "Networking.hpp"

using namespace std;

void Worldstate::Init(LuaState &lua)
{
    sol::table worldstateTable = lua.getState()->create_named_table("Worldstate");

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
