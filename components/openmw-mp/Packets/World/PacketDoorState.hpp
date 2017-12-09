#ifndef OPENMW_PACKETDOORSTATE_HPP
#define OPENMW_PACKETDOORSTATE_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketDoorState final: public WorldPacket
    {
    public:
        explicit PacketDoorState(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETDOORSTATE_HPP
