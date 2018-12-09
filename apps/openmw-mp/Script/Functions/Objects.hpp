#ifndef OPENMW_OBJECTAPI_HPP
#define OPENMW_OBJECTAPI_HPP

#define OBJECTAPI \
    {"ReadReceivedObjectList",                ObjectFunctions::ReadReceivedObjectList},\
    \
    {"ClearObjectList",                       ObjectFunctions::ClearObjectList},\
    {"SetObjectListPid",                      ObjectFunctions::SetObjectListPid},\
    \
    {"CopyReceivedObjectListToStore",         ObjectFunctions::CopyReceivedObjectListToStore},\
    \
    {"GetObjectListSize",                     ObjectFunctions::GetObjectListSize},\
    {"GetObjectListOrigin",                   ObjectFunctions::GetObjectListOrigin},\
    {"GetObjectListClientScript",             ObjectFunctions::GetObjectListClientScript},\
    {"GetObjectListAction",                   ObjectFunctions::GetObjectListAction},\
    {"GetObjectListContainerSubAction",       ObjectFunctions::GetObjectListContainerSubAction},\
    \
    {"IsObjectPlayer",                        ObjectFunctions::IsObjectPlayer},\
    {"GetObjectPid",                          ObjectFunctions::GetObjectPid},\
    {"GetObjectRefId",                        ObjectFunctions::GetObjectRefId},\
    {"GetObjectRefNum",                       ObjectFunctions::GetObjectRefNum},\
    {"GetObjectMpNum",                        ObjectFunctions::GetObjectMpNum},\
    {"GetObjectCount",                        ObjectFunctions::GetObjectCount},\
    {"GetObjectCharge",                       ObjectFunctions::GetObjectCharge},\
    {"GetObjectEnchantmentCharge",            ObjectFunctions::GetObjectEnchantmentCharge},\
    {"GetObjectSoul" ,                        ObjectFunctions::GetObjectSoul},\
    {"GetObjectGoldValue",                    ObjectFunctions::GetObjectGoldValue},\
    {"GetObjectScale",                        ObjectFunctions::GetObjectScale},\
    {"GetObjectState",                        ObjectFunctions::GetObjectState},\
    {"GetObjectDoorState",                    ObjectFunctions::GetObjectDoorState},\
    {"GetObjectLockLevel",                    ObjectFunctions::GetObjectLockLevel},\
    \
    {"DoesObjectHavePlayerActivating",        ObjectFunctions::DoesObjectHavePlayerActivating},\
    {"GetObjectActivatingPid",                ObjectFunctions::GetObjectActivatingPid},\
    {"GetObjectActivatingRefId",              ObjectFunctions::GetObjectActivatingRefId},\
    {"GetObjectActivatingRefNum",             ObjectFunctions::GetObjectActivatingRefNum},\
    {"GetObjectActivatingMpNum",              ObjectFunctions::GetObjectActivatingMpNum},\
    {"GetObjectActivatingName",               ObjectFunctions::GetObjectActivatingName},\
    \
    {"GetObjectSummonState",                  ObjectFunctions::GetObjectSummonState},\
    {"GetObjectSummonDuration",               ObjectFunctions::GetObjectSummonDuration},\
    {"DoesObjectHavePlayerSummoner",          ObjectFunctions::DoesObjectHavePlayerSummoner},\
    {"GetObjectSummonerPid",                  ObjectFunctions::GetObjectSummonerPid},\
    {"GetObjectSummonerRefId",                ObjectFunctions::GetObjectSummonerRefId},\
    {"GetObjectSummonerRefNum",               ObjectFunctions::GetObjectSummonerRefNum},\
    {"GetObjectSummonerMpNum",                ObjectFunctions::GetObjectSummonerMpNum},\
    \
    {"GetObjectPosX",                         ObjectFunctions::GetObjectPosX},\
    {"GetObjectPosY",                         ObjectFunctions::GetObjectPosY},\
    {"GetObjectPosZ",                         ObjectFunctions::GetObjectPosZ},\
    {"GetObjectRotX",                         ObjectFunctions::GetObjectRotX},\
    {"GetObjectRotY",                         ObjectFunctions::GetObjectRotY},\
    {"GetObjectRotZ",                         ObjectFunctions::GetObjectRotZ},\
    \
    {"GetVideoFilename",                      ObjectFunctions::GetVideoFilename},\
    \
    {"GetContainerChangesSize",               ObjectFunctions::GetContainerChangesSize},\
    {"GetContainerItemRefId",                 ObjectFunctions::GetContainerItemRefId},\
    {"GetContainerItemCount",                 ObjectFunctions::GetContainerItemCount},\
    {"GetContainerItemCharge",                ObjectFunctions::GetContainerItemCharge},\
    {"GetContainerItemEnchantmentCharge",     ObjectFunctions::GetContainerItemEnchantmentCharge},\
    {"GetContainerItemSoul",                  ObjectFunctions::GetContainerItemSoul},\
    {"GetContainerItemActionCount",           ObjectFunctions::GetContainerItemActionCount},\
    \
    {"DoesObjectHaveContainer",               ObjectFunctions::DoesObjectHaveContainer},\
    \
    {"SetObjectListCell",                     ObjectFunctions::SetObjectListCell},\
    {"SetObjectListAction",                   ObjectFunctions::SetObjectListAction},\
    {"SetObjectListConsoleCommand",           ObjectFunctions::SetObjectListConsoleCommand},\
    \
    {"SetObjectRefId",                        ObjectFunctions::SetObjectRefId},\
    {"SetObjectRefNum",                       ObjectFunctions::SetObjectRefNum},\
    {"SetObjectMpNum",                        ObjectFunctions::SetObjectMpNum},\
    {"SetObjectCount",                        ObjectFunctions::SetObjectCount},\
    {"SetObjectCharge",                       ObjectFunctions::SetObjectCharge},\
    {"SetObjectEnchantmentCharge",            ObjectFunctions::SetObjectEnchantmentCharge},\
    {"SetObjectSoul",                         ObjectFunctions::SetObjectSoul},\
    {"SetObjectGoldValue",                    ObjectFunctions::SetObjectGoldValue},\
    {"SetObjectScale",                        ObjectFunctions::SetObjectScale},\
    {"SetObjectState",                        ObjectFunctions::SetObjectState},\
    {"SetObjectLockLevel",                    ObjectFunctions::SetObjectLockLevel},\
    {"SetObjectDisarmState",                  ObjectFunctions::SetObjectDisarmState},\
    {"SetObjectSummonDuration",               ObjectFunctions::SetObjectSummonDuration},\
    {"SetObjectSummonState",                  ObjectFunctions::SetObjectSummonState},\
    {"SetObjectPosition",                     ObjectFunctions::SetObjectPosition},\
    {"SetObjectRotation",                     ObjectFunctions::SetObjectRotation},\
    \
    {"SetObjectActivatingPid",                ObjectFunctions::SetObjectActivatingPid},\
    \
    {"SetObjectDoorState",                    ObjectFunctions::SetObjectDoorState},\
    {"SetObjectDoorTeleportState",            ObjectFunctions::SetObjectDoorTeleportState},\
    {"SetObjectDoorDestinationCell",          ObjectFunctions::SetObjectDoorDestinationCell},\
    {"SetObjectDoorDestinationPosition",      ObjectFunctions::SetObjectDoorDestinationPosition},\
    {"SetObjectDoorDestinationRotation",      ObjectFunctions::SetObjectDoorDestinationRotation},\
    \
    {"SetPlayerAsObject",                     ObjectFunctions::SetPlayerAsObject},\
    \
    {"SetContainerItemRefId",                 ObjectFunctions::SetContainerItemRefId},\
    {"SetContainerItemCount",                 ObjectFunctions::SetContainerItemCount},\
    {"SetContainerItemCharge",                ObjectFunctions::SetContainerItemCharge},\
    {"SetContainerItemEnchantmentCharge",     ObjectFunctions::SetContainerItemEnchantmentCharge},\
    {"SetContainerItemSoul",                  ObjectFunctions::SetContainerItemSoul},\
    \
    {"SetContainerItemActionCountByIndex",    ObjectFunctions::SetContainerItemActionCountByIndex},\
    \
    {"AddObject",                             ObjectFunctions::AddObject},\
    {"AddContainerItem",                      ObjectFunctions::AddContainerItem},\
    \
    {"SendObjectActivate",                    ObjectFunctions::SendObjectActivate},\
    {"SendObjectPlace",                       ObjectFunctions::SendObjectPlace},\
    {"SendObjectSpawn",                       ObjectFunctions::SendObjectSpawn},\
    {"SendObjectDelete",                      ObjectFunctions::SendObjectDelete},\
    {"SendObjectLock",                        ObjectFunctions::SendObjectLock},\
    {"SendObjectTrap",                        ObjectFunctions::SendObjectTrap},\
    {"SendObjectScale",                       ObjectFunctions::SendObjectScale},\
    {"SendObjectState",                       ObjectFunctions::SendObjectState},\
    {"SendDoorState",                         ObjectFunctions::SendDoorState},\
    {"SendDoorDestination",                   ObjectFunctions::SendDoorDestination},\
    {"SendContainer",                         ObjectFunctions::SendContainer},\
    {"SendVideoPlay",                         ObjectFunctions::SendVideoPlay},\
    {"SendConsoleCommand",                    ObjectFunctions::SendConsoleCommand},\
    \
    {"ReadLastObjectList",                    ObjectFunctions::ReadLastObjectList},\
    {"ReadLastEvent",                         ObjectFunctions::ReadLastEvent},\
    {"InitializeObjectList",                  ObjectFunctions::InitializeObjectList},\
    {"InitializeEvent",                       ObjectFunctions::InitializeEvent},\
    {"CopyLastObjectListToStore",             ObjectFunctions::CopyLastObjectListToStore},\
    {"GetObjectChangesSize",                  ObjectFunctions::GetObjectChangesSize},\
    {"GetEventAction",                        ObjectFunctions::GetEventAction},\
    {"GetEventContainerSubAction",            ObjectFunctions::GetEventContainerSubAction},\
    {"GetObjectRefNumIndex",                  ObjectFunctions::GetObjectRefNumIndex},\
    {"GetObjectSummonerRefNumIndex",          ObjectFunctions::GetObjectSummonerRefNumIndex},\
    {"SetEventCell",                          ObjectFunctions::SetEventCell},\
    {"SetEventAction",                        ObjectFunctions::SetEventAction},\
    {"SetEventConsoleCommand",                ObjectFunctions::SetEventConsoleCommand},\
    {"SetObjectRefNumIndex",                  ObjectFunctions::SetObjectRefNumIndex},\
    {"AddWorldObject",                        ObjectFunctions::AddWorldObject}

