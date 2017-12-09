#ifndef OPENMW_PACKETACTOREQUIPMENT_HPP
#define OPENMW_PACKETACTOREQUIPMENT_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorEquipment final: public ActorPacket
    {
    public:
        explicit PacketActorEquipment(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTOREQUIPMENT_HPP
