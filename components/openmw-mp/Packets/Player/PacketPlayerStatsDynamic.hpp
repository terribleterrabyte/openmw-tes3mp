//
// Created by koncord on 13.01.16.
//

#ifndef OPENMW_PACKETSTATSDYNAMIC_HPP
#define OPENMW_PACKETSTATSDYNAMIC_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerStatsDynamic final: public PlayerPacket
    {
    public:
        PacketPlayerStatsDynamic(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETSTATSDYNAMIC_HPP