namespace ObjectFunctions
{
    /**
    * \brief Use the last object list received by the server as the one being read.
    *
    * \return void
    */
    extern "C" void ReadReceivedObjectList() noexcept;

    /**
    * \brief Clear the data from the object list stored on the server.
    *
    * \return void
    */
    extern "C" void ClearObjectList() noexcept;

    /**
    * \brief Set the pid attached to the ObjectList.
    *
    * \param pid The player ID to whom the object list should be attached.
    * \return void
    */
    extern "C" void SetObjectListPid(unsigned short pid) noexcept;

    /**
    * \brief Take the contents of the read-only object list last received by the
    *        server from a player and move its contents to the stored object list
    *        that can be sent by the server.
    *
    * \return void
    */
    extern "C" void CopyReceivedObjectListToStore() noexcept;

    /**
    * \brief Get the number of indexes in the read object list.
    *
    * \return The number of indexes.
    */
    extern "C" unsigned int GetObjectListSize() noexcept;

    /**
    * \brief Get the origin of the read object list.
    *
    * \return The origin (0 for CLIENT_GAMEPLAY, 1 for CLIENT_CONSOLE, 2 for
    * CLIENT_DIALOGUE, 3 for CLIENT_SCRIPT_LOCAL, 4 for CLIENT_SCRIPT_GLOBAL,
    * 5 for SERVER_SCRIPT).
    */
    extern "C" unsigned char GetObjectListOrigin() noexcept;

