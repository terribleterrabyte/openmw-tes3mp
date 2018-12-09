#include "Stats.hpp"

#include <iostream>

#include <components/esm/attr.hpp>
#include <components/esm/loadskil.hpp>
#include <components/misc/stringops.hpp>
#include <components/openmw-mp/Log.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>

using namespace std;
using namespace ESM;

extern "C" int StatsFunctions::GetAttributeCount() noexcept
{
    return Attribute::Length;
}

extern "C" int StatsFunctions::GetSkillCount() noexcept
{
    return Skill::Length;
}

extern "C" int StatsFunctions::GetAttributeId(const char *name) noexcept
{
    for (int x = 0; x < Attribute::Length; x++)
    {
        if (Misc::StringUtils::ciEqual(name, Attribute::sAttributeNames[x]))
        {
            return x;
        }
    }

    return -1;
}

extern "C" int StatsFunctions::GetSkillId(const char *name) noexcept
{
    for (int x = 0; x < Skill::Length; x++)
    {
        if (Misc::StringUtils::ciEqual(name, Skill::sSkillNames[x]))
        {
            return x;
        }
    }

    return -1;
}

extern "C" const char *StatsFunctions::GetAttributeName(unsigned short attributeId) noexcept
{
    if (attributeId >= Attribute::Length)
        return "invalid";

    return Attribute::sAttributeNames[attributeId].c_str();
}

extern "C" const char *StatsFunctions::GetSkillName(unsigned short skillId) noexcept
{
    if (skillId >= Skill::Length)
        return "invalid";

    return Skill::sSkillNames[skillId].c_str();
}

extern "C" const char *StatsFunctions::GetName(unsigned short pid) noexcept
{

    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npc.mName.c_str();
}

extern "C" const char *StatsFunctions::GetRace(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npc.mRace.c_str();
}

extern "C" const char *StatsFunctions::GetHead(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npc.mHead.c_str();
}

extern "C" const char *StatsFunctions::GetHairstyle(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npc.mHair.c_str();
}

extern "C" int StatsFunctions::GetIsMale(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, false);

    return player->npc.isMale();
}

extern "C" const char *StatsFunctions::GetBirthsign(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->birthsign.c_str();
}

extern "C" int StatsFunctions::GetLevel(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->creatureStats.mLevel;
}

extern "C" int StatsFunctions::GetLevelProgress(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npcStats.mLevelProgress;
}

extern "C" double StatsFunctions::GetHealthBase(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->creatureStats.mDynamic[0].mBase;
}

extern "C" double StatsFunctions::GetHealthCurrent(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->creatureStats.mDynamic[0].mCurrent;
}

extern "C" double StatsFunctions::GetMagickaBase(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->creatureStats.mDynamic[1].mBase;
}

extern "C" double StatsFunctions::GetMagickaCurrent(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->creatureStats.mDynamic[1].mCurrent;
}

extern "C" double StatsFunctions::GetFatigueBase(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->creatureStats.mDynamic[2].mBase;
}

extern "C" double StatsFunctions::GetFatigueCurrent(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    return player->creatureStats.mDynamic[2].mCurrent;
}

extern "C" int StatsFunctions::GetAttributeBase(unsigned short pid, unsigned short attributeId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (attributeId >= Attribute::Length)
        return 0;

    return player->creatureStats.mAttributes[attributeId].mBase;
}

extern "C" int StatsFunctions::GetAttributeModifier(unsigned short pid, unsigned short attributeId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (attributeId >= Attribute::Length)
        return 0;

    return player->creatureStats.mAttributes[attributeId].mMod;
}

extern "C" int StatsFunctions::GetSkillBase(unsigned short pid, unsigned short skillId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (skillId >= Skill::Length)
        return 0;

    return player->npcStats.mSkills[skillId].mBase;
}

extern "C" int StatsFunctions::GetSkillModifier(unsigned short pid, unsigned short skillId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (skillId >= Skill::Length)
        return 0;

    return player->npcStats.mSkills[skillId].mMod;
}

extern "C" double StatsFunctions::GetSkillProgress(unsigned short pid, unsigned short skillId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0.0f);

    if (skillId >= Skill::Length)
        return 0;

    return player->npcStats.mSkills[skillId].mProgress;
}

extern "C" int StatsFunctions::GetSkillIncrease(unsigned short pid, unsigned int attributeId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (attributeId > Attribute::Length)
        return 0;

    return player->npcStats.mSkillIncrease[attributeId];
}

extern "C" int StatsFunctions::GetBounty(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npcStats.mBounty;
}

extern "C" void StatsFunctions::SetName(unsigned short pid, const char *name) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (player->npc.mName == name)
        return;

    player->npc.mName = name;
}

extern "C" void StatsFunctions::SetRace(unsigned short pid, const char *race) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (player->npc.mRace == race)
        return;

    LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Setting race for %s: %s -> %s", player->npc.mName.c_str(),
                       player->npc.mRace.c_str(), race);

    player->npc.mRace = race;
}

extern "C" void StatsFunctions::SetHead(unsigned short pid, const char *head) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (player->npc.mHead == head)
        return;

    player->npc.mHead = head;
}

extern "C" void StatsFunctions::SetHairstyle(unsigned short pid, const char *hairstyle) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (player->npc.mHair == hairstyle)
        return;

    player->npc.mHair = hairstyle;
}

extern "C" void StatsFunctions::SetIsMale(unsigned short pid, int state) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->npc.setIsMale(state == true);
}

extern "C" void StatsFunctions::SetBirthsign(unsigned short pid, const char *sign) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    if (player->birthsign == sign)
        return;

    player->birthsign = sign;
}

extern "C" void StatsFunctions::SetResetStats(unsigned short pid, bool resetStats) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->resetStats = resetStats;
}

