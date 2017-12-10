#ifndef OPENMW_PROCESSORGAMEWEATHER_HPP
#define OPENMW_PROCESSORGAMEWEATHER_HPP

#include <apps/openmw/mwworld/worldimp.hpp>
#include <apps/openmw/mwworld/weather.hpp>
#include "../PlayerProcessor.hpp"
#include <apps/openmw/mwmp/Main.hpp>
#include <apps/openmw/mwmp/Networking.hpp>

namespace mwmp
{
    class ProcessorGameWeather final: public PlayerProcessor
    {
    public:
        ProcessorGameWeather()
        {
            BPP_INIT(ID_GAME_WEATHER)
        }

        void Do(PlayerPacket &packet, BasePlayer *player) final
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Received %s", strPacketID);
            MWWorld::WeatherManager *weatherManager = Main::get().getWeatherManager();
            auto &weather = player->weather;
            if(isRequest())
            {
                LOG_APPEND(Log::LOG_TRACE, "- requested data");
                weather.currentWeather = weatherManager->mCurrentWeather;
                weather.nextWeather = weatherManager->mNextWeather;
                weather.transitionFactor = weatherManager->mTransitionFactor;
                weather.updateTime = weatherManager->mWeatherUpdateTime;
                packet.setPlayer(player);
                packet.Send();
            }
            else
            {
                LOG_APPEND(Log::LOG_TRACE, "- received data");
                weatherManager->mCurrentWeather = weather.currentWeather;
                weatherManager->mNextWeather = weather.nextWeather;
                weatherManager->mTransitionFactor = weather.transitionFactor;
                weatherManager->mWeatherUpdateTime = weather.updateTime;
            }
        }
    };
}

#endif //OPENMW_PROCESSORGAMEWEATHER_HPP
