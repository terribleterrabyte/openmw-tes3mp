#ifndef OPENMW_OBJECTPACKETCONTROLLER_HPP
#define OPENMW_OBJECTPACKETCONTROLLER_HPP


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

#endif //OPENMW_OBJECTPACKETCONTROLLER_HPP
