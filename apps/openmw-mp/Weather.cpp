//
// Created by koncord on 30.11.17.
//

#include "Weather.hpp"
#include "Script/LuaState.hpp"
#include "Networking.hpp"
#include <Player.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Base/BasePlayer.hpp>

using namespace std;
using namespace mwmp;

void WeatherMgr::Init(LuaState &lua)
{
    lua.getState()->new_usertype<WeatherMgr>("WeatherMgr",
                                             "current", sol::property(&WeatherMgr::getCurrent, &WeatherMgr::setCurrent),
                                             "next", sol::property(&WeatherMgr::getNext, &WeatherMgr::setNext),
                                             "transitionFactor", sol::property(&WeatherMgr::getTransition, &WeatherMgr::setTransition),
                                             "updateTime", sol::property(&WeatherMgr::getUpdate, &WeatherMgr::setUpdate),
                                             "copy", &WeatherMgr::copy,
                                             "setWeather", &WeatherMgr::setWeather,
                                             "request", &WeatherMgr::requestWeather
    );
}

WeatherMgr::WeatherMgr(Player *player) : BaseMgr(player)
{

}

void WeatherMgr::setWeather(int weather)
{
    setChanged();

    player->weather.nextWeather = weather;
    player->weather.transitionFactor = 0.0f;
    player->weather.updateTime = 0.0f;
}

void WeatherMgr::processUpdate()
{

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_WEATHER);

    packet->setPlayer(player);

    packet->Send(/*toOthers*/ false);
}

void WeatherMgr::setCurrent(int weather)
{
    player->weather.currentWeather = weather;
    setChanged();
}

int WeatherMgr::getCurrent() const
{
    return player->weather.currentWeather;
}

void WeatherMgr::setNext(int weather)
{
    player->weather.nextWeather = weather;
    setChanged();
}

int WeatherMgr::getNext() const
{
    return player->weather.nextWeather;
}

void WeatherMgr::setTransition(float time)
{
    player->weather.transitionFactor = time;
    setChanged();
}

float WeatherMgr::getTransition() const
{
    return player->weather.transitionFactor;
}

void WeatherMgr::setUpdate(float time)
{
    player->weather.updateTime = time;
    setChanged();
}

float WeatherMgr::getUpdate() const
{
    return player->weather.updateTime;
}

void WeatherMgr::requestWeather()
{
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_WEATHER);
    packet->RequestData(player->guid);
}

void WeatherMgr::copy(const WeatherMgr &other)
{
    if (other.player == player)
        return;
    player->weather = other.player->weather;
    setChanged();
}
