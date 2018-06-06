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
        float enchantmentCharge;

        int actionCount;

        inline bool operator==(const ContainerItem& rhs)
        {
            return refId == rhs.refId && count == rhs.count && charge == rhs.charge && enchantmentCharge == rhs.enchantmentCharge;
        }
    };

    struct BaseObject
    {
        std::string refId;
        unsigned refNumIndex;
        unsigned mpNum;
        int count;
        int charge;
        float enchantmentCharge;
        int goldValue;

        ESM::Position position;

        bool objectState;
        int lockLevel;
        float scale;

        int doorState;
        bool teleportState;
        ESM::Cell destinationCell;
        ESM::Position destinationPosition;

        std::string filename;
        bool allowSkipping;

        std::string animGroup;
        int animMode;

        int index;
        int shortVal;
        float floatVal;
        std::string varName;

        bool isDisarmed;
        bool droppedByPlayer;

        Target master;
        bool hasMaster;

        std::vector<ContainerItem> containerItems;
        unsigned int containerItemCount;

        RakNet::RakNetGUID guid; // only for object lists that can also include players
        bool isPlayer;
    };

    class BaseObjectList
    {
    public:

        BaseObjectList(RakNet::RakNetGUID guid) : guid(guid)
        {

        }

        BaseObjectList()
        {

        }

        enum class Action : uint8_t
        {
            Set = 0,
            Add,
            Remove,
            Request
        };

        enum class ContainerSubAction : uint8_t
        {
            None = 0,
            Drag,
            Drop,
            TakeAll,
            ReplyToRequest
        };

        RakNet::RakNetGUID guid;
        
        std::vector<BaseObject> baseObjects;

        ESM::Cell cell;
        std::string consoleCommand;

        Action action;
        ContainerSubAction containerSubAction;

        bool isValid;
    };
}

#endif //OPENMW_BASEEVENT_HPP
