#ifndef OPENMW_PACKETPLAYERSHAPESHIFT_HPP
#define OPENMW_PACKETPLAYERSHAPESHIFT_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerShapeshift final: public PlayerPacket
    {
    public:
        PacketPlayerShapeshift(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERSHAPESHIFT_HPP
