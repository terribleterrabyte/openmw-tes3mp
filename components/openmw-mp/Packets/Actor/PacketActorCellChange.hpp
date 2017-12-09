#ifndef OPENMW_PACKETACTORCELLCHANGE_HPP
#define OPENMW_PACKETACTORCELLCHANGE_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorCellChange final: public ActorPacket
    {
    public:
        explicit PacketActorCellChange(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORCELLCHANGE_HPP
