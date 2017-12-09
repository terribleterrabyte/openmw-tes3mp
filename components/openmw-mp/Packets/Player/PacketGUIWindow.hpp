//
// Created by koncord on 15.11.17.
//

#pragma once


#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGUIWindow final: public PlayerPacket
    {
    public:
        PacketGUIWindow(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}
