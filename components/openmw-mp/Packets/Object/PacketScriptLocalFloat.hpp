#ifndef OPENMW_PACKETSCRIPTLOCALFLOAT_HPP
#define OPENMW_PACKETSCRIPTLOCALFLOAT_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketScriptLocalFloat final: public ObjectPacket
    {
    public:
        explicit PacketScriptLocalFloat(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETSCRIPTLOCALFLOAT_HPP
