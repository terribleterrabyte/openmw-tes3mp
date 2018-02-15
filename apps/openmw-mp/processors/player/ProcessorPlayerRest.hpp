#ifndef OPENMW_PROCESSORPLAYERREST_HPP
#define OPENMW_PROCESSORPLAYERREST_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerRest final: public PlayerProcessor
    {
    public:
        ProcessorPlayerRest()
        {
            BPP_INIT(ID_PLAYER_REST)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_REST>(player.get());
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERREST_HPP
