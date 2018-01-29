#ifndef OPENMW_PROCESSORPLAYERREPUTATION_HPP
#define OPENMW_PROCESSORPLAYERREPUTATION_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerReputation final : public PlayerProcessor
    {
    public:
        ProcessorPlayerReputation()
        {
            BPP_INIT(ID_PLAYER_REPUTATION)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_REPUTATION>(player);
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERREPUTATION_HPP
