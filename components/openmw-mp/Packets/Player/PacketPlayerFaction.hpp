#ifndef OPENMW_PACKETPLAYERFACTION_HPP
#define OPENMW_PACKETPLAYERFACTION_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerFaction final: public PlayerPacket
    {
    public:
        PacketPlayerFaction(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERFACTION_HPP
