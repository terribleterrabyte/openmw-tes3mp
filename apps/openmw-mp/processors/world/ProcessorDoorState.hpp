#ifndef OPENMW_PROCESSORDOORSTATE_HPP
#define OPENMW_PROCESSORDOORSTATE_HPP

#include "../WorldProcessor.hpp"

namespace mwmp
{
    class ProcessorDoorState final: public WorldProcessor
    {
    public:
        ProcessorDoorState()
        {
            BPP_INIT(ID_DOOR_STATE)
        }

        void Do(ObjectPacket &packet, const std::shared_ptr<Player> &player, BaseObjectList &objectList) override
        {
            packet.Send(true);

            auto objCtrl = Networking::get().getState().getObjectCtrl();
            auto objects = objCtrl.copyObjects(objectList);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_DOOR_STATE>(player, objects);

            objCtrl.sendObjects(player, objects, objectList.cell);
        }
    };
}

#endif //OPENMW_PROCESSORDOORSTATE_HPP
