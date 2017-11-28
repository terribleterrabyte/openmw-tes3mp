#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerMap.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerMap::PacketPlayerMap(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_MAP;
}

void PacketPlayerMap::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);
    
    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->mapChanges.cellsExplored.size());

    RW(count, send);

    if(!send)
    {
        player->mapChanges.cellsExplored.clear();
        player->mapChanges.cellsExplored.resize(count);
    }

    for (auto &&cellExplored : player->mapChanges.cellsExplored)
    {
        RW(cellExplored.mData, send, true);
        RW(cellExplored.mName, send, true);
    }
}
