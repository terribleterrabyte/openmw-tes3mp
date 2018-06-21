#ifndef OPENMW_PROCESSOROBJECTDELETE_HPP
#define OPENMW_PROCESSOROBJECTDELETE_HPP

#include "../ObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectDelete final: public ObjectProcessor
    {
    public:
        ProcessorObjectDelete()
        {
            BPP_INIT(ID_OBJECT_DELETE)
        }

        void Do(ObjectPacket &packet, const std::shared_ptr<Player> &player, BaseObjectList &objectList) override
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received %s from %s", strPacketID.c_str(), player->npc.mName.c_str());

            auto objCtrl = Networking::get().getState().getObjectCtrl();
            auto objects = objCtrl.copyObjects(objectList);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_OBJECT_DELETE>(player.get(), objects);
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTDELETE_HPP
