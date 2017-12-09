//
// Created by koncord on 22.10.16.
//

#ifndef OPENMW_PACKETPLAYERINVENTORY_HPP
#define OPENMW_PACKETPLAYERINVENTORY_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerInventory final: public PlayerPacket
    {
    public:
        PacketPlayerInventory(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERINVENTORY_HPP
