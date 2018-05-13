#ifndef OPENMW_PACKETOBJECTROTATE_HPP
#define OPENMW_PACKETOBJECTROTATE_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectRotate final: public ObjectPacket
    {
    public:
        explicit PacketObjectRotate(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTROTATE_HPP
