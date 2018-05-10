#ifndef OPENMW_PROCESSORPLAYERMAP_HPP
#define OPENMW_PROCESSORPLAYERMAP_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerMap final: public PlayerProcessor
    {
    public:
        ProcessorPlayerMap()
        {
            BPP_INIT(ID_PLAYER_MAP)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_MAP>(player.get());
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERMAP_HPP
