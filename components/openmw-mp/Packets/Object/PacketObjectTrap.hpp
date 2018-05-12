#ifndef OPENMW_PACKETOBJECTTRAP_HPP
#define OPENMW_PACKETOBJECTTRAP_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectTrap final: public ObjectPacket
    {
    public:
        explicit PacketObjectTrap(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTTRAP_HPP
