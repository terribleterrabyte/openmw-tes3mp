#ifndef OPENMW_PACKETOBJECTLOCK_HPP
#define OPENMW_PACKETOBJECTLOCK_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectLock final: public ObjectPacket
    {
    public:
        explicit PacketObjectLock(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTLOCK_HPP
