#ifndef OPENMW_PLAYERPACKETCONTROLLER_HPP
#define OPENMW_PLAYERPACKETCONTROLLER_HPP


#include "../Packets/Player/PlayerPacket.hpp"
#include "BasePacketController.hpp"

namespace mwmp
{
    class PlayerPacketController: public BasePacketController<PlayerPacket>
    {
    public:
        PlayerPacketController(RakNet::RakPeerInterface *peer);
    };
}

#endif //OPENMW_PLAYERPACKETCONTROLLER_HPP
