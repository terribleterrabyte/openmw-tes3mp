#ifndef OPENMW_PACKETDOORSTATE_HPP
#define OPENMW_PACKETDOORSTATE_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketDoorState final: public ObjectPacket
    {
    public:
        explicit PacketDoorState(RakNet::RakPeerInterface *peer);

        void Object(BaseObject &baseObject, bool send) override;
    };
}

#endif //OPENMW_PACKETDOORSTATE_HPP
