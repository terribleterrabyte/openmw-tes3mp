//
// Created by koncord on 12.08.17.
//

#include <components/misc/stringops.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw/mwworld/inventorystore.hpp>

#include "Script/LuaState.hpp"
#include "Networking.hpp"

#include "Inventory.hpp"
#include "NetActor.hpp"
#include <Player.hpp>

using namespace std;

void Inventory::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Inventory>("Inventory",
                                            "getInventoryChangesSize", &Inventory::getChangesSize,
                                            "addItem", &Inventory::addItem,
                                            "removeItem", &Inventory::removeItem,
                                            "getInventoryItem", &Inventory::getInventoryItem,

                                            "equipItem", &Inventory::equipItem,
                                            "unequipItem", &Inventory::unequipItem,
                                            "hasItemEquipped", &Inventory::hasItemEquipped,
                                            "getEquipmentItem", &Inventory::getEquipmentItem


    );
}

Inventory::Inventory(NetActor *actor) : netActor(actor), equipmentChanged(false), inventoryChanged(mwmp::InventoryChanges::Type::None)
{
    printf("Inventory::Inventory()\n");
}

Inventory::~Inventory()
{
    printf("Inventory::~Inventory()\n");
}

void Inventory::update()
{
    printf("Inventory::update()");
    /*if(isEquipmentChanged())
    {
        if (netActor->isPlayer())
        {
            auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_EQUIPMENT);
            packet->setPlayer(dynamic_cast<Player *>(netActor));
            packet->Send(false);
            packet->Send(true);
        }
        else
        {
            auto packet = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_EQUIPMENT);
            packet->setActorList(&actorList);
            packet->Send(actorList.guid);

            if (sendToAll)
                serverCell->sendToLoaded(packet, &actorList);
        }
        resetEquipmentFlag();
    }*/
    /*if (equipmentChanged)
    {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_EQUIPMENT);
        packet->setPlayer(netActor->getNetCreature());
        packet->Send(false);
        packet->Send(true);
    }

    if (inventoryChanged != 0)
    {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_EQUIPMENT);
        packet->setPlayer(netActor->getNetCreature());
        packet->Send(false);
    }

    equipmentChanged = false;
    inventoryChanged = 0;*/
}


void Inventory::InitializeInventoryChanges()
{
    netActor->getNetCreature()->inventoryChanges.items.clear();
    netActor->getNetCreature()->inventoryChanges.action = mwmp::InventoryChanges::Type::Set;
}

int Inventory::getChangesSize() const
{
    return netActor->getNetCreature()->inventoryChanges.items.size();
}

void Inventory::equipItem(unsigned short slot, const std::string& refId, unsigned int count, int charge, double enchantmentCharge)
{
    netActor->getNetCreature()->equipmentItems[slot].refId = refId;
    netActor->getNetCreature()->equipmentItems[slot].count = count;
    netActor->getNetCreature()->equipmentItems[slot].charge = charge;
    netActor->getNetCreature()->equipmentItems[slot].enchantmentCharge = enchantmentCharge;

    if (!Utils::vectorContains(&netActor->getNetCreature()->equipmentIndexChanges, slot))
        netActor->getNetCreature()->equipmentIndexChanges.push_back(slot);

    if(!equipmentChanged && netActor->isPlayer())
        netActor->toPlayer()->addToUpdateQueue();

    equipmentChanged = true;
}

void Inventory::unequipItem( unsigned short slot)
{
    equipItem(slot, "", 0, -1, -1);
}


void Inventory::addItem(const std::string &refId, unsigned int count, int charge, double enchantmentCharge)
{
    if (inventoryChanged == mwmp::InventoryChanges::Type::Remove)
        return;
    if (inventoryChanged == mwmp::InventoryChanges::Type::None)
        InitializeInventoryChanges();

    mwmp::Item item;
    item.refId = refId;
    item.count = count;
    item.charge = charge;
    item.enchantmentCharge = enchantmentCharge;

    netActor->getNetCreature()->inventoryChanges.items.push_back(item);
    netActor->getNetCreature()->inventoryChanges.action = mwmp::InventoryChanges::Type::Add;
    if (inventoryChanged == mwmp::InventoryChanges::Type::None && netActor->isPlayer())
        netActor->toPlayer()->addToUpdateQueue();
    inventoryChanged = netActor->getNetCreature()->inventoryChanges.action;
}

void Inventory::removeItem(const std::string &refId, unsigned short count)
{
    if (inventoryChanged == mwmp::InventoryChanges::Type::Add)
        return;
    if (inventoryChanged == mwmp::InventoryChanges::Type::None)
        InitializeInventoryChanges();

    mwmp::Item item;
    item.refId = refId;
    item.count = count;

    netActor->getNetCreature()->inventoryChanges.items.push_back(item);
    netActor->getNetCreature()->inventoryChanges.action = mwmp::InventoryChanges::Type::Remove;
    if (inventoryChanged == mwmp::InventoryChanges::Type::None && netActor->isPlayer())
        netActor->toPlayer()->addToUpdateQueue();
    inventoryChanged = netActor->getNetCreature()->inventoryChanges.action;
}

bool Inventory::hasItemEquipped(const std::string &refId) const
{
    for (const auto &equipmentItem : netActor->getNetCreature()->equipmentItems)
        if (Misc::StringUtils::ciEqual(equipmentItem.refId, refId))
            return true;
    return false;
}

std::tuple<std::string, int, int, double> Inventory::getEquipmentItem(unsigned short slot) const
{
    const auto &item = netActor->getNetCreature()->equipmentItems[slot];
    return make_tuple(item.refId, item.count, item.charge, item.enchantmentCharge);
}

std::tuple<std::string, int, int, double> Inventory::getInventoryItem(unsigned int slot) const
{
    const auto &item = netActor->getNetCreature()->inventoryChanges.items.at(slot);
    return make_tuple(item.refId, item.count, item.charge, item.enchantmentCharge);
}

void Inventory::resetEquipmentFlag()
{
    equipmentChanged = false;

    netActor->getNetCreature()->equipmentIndexChanges.clear();
}

bool Inventory::isEquipmentChanged()
{
    return equipmentChanged;
}

void Inventory::resetInventoryFlag()
{
    inventoryChanged = mwmp::InventoryChanges::Type::None;
}

mwmp::InventoryChanges::Type Inventory::inventoryChangeType()
{
    return inventoryChanged;
}



