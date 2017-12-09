#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketActorList.hpp"

using namespace mwmp;

PacketActorList::PacketActorList(RakNet::RakPeerInterface *peer) : ActorPacket(peer)
{
    packetID = ID_ACTOR_LIST;
}

void PacketActorList::Packet(RakNet::BitStream *bs, bool send)
{
    if (!ActorPacket::PacketHeader(bs, send))
        return;

    RW(actorList->action, send);

    for(auto &actor : actorList->baseActors)
    {
        RW(actor->refId, send);
        RW(actor->refNumIndex, send);
        RW(actor->mpNum, send);

        if (actor->refId.empty() || (actor->refNumIndex != 0 && actor->mpNum != 0))
        {
            actorList->isValid = false;
            return;
        }
    }
}
