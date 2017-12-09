#ifndef OPENMW_PACKETGAMEWEATHER_HPP
#define OPENMW_PACKETGAMEWEATHER_HPP

#include <components/openmw-mp/Packets/Player/PlayerPacket.hpp>

namespace mwmp
{
    class PacketGameWeather final: public PlayerPacket
    {
    public:
        PacketGameWeather(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
    };
}

#endif //OPENMW_PACKETGAMEWEATHER_HPP
