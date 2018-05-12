#ifndef OPENMW_PACKETCONTAINER_HPP
#define OPENMW_PACKETCONTAINER_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketContainer final: public ObjectPacket
    {
    public:
        explicit PacketContainer(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETCONTAINER_HPP
