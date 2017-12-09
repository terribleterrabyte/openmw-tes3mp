#ifndef OPENMW_WORLDPACKET_HPP
#define OPENMW_WORLDPACKET_HPP

#include <string>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <PacketPriority.h>
#include <components/openmw-mp/Base/BaseEvent.hpp>

#include <components/openmw-mp/Packets/BasePacket.hpp>


namespace mwmp
{
    class WorldPacket: public BasePacket
    {
    public:
        explicit WorldPacket(RakNet::RakPeerInterface *peer);

        ~WorldPacket() override = default;

        void setEvent(BaseEvent *event);

        void Packet(RakNet::BitStream *bs, bool send) override;

    protected:
        virtual void Object(WorldObject &worldObject, bool send);
        bool PacketHeader(RakNet::BitStream *bs, bool send);
        BaseEvent *event;
        static const int maxObjects = 3000;
        bool hasCellData;
    };
}

#endif //OPENMW_WORLDPACKET_HPP
