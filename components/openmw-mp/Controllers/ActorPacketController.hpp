#ifndef OPENMW_ACTORPACKETCONTROLLER_HPP
#define OPENMW_ACTORPACKETCONTROLLER_HPP


#include "../Packets/Actor/ActorPacket.hpp"
#include "BasePacketController.hpp"

namespace mwmp
{
    class ActorPacketController: public BasePacketController<ActorPacket>
    {
    public:
        ActorPacketController(RakNet::RakPeerInterface *peer);
    };
}

#endif //OPENMW_ACTORPACKETCONTROLLER_HPP
