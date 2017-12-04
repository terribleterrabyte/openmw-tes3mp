//
// Created by koncord on 15.11.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>
#include "PacketGUIWindow.hpp"

using namespace mwmp;

PacketGUIWindow::PacketGUIWindow(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{

    packetID = ID_GUI_WINDOW;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketGUIWindow::Packet(RakNet::BitStream *bs, bool send)
{
    BasePacket::Packet(bs, send);

    RW(player->guiWindow.id, send);
    RW(player->guiWindow.height, send);
    RW(player->guiWindow.width, send);

    int32_t size;
    if (send)
        size = static_cast<int32_t>(player->guiWindow.widgets.size());
    RW(size, send);

    if (!send)
        player->guiWindow.widgets.resize(size);


    for (auto &&widget : player->guiWindow.widgets)
    {
        RW(widget.type, send);
        RW(widget.name, send);
        RW(widget.posX, send);
        RW(widget.posY, send);

        if (widget.type != BasePlayer::GUIWindow::WidgetType::Label)
        {
            RW(widget.disabled, send);

            if (widget.type != BasePlayer::GUIWindow::WidgetType::Button)
            {
                RW(widget.width, send);
                RW(widget.height, send);

                size = widget.data.size();
                RW(size, send);
                if (!send)
                    widget.data.resize(size);
                for (auto &&str : widget.data)
                    RW(str, send);
            }
        }
    }

}
