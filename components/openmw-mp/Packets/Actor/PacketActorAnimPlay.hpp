#ifndef OPENMW_PACKETACTORANIMPLAY_HPP
#define OPENMW_PACKETACTORANIMPLAY_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorAnimPlay final: public ActorPacket
    {
    public:
        explicit PacketActorAnimPlay(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORANIMPLAY_HPP
