//
// Created by koncord on 23.07.16.
//

#ifndef OPENMW_PACKETGUIBOXES_HPP
#define OPENMW_PACKETGUIBOXES_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGUIBoxes final: public PlayerPacket
    {
    public:
        PacketGUIBoxes(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETGUIBOXES_HPP
