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

    RW(player->factionChanges.action, send);

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
        RW(faction.factionId, send, true);

        if (player->factionChanges.action == FactionChanges::Type::Rank)
            RW(faction.rank, send);

        if (player->factionChanges.action == FactionChanges::Type::Expulsion)
            RW(faction.isExpelled, send);

        if (player->factionChanges.action == FactionChanges::Type::Reputation)
            RW(faction.reputation, send);
    }
}
