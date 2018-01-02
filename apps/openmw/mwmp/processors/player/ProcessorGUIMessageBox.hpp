//
// Created by koncord on 16.04.17.
//

#ifndef OPENMW_PROCESSORGUIMESSAGEBOX_HPP
#define OPENMW_PROCESSORGUIMESSAGEBOX_HPP


#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorGUIMessageBox final: public PlayerProcessor
    {
    public:
        ProcessorGUIMessageBox()
        {
            BPP_INIT(ID_GUI_MESSAGEBOX)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (isLocal())
            {
                LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "ID_GUI_MESSAGEBOX, Type %d, MSG %s", (int) player->guiMessageBox.type,
                                   player->guiMessageBox.label.c_str());

                switch(player->guiMessageBox.type)
                {
                    case BasePlayer::GUIMessageBox::Type::MessageBox:
                        Main::get().getGUIController()->showMessageBox(player->guiMessageBox);
                        break;
                    case BasePlayer::GUIMessageBox::Type::CustomMessageBox:
                        Main::get().getGUIController()->showCustomMessageBox(player->guiMessageBox);
                        break;
                    case BasePlayer::GUIMessageBox::Type::InputDialog:
                    case BasePlayer::GUIMessageBox::Type::PasswordDialog:
                        Main::get().getGUIController()->showInputBox(player->guiMessageBox);
                        break;
                    case BasePlayer::GUIMessageBox::Type::ListBox:
                        Main::get().getGUIController()->showDialogList(player->guiMessageBox);
                        break;
                }
            }
        }
    };
}


#endif //OPENMW_PROCESSORGUIMESSAGEBOX_HPP
