#ifndef OPENMW_PACKETSCRIPTLOCALFLOAT_HPP
#define OPENMW_PACKETSCRIPTLOCALFLOAT_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketScriptLocalFloat final: public WorldPacket
    {
    public:
        explicit PacketScriptLocalFloat(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETSCRIPTLOCALFLOAT_HPP
