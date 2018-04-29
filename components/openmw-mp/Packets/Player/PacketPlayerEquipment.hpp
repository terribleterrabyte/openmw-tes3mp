//
// Created by koncord on 07.01.16.
//

#ifndef OPENMW_PACKETPLAYEREQUIPMENT_HPP
#define OPENMW_PACKETPLAYEREQUIPMENT_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketPlayerEquipment final: public PlayerPacket
    {
    public:
        PacketPlayerEquipment(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
        void ExchangeItemInformation(Item &item, bool send);
    };
}

#endif //OPENMW_PACKETPLAYEREQUIPMENT_HPP
