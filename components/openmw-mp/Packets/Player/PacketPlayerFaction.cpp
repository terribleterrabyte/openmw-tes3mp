#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerFaction.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerFaction::PacketPlayerFaction(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_FACTION;
}

void PacketPlayerFaction::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);
    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->factionChanges.factions.size());

    RW(count, send);

    if (!send)
    {
        player->factionChanges.factions.clear();
        player->factionChanges.factions.resize(count);
    }

    for (auto &&faction : player->factionChanges.factions)
    {
        RW(faction.changes, send, true);

        RW(faction.factionId, send, true);

        if (faction.isRankChanged())
            RW(faction.rank, send);

        if (faction.isExpulsionChanged())
            RW(faction.isExpelled, send);

        if (faction.isReputationChanged())
            RW(faction.reputation, send);
    }
}
