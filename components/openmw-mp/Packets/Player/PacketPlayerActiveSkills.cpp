//
// Created by koncord on 03.12.16.
//

#include "PacketPlayerActiveSkills.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketPlayerActiveSkills::PacketPlayerActiveSkills(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_PLAYER_ACTIVESKILLS;
}

void PacketPlayerActiveSkills::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    uint32_t spellCount = 0;

    if (send)
        spellCount = static_cast<uint32_t>(player->activeSpells.mSpells.size());

    RW(spellCount, send);

    auto fnRWSpell = [this, &send](ESM::ActiveSpells::TContainer::value_type &spell) {
        RW(spell.first, send);
        RW(spell.second.mTimeStamp, send);
        uint32_t effectsCount;

        if(send)
            effectsCount = static_cast<uint32_t>(spell.second.mEffects.size());

        RW(effectsCount, send);

        if(!send)
            spell.second.mEffects.resize(effectsCount);

        for (auto &&effect : spell.second.mEffects)
            RW(effect, send);
    };

    if (send)
        for (auto && spell : player->activeSpells.mSpells)
        {
            fnRWSpell(spell);
        }
    else
        for (unsigned int i = 0; i < spellCount; i++)
        {
            ESM::ActiveSpells::TContainer::value_type spell;
            fnRWSpell(spell);
            player->activeSpells.mSpells.insert(spell);
        }
}
