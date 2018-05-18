#ifndef OPENMW_WORLDSTATEPACKETCONTROLLER_HPP
#define OPENMW_WORLDSTATEPACKETCONTROLLER_HPP


#include "../Packets/Worldstate/WorldstatePacket.hpp"
#include "BasePacketController.hpp"

namespace mwmp
{
    class WorldstatePacketController: public BasePacketController<WorldstatePacket>
    {
    public:
        WorldstatePacketController(RakNet::RakPeerInterface *peer);
    };
}

#endif //OPENMW_WORLDSTATEPACKETCONTROLLER_HPP
