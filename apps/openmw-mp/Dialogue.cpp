//
// Created by koncord on 15.08.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>

#include "Script/LuaState.hpp"
#include "Networking.hpp"

#include "Dialogue.hpp"
#include "Player.hpp"

void Dialogue::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Dialogue>("Dialogue",
    "addTopic", &Dialogue::addTopic,
    "getTopicId", &Dialogue::getTopicId,
    "size", &Dialogue::size,
    "reset", &Dialogue::reset);
}



Dialogue::Dialogue(Player *player) : BaseMgr(player)
{

}


void Dialogue::reset()
{
    player->topicChanges.topics.clear();
}

void Dialogue::processUpdate()
{
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_TOPIC);

    packet->setPlayer(player);
    packet->Send(/*toOthers*/ false);
}

void Dialogue::addTopic(const std::string &topicId)
{
    if (!isChanged())
        reset();
    setChanged();
    player->topicChanges.topics.push_back({topicId});
}

std::string Dialogue::getTopicId(unsigned int i) const
{
    return player->topicChanges.topics.at(i).topicId;
}

size_t Dialogue::size() const
{
    return player->topicChanges.topics.size();
}

void Dialogue::playAnimation(const std::string &groupname, int mode, int count, bool persist)
{
    player->animation.groupname = groupname;
    player->animation.mode = mode;
    player->animation.count = count;
    player->animation.persist = persist;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_ANIM_PLAY);
    packet->setPlayer(player);
    packet->Send(false);
    player->sendToLoaded(*packet);
}

void Dialogue::playSpeech(const std::string &sound)
{
    player->sound = sound;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_SPEECH);
    packet->setPlayer(player);
    packet->Send(false);
    player->sendToLoaded(*packet);
}