    /**
    * \brief Get the client script that the read object list originated from.
    *
    * Note: This is not yet implemented.
    *
    * \return The ID of the client script.
    */
    extern "C" const char *GetObjectListClientScript() noexcept;

    /**
    * \brief Get the action type used in the read object list.
    *
    * \return The action type (0 for SET, 1 for ADD, 2 for REMOVE, 3 for REQUEST).
    */
    extern "C" unsigned char GetObjectListAction() noexcept;

    /**
    * \brief Get the container subaction type used in the read object list.
    *
    * \return The action type (0 for NONE, 1 for DRAG, 2 for DROP, 3 for TAKE_ALL).
    */
    extern "C" unsigned char GetObjectListContainerSubAction() noexcept;

    /**
    * \brief Check whether the object at a certain index in the read object list is a
    * player.
    *
    * Note: Although most player data and events are dealt with in Player packets,
    *       object activation is general enough for players themselves to be included
    *       as objects in ObjectActivate packets.
    *
    * \param index The index of the object.
    * \return Whether the object is a player.
    */
    extern "C" bool IsObjectPlayer(unsigned int index) noexcept;

    /**
    * \brief Get the player ID of the object at a certain index in the read object list,
    * only valid if the object is a player.
    *
    * Note: Currently, players can only be objects in ObjectActivate and ConsoleCommand
    *       packets.
    *
    * \param index The index of the object.
    * \return The player ID of the object.
    */
    extern "C" int GetObjectPid(unsigned int index) noexcept;

