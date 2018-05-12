#ifndef OPENMW_PACKETVIDEOPLAY_HPP
#define OPENMW_PACKETVIDEOPLAY_HPP

#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

namespace mwmp
{
    class PacketVideoPlay final: public ObjectPacket
    {
    public:
        explicit PacketVideoPlay(RakNet::RakPeerInterface *peer);

        void Object(WorldObject &obj, bool send) override;
    };
}

#endif //OPENMW_PACKETVIDEOPLAY_HPP
