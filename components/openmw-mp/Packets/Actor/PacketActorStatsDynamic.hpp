#ifndef OPENMW_PACKETACTORSTATSDYNAMIC_HPP
#define OPENMW_PACKETACTORSTATSDYNAMIC_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorStatsDynamic final: public ActorPacket
    {
    public:
        explicit PacketActorStatsDynamic(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORSTATSDYNAMIC_HPP