    /**
    * \brief Get the refId of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The refId.
    */
    extern "C" const char *GetObjectRefId(unsigned int index) noexcept;

    /**
    * \brief Get the refNum of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The refNum.
    */
    extern "C" unsigned int GetObjectRefNum(unsigned int index) noexcept;

    /**
    * \brief Get the mpNum of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The mpNum.
    */
    extern "C" unsigned int GetObjectMpNum(unsigned int index) noexcept;

    /**
    * \brief Get the count of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The object count.
    */
    extern "C" int GetObjectCount(unsigned int index) noexcept;

    /**
    * \brief Get the charge of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The charge.
    */
    extern "C" int GetObjectCharge(unsigned int index) noexcept;

    /**
    * \brief Get the enchantment charge of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The enchantment charge.
    */
    extern "C" double GetObjectEnchantmentCharge(unsigned int index) noexcept;

    /**
    * \brief Get the soul of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The soul.
    */
    extern "C" const char *GetObjectSoul(unsigned int index) noexcept;

    /**
    * \brief Get the gold value of the object at a certain index in the read object list.
    *
    * This is used solely to get the gold value of gold. It is not used for other objects.
    *
    * \param index The index of the object.
    * \return The gold value.
    */
    extern "C" int GetObjectGoldValue(unsigned int index) noexcept;

    /**
    * \brief Get the object scale of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The object scale.
    */
    extern "C" double GetObjectScale(unsigned int index) noexcept;

    /**
    * \brief Get the object state of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The object state.
    */
    extern "C" bool GetObjectState(unsigned int index) noexcept;

    /**
    * \brief Get the door state of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The door state.
    */
    extern "C" int GetObjectDoorState(unsigned int index) noexcept;

    /**
    * \brief Get the lock level of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The lock level.
    */
    extern "C" int GetObjectLockLevel(unsigned int index) noexcept;

    /**
    * \brief Check whether the object at a certain index in the read object list has been
    * activated by a player.
    *
    * \param index The index of the object.
    * \return Whether the object has been activated by a player.
    */
    extern "C" bool DoesObjectHavePlayerActivating(unsigned int index) noexcept;

    /**
    * \brief Get the player ID of the player activating the object at a certain index in the
    * read object list.
    *
    * \param index The index of the object.
    * \return The player ID of the activating player.
    */
    extern "C" int GetObjectActivatingPid(unsigned int index) noexcept;

    /**
    * \brief Get the refId of the actor activating the object at a certain index in the read
    * object list.
    *
    * \param index The index of the object.
    * \return The refId of the activating actor.
    */
    extern "C" const char *GetObjectActivatingRefId(unsigned int index) noexcept;

    /**
    * \brief Get the refNum of the actor activating the object at a certain index in the read
    * object list.
    *
    * \param index The index of the object.
    * \return The refNum of the activating actor.
    */
    extern "C" unsigned int GetObjectActivatingRefNum(unsigned int index) noexcept;

    /**
    * \brief Get the mpNum of the actor activating the object at a certain index in the read
    * object list.
    *
    * \param index The index of the object.
    * \return The mpNum of the activating actor.
    */
    extern "C" unsigned int GetObjectActivatingMpNum(unsigned int index) noexcept;

    /**
    * \brief Get the name of the actor activating the object at a certain index in the read
    * object list.
    *
    * \param index The index of the object.
    * \return The name of the activating actor.
    */
    extern "C" const char *GetObjectActivatingName(unsigned int index) noexcept;

