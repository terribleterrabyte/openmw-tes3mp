#ifndef OPENMW_PACKETOBJECTROTATE_HPP
#define OPENMW_PACKETOBJECTROTATE_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketObjectRotate final: public WorldPacket
    {
    public:
        explicit PacketObjectRotate(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTROTATE_HPP
