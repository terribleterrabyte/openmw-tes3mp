#ifndef OPENMW_PACKETPLAYERSPELLBOOK_HPP
#define OPENMW_PACKETPLAYERSPELLBOOK_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerSpellbook final: public PlayerPacket
    {
    public:
        PacketPlayerSpellbook(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERSPELLBOOK_HPP
