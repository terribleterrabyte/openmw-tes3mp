#include "PacketPlayerAttribute.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerAttribute::PacketPlayerAttribute(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_ATTRIBUTE;
}

void PacketPlayerAttribute::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    uint32_t count;
    if (send)
        count = static_cast<uint32_t>(player->attributeChanges.attributeIndexes.size());

    RW(count, send);

    if (!send)
    {
        player->attributeChanges.attributeIndexes.clear();
        player->attributeChanges.attributeIndexes.resize(count);
    }

    for (auto &&attributeIndex :  player->attributeChanges.attributeIndexes)
    {
        RW(attributeIndex, send);

        RW(player->creatureStats.mAttributes[attributeIndex], send);
        RW(player->npcStats.mSkillIncrease[attributeIndex], send);
    }
}
