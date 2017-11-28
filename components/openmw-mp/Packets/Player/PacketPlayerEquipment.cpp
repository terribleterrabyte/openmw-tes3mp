//
// Created by koncord on 07.01.16.
//

#include "PacketPlayerEquipment.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerEquipment::PacketPlayerEquipment(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_EQUIPMENT;
}

void PacketPlayerEquipment::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    for (auto &equipedItem : player->equipedItems)
    {
        RW(equipedItem.refId, send, true);
        RW(equipedItem.count, send);
        RW(equipedItem.charge, send);
    }
}
