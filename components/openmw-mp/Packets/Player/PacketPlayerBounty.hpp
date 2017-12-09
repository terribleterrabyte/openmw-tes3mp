#ifndef OPENMW_PACKETPLAYERBOUNTY_HPP
#define OPENMW_PACKETPLAYERBOUNTY_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerBounty final: public PlayerPacket
    {
    public:
        PacketPlayerBounty(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERBOUNTY_HPP
