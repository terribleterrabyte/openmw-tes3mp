#ifndef OPENMW_PACKETOBJECTANIMPLAY_HPP
#define OPENMW_PACKETOBJECTANIMPLAY_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectAnimPlay final: public ObjectPacket
    {
    public:
        explicit PacketObjectAnimPlay(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTANIMPLAY_HPP
