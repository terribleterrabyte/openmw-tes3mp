#ifndef OPENMW_PACKETACTORPOSITION_HPP
#define OPENMW_PACKETACTORPOSITION_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorPosition final: public ActorPacket
    {
    public:
        explicit PacketActorPosition(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORPOSITION_HPP
