#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>
#include "PacketContainer.hpp"

using namespace mwmp;

PacketContainer::PacketContainer(RakNet::RakPeerInterface *peer) : ObjectPacket(peer)
{
    packetID = ID_CONTAINER;
    hasCellData = true;
}

void PacketContainer::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    RW(objectList->action, send);
    RW(objectList->containerSubAction, send);

    for (auto &&baseObject : objectList->baseObjects)
    {
        Object(baseObject, send);

        if (send)
        {
            baseObject.containerItemCount = (unsigned int) (baseObject.containerItems.size());
        }

        RW(baseObject.containerItemCount, send);

        if (!send)
        {
            baseObject.containerItems.clear();
            baseObject.containerItems.resize(baseObject.containerItemCount);
        }

        if (baseObject.containerItemCount > maxObjects || baseObject.refId.empty()
            || (baseObject.refNumIndex != 0 && baseObject.mpNum != 0))
        {
            objectList->isValid = false;
            return;
        }

        for (auto &&containerItem: baseObject.containerItems)
        {
            RW(containerItem.refId, send);
            RW(containerItem.count, send);
            RW(containerItem.charge, send);
            RW(containerItem.enchantmentCharge, send);
            RW(containerItem.actionCount, send);
        }
    }
}
