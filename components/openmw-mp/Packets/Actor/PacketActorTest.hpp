#ifndef OPENMW_PACKETACTORTEST_HPP
#define OPENMW_PACKETACTORTEST_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorTest final: public ActorPacket
    {
    public:
        explicit PacketActorTest(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORTEST_HPP
