#include "../Packets/World/PacketObjectAnimPlay.hpp"
#include "../Packets/World/PacketObjectAttach.hpp"
#include "../Packets/World/PacketObjectCollision.hpp"
#include "../Packets/World/PacketObjectDelete.hpp"
#include "../Packets/World/PacketObjectLock.hpp"
#include "../Packets/World/PacketObjectMove.hpp"
#include "../Packets/World/PacketObjectPlace.hpp"
#include "../Packets/World/PacketObjectReset.hpp"
#include "../Packets/World/PacketObjectRotate.hpp"
#include "../Packets/World/PacketObjectScale.hpp"
#include "../Packets/World/PacketObjectSpawn.hpp"
#include "../Packets/World/PacketObjectState.hpp"
#include "../Packets/World/PacketObjectTrap.hpp"

#include "../Packets/World/PacketContainer.hpp"
#include "../Packets/World/PacketDoorDestination.hpp"
#include "../Packets/World/PacketDoorState.hpp"
#include "../Packets/World/PacketMusicPlay.hpp"
#include "../Packets/World/PacketVideoPlay.hpp"

#include "../Packets/World/PacketConsoleCommand.hpp"
#include "../Packets/World/PacketScriptLocalShort.hpp"
#include "../Packets/World/PacketScriptLocalFloat.hpp"
#include "../Packets/World/PacketScriptMemberShort.hpp"
#include "../Packets/World/PacketScriptMemberFloat.hpp"
#include "../Packets/World/PacketScriptGlobalShort.hpp"
#include "../Packets/World/PacketScriptGlobalFloat.hpp"

#include "WorldPacketController.hpp"

mwmp::WorldPacketController::WorldPacketController(RakNet::RakPeerInterface *peer)
{
    AddPacket<PacketObjectAnimPlay>(&packets, peer);
    AddPacket<PacketObjectAttach>(&packets, peer);
    AddPacket<PacketObjectCollision>(&packets, peer);
    AddPacket<PacketObjectDelete>(&packets, peer);
    AddPacket<PacketObjectLock>(&packets, peer);
    AddPacket<PacketObjectMove>(&packets, peer);
    AddPacket<PacketObjectPlace>(&packets, peer);
    AddPacket<PacketObjectReset>(&packets, peer);
    AddPacket<PacketObjectRotate>(&packets, peer);
    AddPacket<PacketObjectScale>(&packets, peer);
    AddPacket<PacketObjectSpawn>(&packets, peer);
    AddPacket<PacketObjectState>(&packets, peer);
    AddPacket<PacketObjectTrap>(&packets, peer);
    
    AddPacket<PacketContainer>(&packets, peer);
    AddPacket<PacketDoorDestination>(&packets, peer);
    AddPacket<PacketDoorState>(&packets, peer);
    AddPacket<PacketMusicPlay>(&packets, peer);
    AddPacket<PacketVideoPlay>(&packets, peer);

    AddPacket<PacketConsoleCommand>(&packets, peer);
    AddPacket<PacketScriptLocalShort>(&packets, peer);
    AddPacket<PacketScriptLocalFloat>(&packets, peer);
    AddPacket<PacketScriptMemberShort>(&packets, peer);
    AddPacket<PacketScriptMemberFloat>(&packets, peer);
    AddPacket<PacketScriptGlobalShort>(&packets, peer);
    AddPacket<PacketScriptGlobalFloat>(&packets, peer);
}
