#ifndef OPENMW_PROCESSORPLAYERMISCELLANEOUS_HPP
#define OPENMW_PROCESSORPLAYERMISCELLANEOUS_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerMiscellaneous final : public PlayerProcessor
    {
    public:
        ProcessorPlayerMiscellaneous()
        {
            BPP_INIT(ID_PLAYER_MISCELLANEOUS)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_MISCELLANEOUS>(player);
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERMISCELLANEOUS_HPP
