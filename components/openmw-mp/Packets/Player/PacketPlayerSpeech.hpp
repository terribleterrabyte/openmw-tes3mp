#ifndef OPENMW_PACKETPLAYERSPEECH_HPP
#define OPENMW_PACKETPLAYERSPEECH_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerSpeech final: public PlayerPacket
    {
    public:
        PacketPlayerSpeech(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERSPEECH_HPP
