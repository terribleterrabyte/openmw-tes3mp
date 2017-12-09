#include <components/openmw-mp/NetworkMessages.hpp>
#include <PacketPriority.h>
#include <RakPeer.h>
#include "ActorPacket.hpp"

using namespace mwmp;

ActorPacket::ActorPacket(RakNet::RakPeerInterface *peer) : BasePacket(peer)
{
    packetID = 0;
    priority = HIGH_PRIORITY;
    reliability = RELIABLE_ORDERED;
    orderChannel = CHANNEL_ACTOR;
    this->peer = peer;
}

void ActorPacket::setActorList(BaseActorList *actorList)
{
    this->actorList = actorList;
    guid = actorList->guid;
}

void ActorPacket::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    for(auto &actor : actorList->baseActors)
    {
        RW(actor->refNumIndex, send);
        RW(actor->mpNum, send);
        Actor(*actor, send);
    }

}

bool ActorPacket::PacketHeader(RakNet::BitStream *bs, bool send)
{
    BasePacket::Packet(bs, send);

    RW(actorList->cell.mData, send, true);
    RW(actorList->cell.mName, send, true);

    uint32_t actorCount;
    if (send)
        actorCount = (uint32_t)(actorList->baseActors.size());

    RW(actorCount, send);

    if(!send)
    {
        actorList->baseActors.clear();
        actorList->baseActors.resize(actorCount, std::make_shared<BaseActor>());
    }

    if (actorCount > maxActors)
    {
        actorList->isValid = false;
        return false;
    }

    return true;
}