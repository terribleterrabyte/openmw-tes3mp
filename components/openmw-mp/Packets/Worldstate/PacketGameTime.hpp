#ifndef OPENMW_PACKETGAMETIME_HPP
#define OPENMW_PACKETGAMETIME_HPP

#include <components/openmw-mp/Packets/Worldstate/WorldstatePacket.hpp>

namespace mwmp
{
    class PacketGameTime final : public WorldstatePacket
    {
    public:
        PacketGameTime(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETGAMETIME_HPP
