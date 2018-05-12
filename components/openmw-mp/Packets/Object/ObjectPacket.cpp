#include <components/openmw-mp/NetworkMessages.hpp>
#include <PacketPriority.h>
#include <RakPeer.h>
#include "ObjectPacket.hpp"

using namespace mwmp;

ObjectPacket::ObjectPacket(RakNet::RakPeerInterface *peer) : BasePacket(peer)
{
    hasCellData = false;
    packetID = 0;
    priority = HIGH_PRIORITY;
    reliability = RELIABLE_ORDERED;
    orderChannel = CHANNEL_WORLDEVENT;
    this->peer = peer;
}

void ObjectPacket::setEvent(BaseEvent *event)
{
    this->event = event;
    guid = event->guid;
}

void ObjectPacket::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    for (auto &&worldObject : event->worldObjects)
    {
        Object(worldObject, send);
    }
}

bool ObjectPacket::PacketHeader(RakNet::BitStream *bs, bool send)
{
    BasePacket::Packet(bs, send);

    uint32_t worldObjectCount;

    if (send)
        worldObjectCount = (uint32_t) (event->worldObjects.size());

    RW(worldObjectCount, send);

    if (worldObjectCount > maxObjects)
    {
        event->isValid = false;
        return false;
    }

    if (!send)
    {
        event->worldObjects.clear();
        event->worldObjects.resize(worldObjectCount);
    }

    if (hasCellData)
    {
        RW(event->cell.mData, send, true);
        RW(event->cell.mName, send, true);
    }

    return true;
}

void ObjectPacket::Object(WorldObject &worldObject, bool send)
{
    RW(worldObject.refId, send);
    RW(worldObject.refNumIndex, send);
    RW(worldObject.mpNum, send);
}
