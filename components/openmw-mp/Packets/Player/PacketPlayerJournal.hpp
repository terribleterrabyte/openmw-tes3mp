#ifndef OPENMW_PACKETPLAYERJOURNAL_HPP
#define OPENMW_PACKETPLAYERJOURNAL_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerJournal final: public PlayerPacket
    {
    public:
        PacketPlayerJournal(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERJOURNAL_HPP
