#ifndef OPENMW_PROCESSOROBJECTSTATE_HPP
#define OPENMW_PROCESSOROBJECTSTATE_HPP

#include "../WorldProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectState final: public WorldProcessor
    {
    public:
        ProcessorObjectState()
        {
            BPP_INIT(ID_OBJECT_STATE)
        }

        void Do(ObjectPacket &packet, const std::shared_ptr<Player> &player, BaseObjectList &objectList) override
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received %s from %s", strPacketID.c_str(), player->npc.mName.c_str());
            
            packet.Send(true);

            auto objCtrl = Networking::get().getState().getObjectCtrl();
            auto objects = objCtrl.copyObjects(objectList);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_OBJECT_STATE>(player.get(), objects);

            objCtrl.sendObjects(player, objects, objectList.cell);
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTSTATE_HPP
