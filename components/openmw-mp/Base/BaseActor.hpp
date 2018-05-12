#ifndef OPENMW_BASEACTOR_HPP
#define OPENMW_BASEACTOR_HPP

#include <components/esm/loadcell.hpp>

#include <components/openmw-mp/Base/BaseStructs.hpp>
#include <components/openmw-mp/Base/BaseNetCreature.hpp>

#include <RakNetTypes.h>
#include <memory>

namespace mwmp
{
    class BaseActor : public BaseNetCreature
    {
    public:

        BaseActor()
        {
            hasPositionData = false;
            hasStatsDynamicData = false;
            refNumIndex = 0;
            mpNum = 0;
            drawState = 0;
            isFlying = false;
        }

        enum class AIAction : uint8_t
        {
            Follow = 0
        };

        std::string refId;
        unsigned refNumIndex;
        unsigned mpNum;

        std::string sound;

        Animation animation;

        bool hasAiTarget;
        Target aiTarget;
        AIAction aiAction;

        bool hasPositionData;
        bool hasStatsDynamicData;
    };

    class BaseActorList
    {
    public:

        BaseActorList()
        {
            cell.blank();
        }

        enum class Action: uint8_t
        {
            Set = 0,
            Add,
            Remove,
            Request
        };

        RakNet::RakNetGUID guid;

        std::vector<std::shared_ptr<BaseActor>> baseActors;

        ESM::Cell cell;

        Action action;

        bool isValid;
    };
}

#endif //OPENMW_BASEACTOR_HPP
