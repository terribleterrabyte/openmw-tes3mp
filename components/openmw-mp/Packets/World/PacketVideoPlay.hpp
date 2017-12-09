#ifndef OPENMW_PACKETVIDEOPLAY_HPP
#define OPENMW_PACKETVIDEOPLAY_HPP

#include <components/openmw-mp/Packets/World/WorldPacket.hpp>

namespace mwmp
{
    class PacketVideoPlay final: public WorldPacket
    {
    public:
        explicit PacketVideoPlay(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &obj, bool send) override;
    };
}

#endif //OPENMW_PACKETVIDEOPLAY_HPP
