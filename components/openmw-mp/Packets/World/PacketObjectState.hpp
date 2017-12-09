#ifndef OPENMW_PACKETOBJECTSTATE_HPP
#define OPENMW_PACKETOBJECTSTATE_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketObjectState final: public WorldPacket
    {
    public:
        explicit PacketObjectState(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTSTATE_HPP
