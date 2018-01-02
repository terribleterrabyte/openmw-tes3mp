//
// Created by koncord on 05.03.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>
#include <boost/foreach.hpp>
#include "PacketPreInit.hpp"

mwmp::PacketPreInit::PacketPreInit(RakNet::RakPeerInterface *peer) : BasePacket(peer)
{
    packetID = ID_GAME_PREINIT;
}

void mwmp::PacketPreInit::Packet(RakNet::BitStream *bs, bool send)
{
    BasePacket::Packet(bs, send);

    uint16_t size = checksums->size();
    RW(size, send);

    if(!send)
    {
        if(size > 256)
            return;
        checksums->clear();
        checksums->resize(size);
    }


    for (auto &&ppair : *checksums)
    {
        RW(ppair.first, send);

        uint8_t hashSize = ppair.second.size();

        RW(hashSize, send);

        if(!send)
        {
            if(hashSize > 16)
                return;
            ppair.second.resize(hashSize);
        }

        for (auto &&hash :ppair.second)
        {
            RW(hash, send);
        }
    }
}

void mwmp::PacketPreInit::setChecksums(mwmp::PacketPreInit::PluginContainer *checksums)
{
    this->checksums = checksums;
}