    /**
    * \brief Check whether the object at a certain index in the read object list is a
    * summon.
    *
    * Only living actors can be summoned.
    *
    * \return The summon state.
    */
    extern "C" bool GetObjectSummonState(unsigned int index) noexcept;

    /**
    * \brief Get the summon duration of the object at a certain index in the read object list.
    *
    * Note: Returns -1 if indefinite.
    *
    * \param index The index of the object.
    * \return The summon duration.
    */
    extern "C" double GetObjectSummonDuration(unsigned int index) noexcept;

    /**
    * \brief Check whether the object at a certain index in the read object list has a player
    * as its summoner.
    *
    * Only living actors can be summoned.
    *
    * \param index The index of the object.
    * \return Whether a player is the summoner of the object.
    */
    extern "C" bool DoesObjectHavePlayerSummoner(unsigned int index) noexcept;

    /**
    * \brief Get the player ID of the summoner of the object at a certain index in the read object
    * list.
    *
    * \param index The index of the object.
    * \return The player ID of the summoner.
    */
    extern "C" int GetObjectSummonerPid(unsigned int index) noexcept;

    /**
    * \brief Get the refId of the actor summoner of the object at a certain index in the read object
    * list.
    *
    * \param index The index of the object.
    * \return The refId of the summoner.
    */
    extern "C" const char *GetObjectSummonerRefId(unsigned int index) noexcept;

    /**
    * \brief Get the refNum of the actor summoner of the object at a certain index in the read object
    * list.
    *
    * \param index The index of the object.
    * \return The refNum of the summoner.
    */
    extern "C" unsigned int GetObjectSummonerRefNum(unsigned int index) noexcept;

    /**
    * \brief Get the mpNum of the actor summoner of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The mpNum of the summoner.
    */
    extern "C" unsigned int GetObjectSummonerMpNum(unsigned int index) noexcept;

    /**
    * \brief Get the X position of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The X position.
    */
    extern "C" double GetObjectPosX(unsigned int index) noexcept;

    /**
    * \brief Get the Y position of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The Y position.
    */
    extern "C" double GetObjectPosY(unsigned int index) noexcept;

    /**
    * \brief Get the Z position at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The Z position.
    */
    extern "C" double GetObjectPosZ(unsigned int index) noexcept;

    /**
    * \brief Get the X rotation of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The X rotation.
    */
    extern "C" double GetObjectRotX(unsigned int index) noexcept;

    /**
    * \brief Get the Y rotation of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The Y rotation.
    */
    extern "C" double GetObjectRotY(unsigned int index) noexcept;

    /**
    * \brief Get the Z rotation of the object at a certain index in the read object list.
    *
    * \param index The index of the object.
    * \return The Z rotation.
    */
    extern "C" double GetObjectRotZ(unsigned int index) noexcept;

    /**
    * \brief Get the videoFilename of the object at a certain index in the read object list.
    *
    * \return The videoFilename.
    */
    extern "C" const char *GetVideoFilename(unsigned int index) noexcept;

    /**
    * \brief Get the number of container item indexes of the object at a certain index in the
    * read object list.
    *
    * \param index The index of the object.
    * \return The number of container item indexes.
    */
    extern "C" unsigned int GetContainerChangesSize(unsigned int objectIndex) noexcept;

    /**
    * \brief Get the refId of the container item at a certain itemIndex in the container changes
    * of the object at a certain objectIndex in the read object list.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \return The refId.
    */
    extern "C" const char *GetContainerItemRefId(unsigned int objectIndex, unsigned int itemIndex) noexcept;

    /**
    * \brief Get the item count of the container item at a certain itemIndex in the container
    * changes of the object at a certain objectIndex in the read object list.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \return The item count.
    */
    extern "C" int GetContainerItemCount(unsigned int objectIndex, unsigned int itemIndex) noexcept;

    /**
    * \brief Get the charge of the container item at a certain itemIndex in the container changes
    * of the object at a certain objectIndex in the read object list.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \return The charge.
    */
    extern "C" int GetContainerItemCharge(unsigned int objectIndex, unsigned int itemIndex) noexcept;

    /**
    * \brief Get the enchantment charge of the container item at a certain itemIndex in the container changes
    * of the object at a certain objectIndex in the read object list.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \return The enchantment charge.
    */
    extern "C" double GetContainerItemEnchantmentCharge(unsigned int objectIndex, unsigned int itemIndex) noexcept;

