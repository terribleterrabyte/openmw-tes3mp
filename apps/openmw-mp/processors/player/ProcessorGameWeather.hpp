#ifndef OPENMW_PROCESSORGAMEWEATHER_HPP
#define OPENMW_PROCESSORGAMEWEATHER_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorGameWeather final: public PlayerProcessor
    {
    public:
        ProcessorGameWeather()
        {
            BPP_INIT(ID_GAME_WEATHER)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) final
        {
            DEBUG_PRINTF(strPacketID);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_WEATHER>(player);
        }
    };
}

#endif //OPENMW_PROCESSORGAMEWEATHER_HPP
