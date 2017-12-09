//
// Created by koncord on 05.03.17.
//

#ifndef OPENMW_PACKETPREINIT_HPP
#define OPENMW_PACKETPREINIT_HPP

#include <vector>
#include "BasePacket.hpp"


namespace mwmp
{
    class PacketPreInit final: public BasePacket
    {
    public:
        typedef std::vector<unsigned> HashList;
        typedef std::pair<std::string, HashList> PluginPair;
        typedef std::vector<PluginPair> PluginContainer;

        explicit PacketPreInit(RakNet::RakPeerInterface *peer);

        void Packet(RakNet::BitStream *bs, bool send) override;
        void setChecksums(PluginContainer *checksums);
    private:
        PluginContainer *checksums;
    };
}


#endif //OPENMW_PACKETPREINIT_HPP
