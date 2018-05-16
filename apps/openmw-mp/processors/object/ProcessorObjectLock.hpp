#ifndef OPENMW_PROCESSOROBJECTLOCK_HPP
#define OPENMW_PROCESSOROBJECTLOCK_HPP

#include "../ObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectLock final: public ObjectProcessor
    {
    public:
        ProcessorObjectLock()
        {
            BPP_INIT(ID_OBJECT_LOCK)
        }

        void Do(ObjectPacket &packet, const std::shared_ptr<Player> &player, BaseObjectList &objectList) override
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received %s from %s", strPacketID.c_str(), player->npc.mName.c_str());
            
            packet.Send(true);

            auto objCtrl = Networking::get().getState().getObjectCtrl();
            auto objects = objCtrl.copyObjects(objectList);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_OBJECT_LOCK>(player.get(), objects);

            objCtrl.sendObjects(player, objects, objectList.cell);
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTLOCK_HPP
