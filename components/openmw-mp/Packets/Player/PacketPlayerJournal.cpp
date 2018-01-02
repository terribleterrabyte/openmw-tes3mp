#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerJournal.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerJournal::PacketPlayerJournal(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_JOURNAL;
}

void PacketPlayerJournal::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    uint32_t count;

    if (send)
        count = static_cast<uint32_t>(player->journalChanges.journalItems.size());

    RW(count, send);

    if (!send)
    {
        player->journalChanges.journalItems.clear();
        player->journalChanges.journalItems.resize(count);
    }

    for (auto &&journalItem : player->journalChanges.journalItems)
    {
        RW(journalItem.type, send);
        RW(journalItem.quest, send, true);
        RW(journalItem.index, send);

        if (journalItem.type == JournalItem::Type::Entry)
            RW(journalItem.actorRefId, send, true);
    }
}
