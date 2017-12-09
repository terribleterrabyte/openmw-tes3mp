#ifndef OPENMW_PACKETPLAYERREGIONCHANGE_HPP
#define OPENMW_PACKETPLAYERREGIONCHANGE_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerKillCount final: public PlayerPacket
    {
    public:
        PacketPlayerKillCount(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERREGIONCHANGE_HPP
