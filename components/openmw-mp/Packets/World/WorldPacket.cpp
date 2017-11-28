#include <components/openmw-mp/NetworkMessages.hpp>
#include <PacketPriority.h>
#include <RakPeer.h>
#include "WorldPacket.hpp"

using namespace mwmp;

WorldPacket::WorldPacket(RakNet::RakPeerInterface *peer) : BasePacket(peer)
{
    hasCellData = false;
    packetID = 0;
    priority = HIGH_PRIORITY;
    reliability = RELIABLE_ORDERED;
    orderChannel = CHANNEL_WORLDEVENT;
    this->peer = peer;
}

WorldPacket::~WorldPacket()
{

}

void WorldPacket::setEvent(BaseEvent *event)
{
    this->event = event;
    guid = event->guid;
}

void WorldPacket::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    for (auto &&worldObject : event->worldObjects)
    {
        Object(worldObject, send);
    }
}

bool WorldPacket::PacketHeader(RakNet::BitStream *bs, bool send)
{
    BasePacket::Packet(bs, send);

    if (send)
        event->worldObjectCount = (unsigned int)(event->worldObjects.size());
    else
        event->worldObjects.clear();

    RW(event->worldObjectCount, send);

    if (event->worldObjectCount > maxObjects)
    {
        event->isValid = false;
        return false;
    }

    if(!send)
    {
        event->worldObjects.resize(event->worldObjectCount);
    }

    if (hasCellData)
    {
        RW(event->cell.mData, send, true);
        RW(event->cell.mName, send, true);
    }

    return true;
}

void WorldPacket::Object(WorldObject &worldObject, bool send)
{
    RW(worldObject.refId, send);
    RW(worldObject.refNumIndex, send);
    RW(worldObject.mpNum, send);
}
