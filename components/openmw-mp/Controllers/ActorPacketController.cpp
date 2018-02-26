#include "../Packets/Actor/PacketActorList.hpp"
#include "../Packets/Actor/PacketActorAuthority.hpp"
#include "../Packets/Actor/PacketActorTest.hpp"
#include "../Packets/Actor/PacketActorAI.hpp"
#include "../Packets/Actor/PacketActorAnimFlags.hpp"
#include "../Packets/Actor/PacketActorAnimPlay.hpp"
#include "../Packets/Actor/PacketActorAttack.hpp"
#include "../Packets/Actor/PacketActorCellChange.hpp"
#include "../Packets/Actor/PacketActorDeath.hpp"
#include "../Packets/Actor/PacketActorEquipment.hpp"
#include "../Packets/Actor/PacketActorInteraction.hpp"
#include "../Packets/Actor/PacketActorPosition.hpp"
#include "../Packets/Actor/PacketActorStatsDynamic.hpp"
#include "../Packets/Actor/PacketActorSpeech.hpp"


#include "ActorPacketController.hpp"

mwmp::ActorPacketController::ActorPacketController(RakNet::RakPeerInterface *peer)
{
    AddPacket<PacketActorList>(&packets, peer);
    AddPacket<PacketActorAuthority>(&packets, peer);
    AddPacket<PacketActorTest>(&packets, peer);
    AddPacket<PacketActorAI>(&packets, peer);
    AddPacket<PacketActorAnimFlags>(&packets, peer);
    AddPacket<PacketActorAnimPlay>(&packets, peer);
    AddPacket<PacketActorAttack>(&packets, peer);
    AddPacket<PacketActorCellChange>(&packets, peer);
    AddPacket<PacketActorDeath>(&packets, peer);
    AddPacket<PacketActorEquipment>(&packets, peer);
    AddPacket<PacketActorInteraction>(&packets, peer);
    AddPacket<PacketActorPosition>(&packets, peer);
    AddPacket<PacketActorSpeech>(&packets, peer);
    AddPacket<PacketActorStatsDynamic>(&packets, peer);
}
