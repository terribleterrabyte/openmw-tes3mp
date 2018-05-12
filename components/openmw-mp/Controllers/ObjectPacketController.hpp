#ifndef OPENMW_WORLDPACKETCONTROLLER_HPP
#define OPENMW_WORLDPACKETCONTROLLER_HPP


#include "../Packets/Object/ObjectPacket.hpp"
#include "BasePacketController.hpp"

namespace mwmp
{
    class ObjectPacketController: public BasePacketController<ObjectPacket>
    {
    public:
        ObjectPacketController(RakNet::RakPeerInterface *peer);
    };
}

#endif //OPENMW_WORLDPACKETCONTROLLER_HPP
