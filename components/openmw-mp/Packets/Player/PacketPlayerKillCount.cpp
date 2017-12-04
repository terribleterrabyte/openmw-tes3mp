#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerKillCount.hpp"

mwmp::PacketPlayerKillCount::PacketPlayerKillCount(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_KILL_COUNT;
}

void mwmp::PacketPlayerKillCount::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);
    
    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->killChanges.kills.size());

    RW(count, send);

    if (!send)
    {
        player->killChanges.kills.clear();
        player->killChanges.kills.resize(count);
    }

    for (auto &&kill : player->killChanges.kills)
    {
        RW(kill.refId, send, true);
        RW(kill.number, send);
    }
}
