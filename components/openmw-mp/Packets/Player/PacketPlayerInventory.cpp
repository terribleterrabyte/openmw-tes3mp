//
// Created by koncord on 22.10.16.
//

#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerInventory.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerInventory::PacketPlayerInventory(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_INVENTORY;
}

void PacketPlayerInventory::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->inventoryChanges.items.size());

    RW(count, send);

    if (!send)
    {
        player->inventoryChanges.items.clear();
        player->inventoryChanges.items.resize(count);
    }

    for (auto &&item :  player->inventoryChanges.items)
    {
        RW(item.first.refId, send, true);
        RW(item.first.count, send);
        RW(item.first.charge, send);
        RW(item.first.enchantmentCharge, send);
        RW(item.second, send, true); // compress byte to bits
    }
}
