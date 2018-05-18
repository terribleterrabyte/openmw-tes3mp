#ifndef OPENMW_BASESTRUCTS_HPP
#define OPENMW_BASESTRUCTS_HPP

#include <components/esm/statstate.hpp>
#include <vector>

#include <RakNetTypes.h>

namespace mwmp
{
    struct Item
    {
        std::string refId;
        int count;
        int charge;
        float enchantmentCharge;

        inline bool operator==(const Item& rhs)
        {
            return refId == rhs.refId && count == rhs.count && charge == rhs.charge && enchantmentCharge == rhs.enchantmentCharge;
        }
    };

    struct InventoryChanges
    {
        enum class Action: int8_t
        {
            None = -1,
            Set = 0,
            Add,
            Remove
        };
        std::vector<std::pair<Item, Action>> items;
    };
    
    struct Target
    {
        bool isPlayer;

        std::string refId;
        int refNumIndex;
        int mpNum;

        RakNet::RakNetGUID guid;
    };

    class Attack
    {
    public:

        Target target;

        enum class Type: uint8_t
        {
            Melee = 0,
            Magic,
            Throwable
        };

        Type type;

        std::string spellId; // id of spell (e.g. "fireball")

        float damage;

        bool success;
        bool block;
        
        bool pressed;
        bool instant;
        bool knockdown;
        bool applyWeaponEnchantment;
        bool applyProjectileEnchantment;

        bool shouldSend;
    };

    struct Animation
    {
        std::string groupname;
        int mode;
        int count;
        bool persist;
    };
}

#endif //OPENMW_BASESTRUCTS_HPP
