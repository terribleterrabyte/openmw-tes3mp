//
// Created by koncord on 29.08.16.
//

#ifndef OPENMW_PACKETPLAYERCLASS_HPP
#define OPENMW_PACKETPLAYERCLASS_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerClass final: public PlayerPacket
    {
    public:
        PacketPlayerClass(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETPLAYERCLASS_HPP
