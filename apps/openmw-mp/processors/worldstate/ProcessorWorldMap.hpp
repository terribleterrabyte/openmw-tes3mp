#ifndef OPENMW_PROCESSORWORLDMAP_HPP
#define OPENMW_PROCESSORWORLDMAP_HPP

#include "../WorldstateProcessor.hpp"

namespace mwmp
{
    class ProcessorWorldMap : public WorldstateProcessor
    {
    public:
        ProcessorWorldMap()
        {
            BPP_INIT(ID_WORLD_MAP)
        }

        void Do(WorldstatePacket &packet, const std::shared_ptr<Player> &player, BaseWorldstate &worldstate) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_WORLD_MAP>(player.get());
        }
    };
}

#endif //OPENMW_PROCESSORWORLDMAP_HPP
