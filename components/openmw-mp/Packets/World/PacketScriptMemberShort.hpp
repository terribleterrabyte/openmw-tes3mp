#ifndef OPENMW_PACKETSCRIPTMEMBERSHORT_HPP
#define OPENMW_PACKETSCRIPTMEMBERSHORT_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketScriptMemberShort final: public WorldPacket
    {
    public:
        explicit PacketScriptMemberShort(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &obj, bool send) override;
    };
}

#endif //OPENMW_PACKETSCRIPTMEMBERSHORT_HPP
