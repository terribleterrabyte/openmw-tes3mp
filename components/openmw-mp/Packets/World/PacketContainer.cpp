#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>
#include "PacketContainer.hpp"

using namespace mwmp;

PacketContainer::PacketContainer(RakNet::RakPeerInterface *peer) : WorldPacket(peer)
{
    packetID = ID_CONTAINER;
    hasCellData = true;
}

void PacketContainer::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    RW(event->action, send);
    RW(event->containerSubAction, send);

    for (auto &&worldObject : event->worldObjects)
    {
        Object(worldObject, send);

        if (send)
        {
            worldObject.containerItemCount = (unsigned int) (worldObject.containerItems.size());
        }

        RW(worldObject.containerItemCount, send);

        if (!send)
        {
            worldObject.containerItems.clear();
            worldObject.containerItems.resize(worldObject.containerItemCount);
        }

        if (worldObject.containerItemCount > maxObjects || worldObject.refId.empty()
            || (worldObject.refNumIndex != 0 && worldObject.mpNum != 0))
        {
            event->isValid = false;
            return;
        }

        for (auto &&containerItem: worldObject.containerItems)
        {
            RW(containerItem.refId, send);
            RW(containerItem.count, send);
            RW(containerItem.charge, send);
            RW(containerItem.enchantmentCharge, send);
            RW(containerItem.actionCount, send);
        }
    }
}
