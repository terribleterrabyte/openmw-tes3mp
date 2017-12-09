#ifndef OPENMW_PACKETACTORSPEECH_HPP
#define OPENMW_PACKETACTORSPEECH_HPP

#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>

namespace mwmp
{
    class PacketActorSpeech final: public ActorPacket
    {
    public:
        explicit PacketActorSpeech(RakNet::RakPeerInterface *peer);

        void Actor(BaseActor &actor, bool send) override;
    };
}

#endif //OPENMW_PACKETACTORSPEECH_HPP
