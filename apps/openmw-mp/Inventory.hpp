//
// Created by koncord on 12.08.17.
//

#pragma once

#include <string>
#include <tuple>

class LuaState;
class NetActor;

class Inventory
{
public:
    static void Init(LuaState &lua);
    bool isEquipmentChanged();
    void resetEquipmentFlag();
    mwmp::InventoryChanges::Type inventoryChangeType();
    void resetInventoryFlag();
public:
    explicit Inventory(NetActor *netActor);
    ~Inventory();
    void update();

    //inventory
    int getChangesSize() const;
    void addItem(const std::string& refId, unsigned int count, int charge, int enchantmentCharge);
    void removeItem(const std::string& refId, unsigned short count);

    /**
     *
     * @param slot
     * @return refid, count, charge, enchantmentCharge
     */
    std::tuple<std::string,int, int, int> getInventoryItem(unsigned int slot) const;


    // equipment
    void equipItem(unsigned short slot, const std::string& refId, unsigned int count, int charge, int enchantmentCharge);
    void unequipItem(unsigned short slot);

    bool hasItemEquipped(const std::string& refId) const;

    /**
     *
     * @param slot
     * @return refid, count, charge, enchantmentCharge
     */
    std::tuple<std::string,int, int, int> getEquipmentItem(unsigned short slot) const;


private:
    void InitializeInventoryChanges();

private:
    // not controlled pointer
    NetActor *netActor;
    bool equipmentChanged;
    mwmp::InventoryChanges::Type inventoryChanged;
};


