//
// Created by koncord on 15.11.17.
//

#pragma once


#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGUIWindow : public PlayerPacket
    {
    public:
        PacketGUIWindow(RakNet::RakPeerInterface *peer);

        virtual void Packet(RakNet::BitStream *bs, bool send);
    };
}
