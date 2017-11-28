#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>
#include "PacketActorEquipment.hpp"

using namespace mwmp;

PacketActorEquipment::PacketActorEquipment(RakNet::RakPeerInterface *peer) : ActorPacket(peer)
{
    packetID = ID_ACTOR_EQUIPMENT;
}

void PacketActorEquipment::Actor(BaseActor &actor, bool send)
{
    for (auto &&equipedItem : actor.equipedItems)
    {
        RW(equipedItem.refId, send);
        RW(equipedItem.count, send);
        RW(equipedItem.charge, send);
    }
}
