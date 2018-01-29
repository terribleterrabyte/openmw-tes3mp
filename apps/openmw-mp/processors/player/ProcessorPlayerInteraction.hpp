#ifndef OPENMW_PROCESSORPLAYERINTERACTION_HPP
#define OPENMW_PROCESSORPLAYERINTERACTION_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerInteraction final : public PlayerProcessor
    {
    public:
        ProcessorPlayerInteraction()
        {
            BPP_INIT(ID_PLAYER_INTERACTION)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_INTERACTION>(player);
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERINTERACTION_HPP
