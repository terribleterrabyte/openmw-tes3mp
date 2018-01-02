#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerQuickKeys.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerQuickKeys::PacketPlayerQuickKeys(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_QUICKKEYS;
}

void PacketPlayerQuickKeys::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->quickKeyChanges.quickKeys.size());

    RW(count, send);

    for (auto &&quickKey : player->quickKeyChanges.quickKeys)
    {
        RW(quickKey.type, send);
        RW(quickKey.slot, send);

        if (quickKey.type != QuickKey::Type::Unassigned)
            RW(quickKey.itemId, send);
    }
}
