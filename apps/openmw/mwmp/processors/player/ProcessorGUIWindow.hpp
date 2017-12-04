//
// Created by koncord on 24.11.17.
//

#pragma once

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorGUIWindow : public PlayerProcessor
    {
    public:
        ProcessorGUIWindow()
        {
            BPP_INIT(ID_GUI_WINDOW)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (isLocal())
            {
                LOG_MESSAGE_SIMPLE(Log::LOG_TRACE, "ID_GUI_WINDOW, ID %d", player->guiWindow.id);

                Main::get().getGUIController()->showCustomWindow(player->guiWindow);
            }
        }
    };
}