    /**
    * \brief Get the soul of the container item at a certain itemIndex in the container changes
    * of the object at a certain objectIndex in the read object list.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \return The soul.
    */
    extern "C" const char *GetContainerItemSoul(unsigned int objectIndex, unsigned int itemIndex) noexcept;

    /**
    * \brief Get the action count of the container item at a certain itemIndex in the container
    * changes of the object at a certain objectIndex in the read object list.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \return The action count.
    */
    extern "C" int GetContainerItemActionCount(unsigned int objectIndex, unsigned int itemIndex) noexcept;

    /**
    * \brief Check whether the object at a certain index in the read object list has a container.
    * 
    * Note: Only ObjectLists from ObjectPlace packets contain this information. Objects from
    *       received ObjectSpawn packets can always be assumed to have a container.
    *
    * \param index The index of the object.
    * \return Whether the object has a container.
    */
    extern "C" bool DoesObjectHaveContainer(unsigned int index) noexcept;

    /**
    * \brief Set the cell of the temporary object list stored on the server.
    *
    * The cell is determined to be an exterior cell if it fits the pattern of a number followed
    * by a comma followed by another number.
    *
    * \param cellDescription The description of the cell.
    * \return void
    */
    extern "C" void SetObjectListCell(const char* cellDescription) noexcept;

    /**
    * \brief Set the action type of the temporary object list stored on the server.
    *
    * \param action The action type (0 for SET, 1 for ADD, 2 for REMOVE, 3 for REQUEST).
    * \return void
    */
    extern "C" void SetObjectListAction(unsigned char action) noexcept;

    /**
    * \brief Set the console command of the temporary object list stored on the server.
    *
    * When sent, the command will run once on every object added to the object list. If no objects
    * have been added, it will run once without any object reference.
    *
    * \param consoleCommand The console command.
    * \return void
    */
    extern "C" void SetObjectListConsoleCommand(const char* consoleCommand) noexcept;

    /**
    * \brief Set the refId of the temporary object stored on the server.
    *
    * \param refId The refId.
    * \return void
    */
    extern "C" void SetObjectRefId(const char* refId) noexcept;

    /**
    * \brief Set the refNum of the temporary object stored on the server.
    *
    * Every object loaded from .ESM and .ESP data files has a unique refNum which needs to be
    * retained to refer to it in packets.
    * 
    * On the other hand, objects placed or spawned via the server should always have a refNum
    * of 0.
    *
    * \param refNum The refNum.
    * \return void
    */
    extern "C" void SetObjectRefNum(int refNum) noexcept;

    /**
    * \brief Set the mpNum of the temporary object stored on the server.
    *
    * Every object placed or spawned via the server is assigned an mpNum by incrementing the last
    * mpNum stored on the server. Scripts should take care to ensure that mpNums are kept unique
    * for these objects.
    * 
    * Objects loaded from .ESM and .ESP data files should always have an mpNum of 0, because they
    * have unique refNumes instead.
    *
    * \param mpNum The mpNum.
    * \return void
    */
    extern "C" void SetObjectMpNum(int mpNum) noexcept;

    /**
    * \brief Set the object count of the temporary object stored on the server.
    *
    * This determines the quantity of an object, with the exception of gold.
    *
    * \param count The object count.
    * \return void
    */
    extern "C" void SetObjectCount(int count) noexcept;

    /**
    * \brief Set the charge of the temporary object stored on the server.
    *
    * Object durabilities are set through this value.
    *
    * \param charge The charge.
    * \return void
    */
    extern "C" void SetObjectCharge(int charge) noexcept;

    /**
    * \brief Set the enchantment charge of the temporary object stored on the server.
    *
    * Object durabilities are set through this value.
    *
    * \param charge The enchantment charge.
    * \return void
    */
    extern "C" void SetObjectEnchantmentCharge(double enchantmentCharge) noexcept;

    /**
    * \brief Set the soul of the temporary object stored on the server.
    *
    * \param refId The soul.
    * \return void
    */
    extern "C" void SetObjectSoul(const char* soul) noexcept;

    /**
    * \brief Set the gold value of the temporary object stored on the server.
    *
    * This is used solely to set the gold value for gold. It has no effect on other objects.
    *
    * \param goldValue The gold value.
    * \return void
    */
    extern "C" void SetObjectGoldValue(int goldValue) noexcept;

