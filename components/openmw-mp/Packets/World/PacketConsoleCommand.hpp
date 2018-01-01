#ifndef OPENMW_PACKETCONSOLECOMMAND_HPP
#define OPENMW_PACKETCONSOLECOMMAND_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketConsoleCommand final: public WorldPacket
    {
    public:
        explicit PacketConsoleCommand(RakNet::RakPeerInterface *peer);
        
        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETCONSOLECOMMAND_HPP