extern "C" void StatsFunctions::SetLevel(unsigned short pid, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->creatureStats.mLevel = value;
}

extern "C" void StatsFunctions::SetLevelProgress(unsigned short pid, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->npcStats.mLevelProgress = value;
}

extern "C" void StatsFunctions::SetHealthBase(unsigned short pid, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->creatureStats.mDynamic[0].mBase = value;

    if (!Utils::vectorContains(player->statsDynamicIndexChanges, 0))
        player->statsDynamicIndexChanges.push_back(0);
}

extern "C" void StatsFunctions::SetHealthCurrent(unsigned short pid, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->creatureStats.mDynamic[0].mCurrent = value;

    if (!Utils::vectorContains(player->statsDynamicIndexChanges, 0))
        player->statsDynamicIndexChanges.push_back(0);
}

extern "C" void StatsFunctions::SetMagickaBase(unsigned short pid, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->creatureStats.mDynamic[1].mBase = value;

    if (!Utils::vectorContains(player->statsDynamicIndexChanges, 1))
        player->statsDynamicIndexChanges.push_back(1);
}

extern "C" void StatsFunctions::SetMagickaCurrent(unsigned short pid, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->creatureStats.mDynamic[1].mCurrent = value;

    if (!Utils::vectorContains(player->statsDynamicIndexChanges, 1))
        player->statsDynamicIndexChanges.push_back(1);
}

extern "C" void StatsFunctions::SetFatigueBase(unsigned short pid, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->creatureStats.mDynamic[2].mBase = value;

    if (!Utils::vectorContains(player->statsDynamicIndexChanges, 2))
        player->statsDynamicIndexChanges.push_back(2);
}

extern "C" void StatsFunctions::SetFatigueCurrent(unsigned short pid, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->creatureStats.mDynamic[2].mCurrent = value;

    if (!Utils::vectorContains(player->statsDynamicIndexChanges, 2))
        player->statsDynamicIndexChanges.push_back(2);
}

extern "C" void StatsFunctions::SetAttributeBase(unsigned short pid, unsigned short attributeId, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (attributeId >= Attribute::Length)
        return;

    player->creatureStats.mAttributes[attributeId].mBase = value;

    if (!Utils::vectorContains(player->attributeIndexChanges, attributeId))
        player->attributeIndexChanges.push_back(attributeId);
}

extern "C" void StatsFunctions::ClearAttributeModifier(unsigned short pid, unsigned short attributeId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (attributeId >= Attribute::Length)
        return;

    player->creatureStats.mAttributes[attributeId].mMod = 0;

    if (!Utils::vectorContains(player->attributeIndexChanges, attributeId))
        player->attributeIndexChanges.push_back(attributeId);
}

extern "C" void StatsFunctions::SetSkillBase(unsigned short pid, unsigned short skillId, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (skillId >= Skill::Length)
        return;

    player->npcStats.mSkills[skillId].mBase = value;

    if (!Utils::vectorContains(player->skillIndexChanges, skillId))
        player->skillIndexChanges.push_back(skillId);
}

extern "C" void StatsFunctions::ClearSkillModifier(unsigned short pid, unsigned short skillId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (skillId >= Skill::Length)
        return;

    player->npcStats.mSkills[skillId].mMod = 0;

    if (!Utils::vectorContains(player->skillIndexChanges, skillId))
        player->skillIndexChanges.push_back(skillId);
}

extern "C" void StatsFunctions::SetSkillProgress(unsigned short pid, unsigned short skillId, double value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    if (skillId >= Skill::Length)
        return;

    player->npcStats.mSkills[skillId].mProgress = value;

    if (!Utils::vectorContains(player->skillIndexChanges, skillId))
        player->skillIndexChanges.push_back(skillId);
}

extern "C" void StatsFunctions::SetSkillIncrease(unsigned short pid, unsigned int attributeId, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (attributeId > Attribute::Length)
        return;

    player->npcStats.mSkillIncrease[attributeId] = value;

    if (!Utils::vectorContains(player->attributeIndexChanges, attributeId))
        player->attributeIndexChanges.push_back(attributeId);
}

extern "C" void StatsFunctions::SetBounty(unsigned short pid, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->npcStats.mBounty = value;
}

extern "C" void StatsFunctions::SetCharGenStage(unsigned short pid, int currentStage, int endStage) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->charGenState.currentStage = currentStage;
    player->charGenState.endStage = endStage;
    player->charGenState.isFinished = false;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_CHARGEN);
    packet->setPlayer(player);
    
    packet->Send(false);
}

extern "C" void StatsFunctions::SendBaseInfo(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_BASEINFO);
    packet->setPlayer(player);
    
    packet->Send(false);
    packet->Send(true);
}

extern "C" void StatsFunctions::SendStatsDynamic(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_STATS_DYNAMIC);
    packet->setPlayer(player);
    
    packet->Send(false);
    packet->Send(true);

    player->statsDynamicIndexChanges.clear();
}

extern "C" void StatsFunctions::SendAttributes(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_ATTRIBUTE);
    packet->setPlayer(player);
    
    packet->Send(false);
    packet->Send(true);

    player->attributeIndexChanges.clear();
}

extern "C" void StatsFunctions::SendSkills(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_SKILL);
    packet->setPlayer(player);
    
    packet->Send(false);
    packet->Send(true);

    player->skillIndexChanges.clear();
}

extern "C" void StatsFunctions::SendLevel(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_LEVEL);
    packet->setPlayer(player);
    
    packet->Send(false);
    packet->Send(true);
}

extern "C" void StatsFunctions::SendBounty(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_BOUNTY);
    packet->setPlayer(player);
    
    packet->Send(false);
    packet->Send(true);
}
