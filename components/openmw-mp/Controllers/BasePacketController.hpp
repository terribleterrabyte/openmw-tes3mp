//
// Created by koncord on 26.02.18.
//

#pragma once


#include <RakNetTypes.h>
#include <unordered_map>
#include <memory>

namespace mwmp
{
    template<typename PacketT>
    class BasePacketController
    {
    public:
        bool ContainsPacket(RakNet::MessageID id) const
        {
            return packets.count(id) == 1;
        }

        PacketT *GetPacket(RakNet::MessageID id)
        {
            return packets.at(id).get(); //operator[] calls rehash() if key not found, that not applicable here.
        }

        void SetStream(RakNet::BitStream *inStream, RakNet::BitStream *outStream)
        {
            for (const auto &packet : packets)
                packet.second->SetStreams(inStream, outStream);
        }

        typedef std::unordered_map<RakNet::MessageID, std::unique_ptr<PacketT> > packets_t;

    protected:
        template <typename T>
        inline void static AddPacket(packets_t *packets, RakNet::RakPeerInterface *peer)
        {
            auto packet = new T(peer);
            RakNet::MessageID packetId = packet->GetPacketID();
            packets->emplace(packetId, packet);
        }

    protected:
        packets_t packets;
    };
}
