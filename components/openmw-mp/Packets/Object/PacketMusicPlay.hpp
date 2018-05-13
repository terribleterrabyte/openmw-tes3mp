#ifndef OPENMW_PACKETMUSICPLAY_HPP
#define OPENMW_PACKETMUSICPLAY_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketMusicPlay final: public ObjectPacket
    {
    public:
        explicit PacketMusicPlay(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETMUSICPLAY_HPP
