#ifndef OPENMW_PACKETOBJECTLOCK_HPP
#define OPENMW_PACKETOBJECTLOCK_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketObjectLock final: public WorldPacket
    {
    public:
        explicit PacketObjectLock(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTLOCK_HPP
