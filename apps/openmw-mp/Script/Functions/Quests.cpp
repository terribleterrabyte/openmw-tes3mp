#include "Quests.hpp"

#include <components/misc/stringops.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

using namespace mwmp;

extern "C" void QuestFunctions::ClearJournalChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->journalChanges.journalItems.clear();
}

extern "C" void QuestFunctions::ClearKillChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->killChanges.kills.clear();
}

extern "C" unsigned int QuestFunctions::GetJournalChangesSize(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->journalChanges.count;
}

extern "C" unsigned int QuestFunctions::GetKillChangesSize(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->killChanges.count;
}

extern "C" void QuestFunctions::AddJournalEntry(unsigned short pid, const char* quest, unsigned int index, const char* actorRefId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::JournalItem journalItem;
    journalItem.type = JournalItem::ENTRY;
    journalItem.quest = quest;
    journalItem.index = index;
    journalItem.actorRefId = actorRefId;
    journalItem.hasTimestamp = false;

    player->journalChanges.journalItems.push_back(journalItem);
}

extern "C" void QuestFunctions::AddJournalEntryWithTimestamp(unsigned short pid, const char* quest, unsigned int index, const char* actorRefId,
    unsigned int daysPassed, unsigned int month, unsigned int day) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::JournalItem journalItem;
    journalItem.type = JournalItem::ENTRY;
    journalItem.quest = quest;
    journalItem.index = index;
    journalItem.actorRefId = actorRefId;
    journalItem.hasTimestamp = true;

    journalItem.timestamp.daysPassed = daysPassed;
    journalItem.timestamp.month = month;
    journalItem.timestamp.day = day;

    player->journalChanges.journalItems.push_back(journalItem);
}

extern "C" void QuestFunctions::AddJournalIndex(unsigned short pid, const char* quest, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::JournalItem journalItem;
    journalItem.type = JournalItem::INDEX;
    journalItem.quest = quest;
    journalItem.index = index;

    player->journalChanges.journalItems.push_back(journalItem);
}

extern "C" void QuestFunctions::AddKill(unsigned short pid, const char* refId, int number) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::Kill kill;
    kill.refId = refId;
    kill.number = number;

    player->killChanges.kills.push_back(kill);
}

extern "C" void QuestFunctions::SetReputation(unsigned short pid, int value) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->npcStats.mReputation = value;
}

extern "C" const char *QuestFunctions::GetJournalItemQuest(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->journalChanges.count)
        return "invalid";

    return player->journalChanges.journalItems.at(index).quest.c_str();
}

extern "C" int QuestFunctions::GetJournalItemIndex(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->journalChanges.journalItems.at(index).index;
}

extern "C" int QuestFunctions::GetJournalItemType(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->journalChanges.journalItems.at(index).type;
}

extern "C" const char *QuestFunctions::GetJournalItemActorRefId(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->journalChanges.journalItems.at(index).actorRefId.c_str();
}

extern "C" const char *QuestFunctions::GetKillRefId(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->killChanges.count)
        return "invalid";

    return player->killChanges.kills.at(index).refId.c_str();
}

extern "C" int QuestFunctions::GetKillNumber(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->killChanges.kills.at(index).number;
}

extern "C" int QuestFunctions::GetReputation(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->npcStats.mReputation;
}

extern "C" void QuestFunctions::SendJournalChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_JOURNAL);
    packet->setPlayer(player);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void QuestFunctions::SendKillChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_WORLD_KILL_COUNT);
    packet->setPlayer(player);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void QuestFunctions::SendReputation(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_REPUTATION);
    packet->setPlayer(player);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" // All methods below are deprecated versions of methods from above

void QuestFunctions::InitializeJournalChanges(unsigned short pid) noexcept
{
    ClearJournalChanges(pid);
}

extern "C" void QuestFunctions::InitializeKillChanges(unsigned short pid) noexcept
{
    ClearKillChanges(pid);
}
