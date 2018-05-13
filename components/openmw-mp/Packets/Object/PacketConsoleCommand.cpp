#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketConsoleCommand.hpp"

using namespace mwmp;

PacketConsoleCommand::PacketConsoleCommand(RakNet::RakPeerInterface *peer) : ObjectPacket(peer)
{
    packetID = ID_CONSOLE_COMMAND;
}

void PacketConsoleCommand::Packet(RakNet::BitStream *bs, bool send)
{
    if (!PacketHeader(bs, send))
        return;

    RW(objectList->consoleCommand, send);

    BaseObject baseObject;
    for (auto &&baseObject : objectList->baseObjects)
    {
        RW(baseObject.isPlayer, send);

        if (baseObject.isPlayer)
            RW(baseObject.guid, send);
        else
            Object(baseObject, send);
    }
}
