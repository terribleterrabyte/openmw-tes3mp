#ifndef OPENMW_PACKETPLAYERANIMFLAGS_HPP
#define OPENMW_PACKETPLAYERANIMFLAGS_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerAnimFlags final: public PlayerPacket
    {
    public:
        PacketPlayerAnimFlags(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERANIMFLAGS_HPP
