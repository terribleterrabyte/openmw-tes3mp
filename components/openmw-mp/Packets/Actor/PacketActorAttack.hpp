#ifndef OPENMW_PACKETACTORATTACK_HPP
#define OPENMW_PACKETACTORATTACK_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorAttack final: public ActorPacket
    {
    public:
        explicit PacketActorAttack(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORATTACK_HPP
