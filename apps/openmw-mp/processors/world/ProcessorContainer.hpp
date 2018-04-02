#ifndef OPENMW_PROCESSORCONTAINER_HPP
#define OPENMW_PROCESSORCONTAINER_HPP

#include <apps/openmw-mp/Object.hpp>
#include "../WorldProcessor.hpp"


namespace mwmp
{
    class ProcessorContainer final: public WorldProcessor
    {
    public:
        ProcessorContainer()
        {
            BPP_INIT(ID_CONTAINER)
        }

        void Do(WorldPacket &packet, const std::shared_ptr<Player> &player, BaseEvent &event) override
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received %s from %s", strPacketID.c_str(), player->npc.mName.c_str());
            LOG_APPEND(Log::LOG_INFO, "- action: %i", (int) event.action);

            // Don't have any hardcoded sync, and instead expect Lua scripts to forward
            // container packets to ensure their integrity based on what exists in the
            // server data

            auto objCtrl = Networking::get().getState().getObjectCtrl();
            auto containers = objCtrl.copyContainers(event);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_CONTAINER>(player, containers);

            LOG_APPEND(Log::LOG_INFO, "- Finished processing ID_CONTAINER");
        }
    };
}

#endif //OPENMW_PROCESSORCONTAINER_HPP
