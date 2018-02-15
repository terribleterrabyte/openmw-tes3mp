#ifndef OPENMW_PROCESSORPLAYERFACTION_HPP
#define OPENMW_PROCESSORPLAYERFACTION_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerFaction final: public PlayerProcessor
    {
    public:
        ProcessorPlayerFaction()
        {
            BPP_INIT(ID_PLAYER_FACTION)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_FACTION>(player.get());
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERFACTION_HPP
