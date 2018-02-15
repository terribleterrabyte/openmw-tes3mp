#ifndef OPENMW_PROCESSOROBJECTPLACE_HPP
#define OPENMW_PROCESSOROBJECTPLACE_HPP

#include "../WorldProcessor.hpp"
#include <apps/openmw-mp/Networking.hpp>

namespace mwmp
{
    class ProcessorObjectPlace final: public WorldProcessor
    {
    public:
        ProcessorObjectPlace()
        {
            BPP_INIT(ID_OBJECT_PLACE)
        }

        void Do(WorldPacket &packet, const std::shared_ptr<Player> &player, BaseEvent &event) override
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received %s from %s", strPacketID.c_str(), player->npc.mName.c_str());

            for (auto & object : event.worldObjects)
                object.mpNum = mwmp::Networking::getPtr()->incrementMpNum();

            // Send this packet back to the original sender with the mpNum generation from above,
            // then send it to the other players
            packet.Send(false);
            packet.Send(true);

            auto objCtrl = Networking::get().getState().getObjectCtrl();
            auto objects = objCtrl.copyObjects(event);

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_OBJECT_PLACE>(player.get(), objects);

            objCtrl.sendObjects(player, objects, event.cell);
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTPLACE_HPP
