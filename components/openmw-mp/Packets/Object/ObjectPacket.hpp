#ifndef OPENMW_OBJECTPACKET_HPP
#define OPENMW_OBJECTPACKET_HPP

#include <string>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <PacketPriority.h>
#include <components/openmw-mp/Base/BaseObject.hpp>

#include <components/openmw-mp/Packets/BasePacket.hpp>


namespace mwmp
{
    class ObjectPacket: public BasePacket
    {
    public:
        explicit ObjectPacket(RakNet::RakPeerInterface *peer);

        ~ObjectPacket() override = default;

        void setObjectList(BaseObjectList *objectList);

        void Packet(RakNet::BitStream *bs, bool send) override;

    protected:
        virtual void Object(BaseObject &baseObject, bool send);
        bool PacketHeader(RakNet::BitStream *bs, bool send);
        BaseObjectList *objectList;
        static const int maxObjects = 3000;
        bool hasCellData;
    };
}

#endif //OPENMW_OBJECTPACKET_HPP
