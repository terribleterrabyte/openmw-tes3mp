#ifndef OPENMW_PACKETOBJECTSCALE_HPP
#define OPENMW_PACKETOBJECTSCALE_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketObjectScale final: public ObjectPacket
    {
    public:
        explicit PacketObjectScale(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETOBJECTSCALE_HPP
