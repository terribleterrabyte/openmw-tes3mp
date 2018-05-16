#ifndef OPENMW_PROCESSORCONTAINER_HPP
#define OPENMW_PROCESSORCONTAINER_HPP

#include "BaseObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorContainer : public BaseObjectProcessor
    {
    public:
        ProcessorContainer()
        {
            BPP_INIT(ID_CONTAINER)
        }

        virtual void Do(ObjectPacket &packet, ObjectList &objectList)
        {
            BaseObjectProcessor::Do(packet, objectList);

            LOG_APPEND(Log::LOG_VERBOSE, "- action: %i, containerSubAction: %i", (int) objectList.action, (int) objectList.containerSubAction);

            // If we've received a request for information, comply with it
            if (objectList.action == mwmp::BaseObjectList::Action::Request)
            {
                if (objectList.baseObjects.size() == 0)
                {
                    LOG_APPEND(Log::LOG_VERBOSE, "- Request had no objects attached, so we are sending all containers in the cell %s",
                        objectList.cell.getDescription().c_str());
                    objectList.reset();
                    objectList.cell = *ptrCellStore->getCell();
                    objectList.action = BaseObjectList::Action::Set;
                    objectList.addAllContainers(ptrCellStore);
                    objectList.sendContainer();
                }
                else
                {
                    LOG_APPEND(Log::LOG_VERBOSE, "- Request was for %i %s", objectList.baseObjects.size(), objectList.baseObjects.size() == 1 ? "object" : "objects");
                    std::vector<BaseObject> requestObjects = objectList.baseObjects;
                    objectList.reset();
                    objectList.cell = *ptrCellStore->getCell();
                    objectList.action = mwmp::BaseObjectList::Action::Set;
                    objectList.addRequestedContainers(ptrCellStore, requestObjects);

                    if (objectList.baseObjects.size() > 0)
                        objectList.sendContainer();
                }
            }
            // Otherwise, edit containers based on the information received
            else
            {
                LOG_APPEND(Log::LOG_VERBOSE, "- Editing container contents to match those of packet");
                objectList.editContainers(ptrCellStore);
            }
        }

    };
}

#endif //OPENMW_PROCESSORCONTAINER_HPP
