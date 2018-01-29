#ifndef OPENMW_PROCESSORPLAYERQUICKKEYS_HPP
#define OPENMW_PROCESSORPLAYERQUICKKEYS_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerQuickKeys final : public PlayerProcessor
    {
    public:
        ProcessorPlayerQuickKeys()
        {
            BPP_INIT(ID_PLAYER_QUICKKEYS)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_QUICKKEYS>(player);
        }
    };
}


#endif //OPENMW_PROCESSORPLAYERQUICKKEYS_HPP
