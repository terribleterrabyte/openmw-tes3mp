//
// Created by koncord on 03.12.16.
//

#ifndef OPENMW_PACKETPLAYERACTIVESKILLS_HPP
#define OPENMW_PACKETPLAYERACTIVESKILLS_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerActiveSkills final: public PlayerPacket
    {
    public:
        PacketPlayerActiveSkills(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERACTIVESKILLS_HPP
