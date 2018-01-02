#ifndef OPENMW_BASEEVENT_HPP
#define OPENMW_BASEEVENT_HPP

#include <components/esm/loadcell.hpp>
#include <components/openmw-mp/Base/BaseStructs.hpp>
#include <RakNetTypes.h>

namespace mwmp
{
    struct ContainerItem
    {
        std::string refId;
        int count;
        int charge;
        int enchantmentCharge;

        int actionCount;

        inline bool operator==(const ContainerItem& rhs)
        {
            return refId == rhs.refId && count == rhs.count && charge == rhs.charge && enchantmentCharge == rhs.enchantmentCharge;
        }
    };

    struct WorldObject
    {
        std::string refId;
        unsigned refNumIndex;
        unsigned mpNum;
        int count;
        int charge;
        int enchantmentCharge;
        int goldValue;

        ESM::Position position;

        bool objectState;
        int doorState;
        int lockLevel;
        float scale;

        std::string filename;
        bool allowSkipping;

        std::string animGroup;
        int animMode;

        int index;
        int shortVal;
        float floatVal;
        std::string varName;

        bool isDisarmed;

        Target master;
        bool hasMaster;

        std::vector<ContainerItem> containerItems;
        unsigned int containerItemCount;

        RakNet::RakNetGUID guid; // only for events that can also affect players
        bool isPlayer;
    };

    class BaseEvent
    {
    public:

        BaseEvent(RakNet::RakNetGUID guid) : guid(guid)
        {

        }

        BaseEvent()
        {

        }

        enum class Action : uint8_t
        {
            Set = 0,
            Add,
            Remove,
            Request
        };

        RakNet::RakNetGUID guid;
        
        std::vector<WorldObject> worldObjects;

        ESM::Cell cell;
        std::string consoleCommand;

        Action action;

        bool isValid;
    };
}

#endif //OPENMW_BASEEVENT_HPP
