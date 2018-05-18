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
    orderChannel = CHANNEL_OBJECT;
    this->peer = peer;
}

void ObjectPacket::setObjectList(BaseObjectList *objectList)
{
    this->objectList = objectList;
    guid = objectList->guid;
}

void ObjectPacket::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    for (auto &&baseObject : objectList->baseObjects)
    {
        Object(baseObject, send);
    }
}

bool ObjectPacket::PacketHeader(RakNet::BitStream *bs, bool send)
{
    BasePacket::Packet(bs, send);

    uint32_t baseObjectCount;

    if (send)
        baseObjectCount = (uint32_t) (objectList->baseObjects.size());

    RW(baseObjectCount, send);

    if (baseObjectCount > maxObjects)
    {
        objectList->isValid = false;
        return false;
    }

    if (!send)
    {
        objectList->baseObjects.clear();
        objectList->baseObjects.resize(baseObjectCount);
    }

    if (hasCellData)
    {
        RW(objectList->cell.mData, send, true);
        RW(objectList->cell.mName, send, true);
    }

    return true;
}

void ObjectPacket::Object(BaseObject &baseObject, bool send)
{
    RW(baseObject.refId, send);
    RW(baseObject.refNumIndex, send);
    RW(baseObject.mpNum, send);
}
