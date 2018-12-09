#include "Items.hpp"

#include <components/misc/stringops.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw/mwworld/inventorystore.hpp>

using namespace mwmp;

extern "C" void ItemFunctions::ClearInventoryChanges(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->inventoryChanges.items.clear();
}

extern "C" int ItemFunctions::GetEquipmentSize() noexcept
{
    return MWWorld::InventoryStore::Slots;
}

extern "C" unsigned int ItemFunctions::GetInventoryChangesSize(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->inventoryChanges.count;
}

extern "C" unsigned int ItemFunctions::GetInventoryChangesAction(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->inventoryChanges.action;
}

extern "C" void ItemFunctions::SetInventoryChangesAction(unsigned short pid, unsigned char action) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    player->inventoryChanges.action = action;
}

extern "C" void ItemFunctions::EquipItem(unsigned short pid, unsigned short slot, const char *refId, unsigned int count,
    int charge, double enchantmentCharge) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->equipmentItems[slot].refId = refId;
    player->equipmentItems[slot].count = count;
    player->equipmentItems[slot].charge = charge;
    player->equipmentItems[slot].enchantmentCharge = enchantmentCharge;

    if (!Utils::vectorContains(player->equipmentIndexChanges, slot))
        player->equipmentIndexChanges.push_back(slot);
}

extern "C" void ItemFunctions::UnequipItem(unsigned short pid, unsigned short slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    ItemFunctions::EquipItem(pid, slot, "", 0, -1, -1);
}

extern "C" void ItemFunctions::AddItemChange(unsigned short pid, const char* refId, unsigned int count, int charge,
    double enchantmentCharge, const char* soul) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    Item item;
    item.refId = refId;
    item.count = count;
    item.charge = charge;
    item.enchantmentCharge = enchantmentCharge;
    item.soul = soul;

    player->inventoryChanges.items.push_back(item);
}

extern "C" bool ItemFunctions::HasItemEquipped(unsigned short pid, const char* refId)
{
    Player *player;
    GET_PLAYER(pid, player, false);

    for (int slot = 0; slot < MWWorld::InventoryStore::Slots; slot++)
        if (Misc::StringUtils::ciEqual(player->equipmentItems[slot].refId, refId))
            return true;
    return false;
}

extern "C" const char *ItemFunctions::GetEquipmentItemRefId(unsigned short pid, unsigned short slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->equipmentItems[slot].refId.c_str();
}

extern "C" int ItemFunctions::GetEquipmentItemCount(unsigned short pid, unsigned short slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->equipmentItems[slot].count;
}

extern "C" int ItemFunctions::GetEquipmentItemCharge(unsigned short pid, unsigned short slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->equipmentItems[slot].charge;
}

extern "C" double ItemFunctions::GetEquipmentItemEnchantmentCharge(unsigned short pid, unsigned short slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->equipmentItems[slot].enchantmentCharge;
}

extern "C" const char *ItemFunctions::GetInventoryItemRefId(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->inventoryChanges.count)
        return "invalid";

    return player->inventoryChanges.items.at(index).refId.c_str();
}

extern "C" int ItemFunctions::GetInventoryItemCount(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->inventoryChanges.items.at(index).count;
}

extern "C" int ItemFunctions::GetInventoryItemCharge(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->inventoryChanges.items.at(index).charge;
}

extern "C" double ItemFunctions::GetInventoryItemEnchantmentCharge(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->inventoryChanges.items.at(index).enchantmentCharge;
}

extern "C" const char *ItemFunctions::GetInventoryItemSoul(unsigned short pid, unsigned int index) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    if (index >= player->inventoryChanges.count)
        return "invalid";

    return player->inventoryChanges.items.at(index).soul.c_str();
}

extern "C" const char *ItemFunctions::GetUsedItemRefId(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->usedItem.refId.c_str();
}

extern "C" int ItemFunctions::GetUsedItemCount(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->usedItem.count;
}

extern "C" int ItemFunctions::GetUsedItemCharge(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->usedItem.charge;
}

extern "C" double ItemFunctions::GetUsedItemEnchantmentCharge(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->usedItem.enchantmentCharge;
}

extern "C" const char *ItemFunctions::GetUsedItemSoul(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->usedItem.soul.c_str();
}

extern "C" void ItemFunctions::SendEquipment(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_EQUIPMENT);
    packet->setPlayer(player);

    packet->Send(false);
    packet->Send(true);

    player->equipmentIndexChanges.clear();
}

extern "C" void ItemFunctions::SendInventoryChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_INVENTORY);
    packet->setPlayer(player);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ItemFunctions::SendItemUse(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_ITEM_USE);
    packet->setPlayer(player);

    packet->Send(false);
}

extern "C" // All methods below are deprecated versions of methods from above

void ItemFunctions::InitializeInventoryChanges(unsigned short pid) noexcept
{
    ClearInventoryChanges(pid);
}

extern "C" void ItemFunctions::AddItem(unsigned short pid, const char* refId, unsigned int count, int charge,
    double enchantmentCharge, const char* soul) noexcept
{
    AddItemChange(pid, refId, count, charge, enchantmentCharge, soul);
}
