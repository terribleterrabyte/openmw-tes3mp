//
// Created by koncord on 13.01.16.
//

#ifndef OPENMW_PACKETPLAYERATTACK_HPP
#define OPENMW_PACKETPLAYERATTACK_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerAttack final: public PlayerPacket
    {
    public:
        PacketPlayerAttack(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERATTACK_HPP
