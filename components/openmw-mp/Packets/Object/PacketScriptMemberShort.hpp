#ifndef OPENMW_PACKETSCRIPTMEMBERSHORT_HPP
#define OPENMW_PACKETSCRIPTMEMBERSHORT_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketScriptMemberShort final: public ObjectPacket
    {
    public:
        explicit PacketScriptMemberShort(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &obj, bool send) override;
    };
}

#endif //OPENMW_PACKETSCRIPTMEMBERSHORT_HPP
