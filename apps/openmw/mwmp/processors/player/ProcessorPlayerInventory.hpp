//
// Created by koncord on 16.04.17.
//

#ifndef OPENMW_PROCESSORPLAYERUPDATEINVENTORY_HPP
#define OPENMW_PROCESSORPLAYERUPDATEINVENTORY_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerInventory final: public PlayerProcessor
    {
    public:
        ProcessorPlayerInventory()
        {
            BPP_INIT(ID_PLAYER_INVENTORY)
        }

        virtual void Do(PlayerPacket &packet, BasePlayer *player)
        {
            if (!isLocal()) return;

            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Received ID_PLAYER_INVENTORY about LocalPlayer from server");

            if (isRequest())
                static_cast<LocalPlayer*>(player)->updateInventory(true);
            else
            {
                LocalPlayer &localPlayer = static_cast<LocalPlayer&>(*player);

                for (const auto &item : localPlayer.inventoryChanges.items)
                {
                    if (item.second == InventoryChanges::Action::Add)
                        localPlayer.addItem(item.first);
                    else if (item.second == InventoryChanges::Action::Remove)
                        localPlayer.removeItem(item.first);
                    else // InventoryChanges::SET
                    {
                        // found set flag, clear and reset inventory 
                        localPlayer.setInventory();
                        break;
                    }
                }
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERUPDATEINVENTORY_HPP
