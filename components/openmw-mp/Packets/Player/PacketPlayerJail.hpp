#ifndef OPENMW_PACKETPLAYERJAIL_HPP
#define OPENMW_PACKETPLAYERJAIL_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerJail final: public PlayerPacket
    {
    public:
        PacketPlayerJail(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERJAIL_HPP
