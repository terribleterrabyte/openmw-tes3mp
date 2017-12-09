#ifndef OPENMW_PACKETACTORDEATH_HPP
#define OPENMW_PACKETACTORDEATH_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorDeath final: public ActorPacket
    {
    public:
        explicit PacketActorDeath(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORDEATH_HPP
