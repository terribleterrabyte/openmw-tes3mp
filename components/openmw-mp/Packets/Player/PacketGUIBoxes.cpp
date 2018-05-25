#include "PacketGUIBoxes.hpp"
#include <components/openmw-mp/NetworkMessages.hpp>

using namespace mwmp;

PacketGUIBoxes::PacketGUIBoxes(RakNet::RakPeerInterface *peer) : PlayerPacket(peer)
{
    packetID = ID_GUI_MESSAGEBOX;
    orderChannel = CHANNEL_SYSTEM;
}

void PacketGUIBoxes::Packet(RakNet::BitStream *bs, bool send)
{
    PlayerPacket::Packet(bs, send);

    RW(player->guiMessageBox.id, send);
    RW(player->guiMessageBox.type, send);
    RW(player->guiMessageBox.label, send);

    RW(player->guiMessageBox.data, send);

    if (player->guiMessageBox.type == BasePlayer::GUIMessageBox::Type::CustomMessageBox)
        RW(player->guiMessageBox.buttons, send);
    else if (player->guiMessageBox.type == BasePlayer::GUIMessageBox::Type::InputDialog ||
        player->guiMessageBox.type == BasePlayer::GUIMessageBox::Type::PasswordDialog)
        RW(player->guiMessageBox.note, send);
}

