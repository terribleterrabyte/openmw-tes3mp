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

                if (localPlayer.inventoryChanges.action == InventoryChanges::Type::Add)
                    localPlayer.addItems();
                else if (localPlayer.inventoryChanges.action == InventoryChanges::Type::Remove)
                    localPlayer.removeItems();
                else // InventoryChanges::SET
                    localPlayer.setInventory();
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERUPDATEINVENTORY_HPP
