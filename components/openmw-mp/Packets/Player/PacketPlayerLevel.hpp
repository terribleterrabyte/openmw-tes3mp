#ifndef OPENMW_PACKETPLAYERLEVEL_HPP
#define OPENMW_PACKETPLAYERLEVEL_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerLevel final: public PlayerPacket
    {
    public:
        PacketPlayerLevel(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERLEVEL_HPP
