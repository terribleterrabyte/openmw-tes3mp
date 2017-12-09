#ifndef OPENMW_PACKETPLAYERMAP_HPP
#define OPENMW_PACKETPLAYERMAP_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerMap final: public PlayerPacket
    {
    public:
        PacketPlayerMap(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERMAP_HPP
