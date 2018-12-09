#include "Dialogue.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

using namespace mwmp;

extern "C" void DialogueFunctions::ClearTopicChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->topicChanges.topics.clear();
}

extern "C" unsigned int DialogueFunctions::GetTopicChangesSize(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->topicChanges.count;
}

extern "C" void DialogueFunctions::AddTopic(unsigned short pid, const char* topicId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::Topic topic;
    topic.topicId = topicId;

    player->topicChanges.topics.push_back(topic);
}

extern "C" const char *DialogueFunctions::GetTopicId(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->topicChanges.count)
        return "invalid";

    return player->topicChanges.topics.at(index).topicId.c_str();
}

extern "C" void DialogueFunctions::SendTopicChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_TOPIC);
    packet->setPlayer(player);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void DialogueFunctions::PlayAnimation(unsigned short pid, const char* groupname, int mode, int count, bool persist) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->animation.groupname = groupname;
    player->animation.mode = mode;
    player->animation.count = count;
    player->animation.persist = persist;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_ANIM_PLAY);
    packet->setPlayer(player);

    packet->Send(false);
    player->sendToLoaded(packet);
}

extern "C" void DialogueFunctions::PlaySpeech(unsigned short pid, const char* sound) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->sound = sound;

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_SPEECH);
    packet->setPlayer(player);

    packet->Send(false);
    player->sendToLoaded(packet);
}

extern "C" // All methods below are deprecated versions of methods from above

void DialogueFunctions::InitializeTopicChanges(unsigned short pid) noexcept
{
    ClearTopicChanges(pid);
}
