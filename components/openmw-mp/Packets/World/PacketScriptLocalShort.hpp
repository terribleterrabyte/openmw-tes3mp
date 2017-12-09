#ifndef OPENMW_PACKETSCRIPTLOCALSHORT_HPP
#define OPENMW_PACKETSCRIPTLOCALSHORT_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketScriptLocalShort final: public WorldPacket
    {
    public:
        explicit PacketScriptLocalShort(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &obj, bool send) override;
    };
}

#endif //OPENMW_PACKETSCRIPTLOCALSHORT_HPP
