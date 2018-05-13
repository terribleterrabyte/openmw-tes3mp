#ifndef OPENMW_PACKETOBJECTPLACE_HPP
#define OPENMW_PACKETOBJECTPLACE_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectPlace final: public ObjectPacket
    {
    public:
        explicit PacketObjectPlace(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTPLACE_HPP
