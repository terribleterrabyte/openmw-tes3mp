#ifndef OPENMW_PacketObjectMove_HPP
#define OPENMW_PacketObjectMove_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectMove final: public ObjectPacket
    {
    public:
        explicit PacketObjectMove(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PacketObjectMove_HPP
