#ifndef OPENMW_PACKETPLAYERREGIONAUTHORITY_HPP
#define OPENMW_PACKETPLAYERREGIONAUTHORITY_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerRegionAuthority final: public PlayerPacket
    {
    public:
        PacketPlayerRegionAuthority(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERREGIONAUTHORITY_HPP
