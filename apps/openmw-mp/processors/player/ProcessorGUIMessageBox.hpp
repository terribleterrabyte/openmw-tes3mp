//
// Created by koncord on 01.04.17.
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

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            player->getGUI().onGUIAction();
        }
    };
}

#endif //OPENMW_PROCESSORGUIMESSAGEBOX_HPP
