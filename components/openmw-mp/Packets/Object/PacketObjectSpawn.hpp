#ifndef OPENMW_PACKETOBJECTSPAWN_HPP
#define OPENMW_PACKETOBJECTSPAWN_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectSpawn final: public ObjectPacket
    {
    public:
        explicit PacketObjectSpawn(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTSPAWN_HPP
