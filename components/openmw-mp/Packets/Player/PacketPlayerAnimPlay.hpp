#ifndef OPENMW_PACKETPLAYERANIMPLAY_HPP
#define OPENMW_PACKETPLAYERANIMPLAY_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerAnimPlay final: public PlayerPacket
    {
    public:
        PacketPlayerAnimPlay(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERANIMPLAY_HPP
