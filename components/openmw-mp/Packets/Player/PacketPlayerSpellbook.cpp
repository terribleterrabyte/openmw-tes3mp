#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketPlayerSpellbook.hpp"

using namespace std;
using namespace mwmp;

PacketPlayerSpellbook::PacketPlayerSpellbook(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_SPELLBOOK;
}

void PacketPlayerSpellbook::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    RW(player->spellbookChanges.action, send);

    uint32_t changesCount;
    
    if (send)
        changesCount = static_cast<uint32_t>(player->spellbookChanges.spells.size());

    RW(changesCount, send);

    if (!send)
    {
        player->spellbookChanges.spells.clear();
        player->spellbookChanges.spells.resize(changesCount);
    }

    for (auto &&spell : player->spellbookChanges.spells)
    {

        RW(spell.mId, send, true);

        if (spell.mId.find("$dynamic") != string::npos)
        {
            RW(spell.mName, send, true);

            RW(spell.mData.mType, send, true);
            RW(spell.mData.mCost, send, true);
            RW(spell.mData.mFlags, send, true);

            uint32_t effectCount;
            if (send)
                effectCount = static_cast<uint32_t>(spell.mEffects.mList.size());

            RW(effectCount, send, true);
            
            if (!send)
            {
                spell.mEffects.mList.resize(effectCount);
            }

            for (auto &&effect : spell.mEffects.mList)
            {

                RW(effect.mEffectID, send, true);
                RW(effect.mSkill, send, true);
                RW(effect.mAttribute, send, true);
                RW(effect.mRange, send, true);
                RW(effect.mArea, send, true);
                RW(effect.mDuration, send, true);
                RW(effect.mMagnMin, send, true);
                RW(effect.mMagnMax, send, true);
            }
        }
    }

}
