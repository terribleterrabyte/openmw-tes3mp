#include "../Packets/Worldstate/PacketWorldTime.hpp"

#include "WorldstatePacketController.hpp"

mwmp::WorldstatePacketController::WorldstatePacketController(RakNet::RakPeerInterface *peer)
{
    AddPacket<PacketWorldTime>(&packets, peer);
}