    /**
    * \brief Set the scale of the temporary object stored on the server.
    *
    * Objects are smaller or larger than their default size based on their scale.
    *
    * \param scale The scale.
    * \return void
    */
    extern "C" void SetObjectScale(double scale) noexcept;

    /**
    * \brief Set the object state of the temporary object stored on the server.
    *
    * Objects are enabled or disabled based on their object state.
    *
    * \param objectState The object state.
    * \return void
    */
    extern "C" void SetObjectState(bool objectState) noexcept;

    /**
    * \brief Set the lock level of the temporary object stored on the server.
    *
    * \param lockLevel The lock level.
    * \return void
    */
    extern "C" void SetObjectLockLevel(int lockLevel) noexcept;

    /**
    * \brief Set the summon duration of the temporary object stored on the server.
    *
    * \param summonDuration The summon duration.
    * \return void
    */
    extern "C" void SetObjectSummonDuration(float summonDuration) noexcept;

    /**
    * \brief Set the disarm state of the temporary object stored on the server.
    *
    * \param disarmState The disarmState.
    * \return void
    */
    extern "C" void SetObjectDisarmState(bool disarmState) noexcept;

    /**
    * \brief Set the summon state of the temporary object stored on the server.
    *
    * This only affects living actors and determines whether they are summons of another
    * living actor.
    *
    * \param summonState The summon state.
    * \return void
    */
    extern "C" void SetObjectSummonState(bool summonState) noexcept;

    /**
    * \brief Set the position of the temporary object stored on the server.
    *
    * \param x The X position.
    * \param y The Y position.
    * \param z The Z position.
    * \return void
    */
    extern "C" void SetObjectPosition(double x, double y, double z) noexcept;

    /**
    * \brief Set the rotation of the temporary object stored on the server.
    *
    * \param x The X rotation.
    * \param y The Y rotation.
    * \param z The Z rotation.
    * \return void
    */
    extern "C" void SetObjectRotation(double x, double y, double z) noexcept;

    /**
    * \brief Set the player ID of the player activating the temporary object stored on the
    *        server. Currently only used for ObjectActivate packets.
    *
    * \param pid The pid of the player.
    * \return void
    */
    extern "C" void SetObjectActivatingPid(unsigned short pid) noexcept;

    /**
    * \brief Set the door state of the temporary object stored on the server.
    *
    * Doors are open or closed based on their door state.
    *
    * \param doorState The door state.
    * \return void
    */
    extern "C" void SetObjectDoorState(int doorState) noexcept;

    /**
    * \brief Set the teleport state of the temporary object stored on the server.
    *
    * If a door's teleport state is true, interacting with the door teleports a player to its
    * destination. If it's false, it opens and closes like a regular door.
    *
    * \param teleportState The teleport state.
    * \return void
    */
    extern "C" void SetObjectDoorTeleportState(bool teleportState) noexcept;

    /**
    * \brief Set the door destination cell of the temporary object stored on the server.
    *
    * The cell is determined to be an exterior cell if it fits the pattern of a number followed
    * by a comma followed by another number.
    *
    * \param cellDescription The description of the cell.
    * \return void
    */
    extern "C" void SetObjectDoorDestinationCell(const char* cellDescription) noexcept;

    /**
    * \brief Set the door destination position of the temporary object stored on the server.
    *
    * \param x The X position.
    * \param y The Y position.
    * \param z The Z position.
    * \return void
    */
    extern "C" void SetObjectDoorDestinationPosition(double x, double y, double z) noexcept;

    /**
    * \brief Set the door destination rotation of the temporary object stored on the server.
    *
    * Note: Because this sets the rotation a player will have upon using the door, and rotation
    *       on the Y axis has no effect on players, the Y value has been omitted as an argument.
    *
    * \param x The X rotation.
    * \param z The Z rotation.
    * \return void
    */
    extern "C" void SetObjectDoorDestinationRotation(double x, double z) noexcept;

    /**
    * \brief Set a player as the object in the temporary object stored on the server.
    *        Currently only used for ConsoleCommand packets.
    *
    * \param pid The pid of the player.
    * \return void
    */
    extern "C" void SetPlayerAsObject(unsigned short pid) noexcept;

