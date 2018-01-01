#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketConsoleCommand.hpp"

using namespace mwmp;

PacketConsoleCommand::PacketConsoleCommand(RakNet::RakPeerInterface *peer) : WorldPacket(peer)
{
    packetID = ID_CONSOLE_COMMAND;
}

void PacketConsoleCommand::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    RW(event->consoleCommand, send);

    WorldObject worldObject;
    for (auto &&worldObject : event->worldObjects)
    {
        RW(worldObject.isPlayer, send);

        if (worldObject.isPlayer)
            RW(worldObject.guid, send);
        else
            Object(worldObject, send);
    }
}
