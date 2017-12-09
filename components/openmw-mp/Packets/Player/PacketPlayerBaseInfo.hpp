//
// Created by koncord on 07.01.16.
//

#ifndef OPENMW_PACKETPLAYERBASEINFO_HPP
#define OPENMW_PACKETPLAYERBASEINFO_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerBaseInfo final: public PlayerPacket
    {
    public:
        PacketPlayerBaseInfo(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERBASEINFO_HPP