    /**
    * \brief Set the refId of the temporary container item stored on the server.
    *
    * \param refId The refId.
    * \return void
    */
    extern "C" void SetContainerItemRefId(const char* refId) noexcept;

    /**
    * \brief Set the item count of the temporary container item stored on the server.
    *
    * \param count The item count.
    * \return void
    */
    extern "C" void SetContainerItemCount(int count) noexcept;

    /**
    * \brief Set the charge of the temporary container item stored on the server.
    *
    * \param charge The charge.
    * \return void
    */
    extern "C" void SetContainerItemCharge(int charge) noexcept;

    /**
    * \brief Set the enchantment charge of the temporary container item stored on the server.
    *
    * \param charge The enchantment charge.
    * \return void
    */
    extern "C" void SetContainerItemEnchantmentCharge(double enchantmentCharge) noexcept;

    /**
    * \brief Set the soul of the temporary container item stored on the server.
    *
    * \param refId The soul.
    * \return void
    */
    extern "C" void SetContainerItemSoul(const char* soul) noexcept;

    /**
    * \brief Set the action count of the container item at a certain itemIndex in the container
    * changes of the object at a certain objectIndex in the object list stored on the server.
    *
    * When resending a received Container packet, this allows you to correct the amount of items
    * removed from a container by a player when it conflicts with what other players have already
    * taken.
    *
    * \param objectIndex The index of the object.
    * \param itemIndex The index of the container item.
    * \param actionCount The action count.
    * \return void
    */
    extern "C" void SetContainerItemActionCountByIndex(unsigned int objectIndex, unsigned int itemIndex, int actionCount) noexcept;

    /**
    * \brief Add a copy of the server's temporary object to the server's currently stored object
    * list.
    *
    * In the process, the server's temporary object will automatically be cleared so a new
    * one can be set up.
    *
    * \return void
    */
    extern "C" void AddObject() noexcept;

    /**
    * \brief Add a copy of the server's temporary container item to the container changes of the
    * server's temporary object.
    *
    * In the process, the server's temporary container item will automatically be cleared so a new
    * one can be set up.
    *
    * \return void
    */
    extern "C" void AddContainerItem() noexcept;

    /**
    * \brief Send an ObjectActivate packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendObjectActivate(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectPlace packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendObjectPlace(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectSpawn packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendObjectSpawn(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectDelete packet.
    *
    * \param broadcast Whether this packet should be sent only to the player for whom the current
    *                  object list was initialized or to everyone on the server.
    *
    * \return void
    */
    extern "C" void SendObjectDelete(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectLock packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendObjectLock(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectTrap packet.
    *
    * \param broadcast Whether this packet should be sent only to the player for whom the current
    *                  object list was initialized or to everyone on the server.
    *
    * \return void
    */
    extern "C" void SendObjectTrap(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectScale packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendObjectScale(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send an ObjectState packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendObjectState(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send a DoorState packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendDoorState(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send a DoorDestination packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendDoorDestination(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send a Container packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendContainer(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send a VideoPlay packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendVideoPlay(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Send a ConsoleCommand packet.
    *
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendConsoleCommand(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;


    // All methods below are deprecated versions of methods from above

    extern "C" void ReadLastObjectList() noexcept;
    extern "C" void ReadLastEvent() noexcept;
    extern "C" void InitializeObjectList(unsigned short pid) noexcept;
    extern "C" void InitializeEvent(unsigned short pid) noexcept;
    extern "C" void CopyLastObjectListToStore() noexcept;
    extern "C" unsigned int GetObjectChangesSize() noexcept;
    extern "C" unsigned char GetEventAction() noexcept;
    extern "C" unsigned char GetEventContainerSubAction() noexcept;
    extern "C" unsigned int GetObjectRefNumIndex(unsigned int index) noexcept;
    extern "C" unsigned int GetObjectSummonerRefNumIndex(unsigned int index) noexcept;
    extern "C" void SetEventCell(const char* cellDescription) noexcept;
    extern "C" void SetEventAction(unsigned char action) noexcept;
    extern "C" void SetEventConsoleCommand(const char* consoleCommand) noexcept;
    extern "C" void SetObjectRefNumIndex(int refNum) noexcept;
    extern "C" void AddWorldObject() noexcept;
}


#endif //OPENMW_OBJECTAPI_HPP
