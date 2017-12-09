//
// Created by koncord on 30.08.16.
//

#ifndef OPENMW_PACKETGAMETIME_HPP
#define OPENMW_PACKETGAMETIME_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGameTime final: public PlayerPacket
    {
    public:
        PacketGameTime(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETGAMETIME_HPP
