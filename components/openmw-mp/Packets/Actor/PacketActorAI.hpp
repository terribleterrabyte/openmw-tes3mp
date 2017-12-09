#ifndef OPENMW_PACKETACTORAI_HPP
#define OPENMW_PACKETACTORAI_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorAI final: public ActorPacket
    {
    public:
        explicit PacketActorAI(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORAI_HPP
