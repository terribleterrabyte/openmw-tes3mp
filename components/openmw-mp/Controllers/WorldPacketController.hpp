#ifndef OPENMW_WORLDPACKETCONTROLLER_HPP
#define OPENMW_WORLDPACKETCONTROLLER_HPP


#include "../Packets/World/WorldPacket.hpp"
#include "BasePacketController.hpp"

namespace mwmp
{
    class WorldPacketController: public BasePacketController<WorldPacket>
    {
    public:
        WorldPacketController(RakNet::RakPeerInterface *peer);
    };
}

#endif //OPENMW_WORLDPACKETCONTROLLER_HPP
