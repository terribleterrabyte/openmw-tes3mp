#include "../Packets/Worldstate/PacketGameTime.hpp"

#include "WorldstatePacketController.hpp"

mwmp::WorldstatePacketController::WorldstatePacketController(RakNet::RakPeerInterface *peer)
{
    AddPacket<PacketGameTime>(&packets, peer);
}
