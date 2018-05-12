#ifndef OPENMW_PACKETSCRIPTGLOBALSHORT_HPP
#define OPENMW_PACKETSCRIPTGLOBALSHORT_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketScriptGlobalShort final: public ObjectPacket
    {
    public:
        explicit PacketScriptGlobalShort(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &worldObject, bool send) override;
    };
}

#endif //OPENMW_PACKETSCRIPTGLOBALSHORT_HPP
