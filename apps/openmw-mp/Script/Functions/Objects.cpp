#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Base/BaseObject.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Utils.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>

#include "Objects.hpp"

using namespace mwmp;

BaseObjectList *readObjectList;
BaseObjectList writeObjectList;

BaseObject tempObject;
const BaseObject emptyObject = {};

ContainerItem tempContainerItem;
const ContainerItem emptyContainerItem = {};

extern "C" void ObjectFunctions::ReadReceivedObjectList() noexcept
{
    readObjectList = mwmp::Networking::getPtr()->getReceivedObjectList();
}

extern "C" void ObjectFunctions::ClearObjectList() noexcept
{
    writeObjectList.cell.blank();
    writeObjectList.baseObjects.clear();
    writeObjectList.packetOrigin = mwmp::PACKET_ORIGIN::SERVER_SCRIPT;
}

extern "C" void ObjectFunctions::SetObjectListPid(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeObjectList.guid = player->guid;
}

extern "C" void ObjectFunctions::CopyReceivedObjectListToStore() noexcept
{
    writeObjectList = *readObjectList;
}

extern "C" unsigned int ObjectFunctions::GetObjectListSize() noexcept
{
    return readObjectList->baseObjectCount;
}

extern "C" unsigned char ObjectFunctions::GetObjectListOrigin() noexcept
{
    return readObjectList->packetOrigin;
}

extern "C" const char *ObjectFunctions::GetObjectListClientScript() noexcept
{
    return readObjectList->originClientScript.c_str();
}

extern "C" unsigned char ObjectFunctions::GetObjectListAction() noexcept
{
    return readObjectList->action;
}

extern "C" unsigned char ObjectFunctions::GetObjectListContainerSubAction() noexcept
{
    return readObjectList->containerSubAction;
}

extern "C" bool ObjectFunctions::IsObjectPlayer(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).isPlayer;
}

extern "C" int ObjectFunctions::GetObjectPid(unsigned int index) noexcept
{
    Player *player = Players::getPlayer(readObjectList->baseObjects.at(index).guid);

    if (player != nullptr)
        return player->getId();

    return -1;
}

extern "C" const char *ObjectFunctions::GetObjectRefId(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).refId.c_str();
}

extern "C" unsigned int ObjectFunctions::GetObjectRefNum(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).refNum;
}

extern "C" unsigned int ObjectFunctions::GetObjectMpNum(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).mpNum;
}

extern "C" int ObjectFunctions::GetObjectCount(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).count;
}

extern "C" int ObjectFunctions::GetObjectCharge(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).charge;
}

extern "C" double ObjectFunctions::GetObjectEnchantmentCharge(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).enchantmentCharge;
}

extern "C" const char *ObjectFunctions::GetObjectSoul(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).soul.c_str();
}

extern "C" int ObjectFunctions::GetObjectGoldValue(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).goldValue;
}

extern "C" double ObjectFunctions::GetObjectScale(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).scale;
}

extern "C" bool ObjectFunctions::GetObjectState(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).objectState;
}

extern "C" int ObjectFunctions::GetObjectDoorState(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).doorState;
}

extern "C" int ObjectFunctions::GetObjectLockLevel(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).lockLevel;
}

extern "C" bool ObjectFunctions::DoesObjectHavePlayerActivating(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).activatingActor.isPlayer;
}

extern "C" int ObjectFunctions::GetObjectActivatingPid(unsigned int index) noexcept
{
    Player *player = Players::getPlayer(readObjectList->baseObjects.at(index).activatingActor.guid);

    if (player != nullptr)
        return player->getId();

    return -1;
}

extern "C" const char *ObjectFunctions::GetObjectActivatingRefId(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).activatingActor.refId.c_str();
}

extern "C" unsigned int ObjectFunctions::GetObjectActivatingRefNum(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).activatingActor.refNum;
}

extern "C" unsigned int ObjectFunctions::GetObjectActivatingMpNum(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).activatingActor.mpNum;
}

extern "C" const char *ObjectFunctions::GetObjectActivatingName(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).activatingActor.name.c_str();
}

extern "C" bool ObjectFunctions::GetObjectSummonState(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).isSummon;
}

extern "C" double ObjectFunctions::GetObjectSummonDuration(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).summonDuration;
}

extern "C" bool ObjectFunctions::DoesObjectHavePlayerSummoner(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).master.isPlayer;
}

extern "C" int ObjectFunctions::GetObjectSummonerPid(unsigned int index) noexcept
{
    Player *player = Players::getPlayer(readObjectList->baseObjects.at(index).master.guid);
    
    if (player != nullptr)
        return player->getId();

    return -1;
}

extern "C" const char *ObjectFunctions::GetObjectSummonerRefId(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).master.refId.c_str();
}

extern "C" unsigned int ObjectFunctions::GetObjectSummonerRefNum(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).master.refNum;
}

extern "C" unsigned int ObjectFunctions::GetObjectSummonerMpNum(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).master.mpNum;
}

extern "C" double ObjectFunctions::GetObjectPosX(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).position.pos[0];
}

extern "C" double ObjectFunctions::GetObjectPosY(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).position.pos[1];
}

extern "C" double ObjectFunctions::GetObjectPosZ(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).position.pos[2];
}

extern "C" double ObjectFunctions::GetObjectRotX(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).position.rot[0];
}

extern "C" double ObjectFunctions::GetObjectRotY(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).position.rot[1];
}

extern "C" double ObjectFunctions::GetObjectRotZ(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).position.rot[2];
}

extern "C" const char *ObjectFunctions::GetVideoFilename(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).videoFilename.c_str();
}

extern "C" unsigned int ObjectFunctions::GetContainerChangesSize(unsigned int objectIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex).containerItemCount;
}

extern "C" const char *ObjectFunctions::GetContainerItemRefId(unsigned int objectIndex, unsigned int itemIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex)
        .containerItems.at(itemIndex).refId.c_str();
}

extern "C" int ObjectFunctions::GetContainerItemCount(unsigned int objectIndex, unsigned int itemIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex)
        .containerItems.at(itemIndex).count;
}

extern "C" int ObjectFunctions::GetContainerItemCharge(unsigned int objectIndex, unsigned int itemIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex)
        .containerItems.at(itemIndex).charge;
}

extern "C" double ObjectFunctions::GetContainerItemEnchantmentCharge(unsigned int objectIndex, unsigned int itemIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex)
        .containerItems.at(itemIndex).enchantmentCharge;
}

extern "C" const char *ObjectFunctions::GetContainerItemSoul(unsigned int objectIndex, unsigned int itemIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex)
        .containerItems.at(itemIndex).soul.c_str();
}

extern "C" int ObjectFunctions::GetContainerItemActionCount(unsigned int objectIndex, unsigned int itemIndex) noexcept
{
    return readObjectList->baseObjects.at(objectIndex)
        .containerItems.at(itemIndex).actionCount;
}

extern "C" bool ObjectFunctions::DoesObjectHaveContainer(unsigned int index) noexcept
{
    return readObjectList->baseObjects.at(index).hasContainer;
}

extern "C" void ObjectFunctions::SetObjectListCell(const char* cellDescription) noexcept
{
    writeObjectList.cell = Utils::getCellFromDescription(cellDescription);
}

extern "C" void ObjectFunctions::SetObjectListAction(unsigned char action) noexcept
{
    writeObjectList.action = action;
}

extern "C" void ObjectFunctions::SetObjectListConsoleCommand(const char* consoleCommand) noexcept
{
    writeObjectList.consoleCommand = consoleCommand;
}

extern "C" void ObjectFunctions::SetObjectRefId(const char* refId) noexcept
{
    tempObject.refId = refId;
}

extern "C" void ObjectFunctions::SetObjectRefNum(int refNum) noexcept
{
    tempObject.refNum = refNum;
}

extern "C" void ObjectFunctions::SetObjectMpNum(int mpNum) noexcept
{
    tempObject.mpNum = mpNum;
}

extern "C" void ObjectFunctions::SetObjectCount(int count) noexcept
{
    tempObject.count = count;
}

extern "C" void ObjectFunctions::SetObjectCharge(int charge) noexcept
{
    tempObject.charge = charge;
}

extern "C" void ObjectFunctions::SetObjectEnchantmentCharge(double enchantmentCharge) noexcept
{
    tempObject.enchantmentCharge = enchantmentCharge;
}

extern "C" void ObjectFunctions::SetObjectSoul(const char* soul) noexcept
{
    tempObject.soul = soul;
}

extern "C" void ObjectFunctions::SetObjectGoldValue(int goldValue) noexcept
{
    tempObject.goldValue = goldValue;
}

extern "C" void ObjectFunctions::SetObjectScale(double scale) noexcept
{
    tempObject.scale = scale;
}

extern "C" void ObjectFunctions::SetObjectState(bool objectState) noexcept
{
    tempObject.objectState = objectState;
}

extern "C" void ObjectFunctions::SetObjectLockLevel(int lockLevel) noexcept
{
    tempObject.lockLevel = lockLevel;
}

extern "C" void ObjectFunctions::SetObjectSummonDuration(float summonDuration) noexcept
{
    tempObject.summonDuration = summonDuration;
}

extern "C" void ObjectFunctions::SetObjectDisarmState(bool disarmState) noexcept
{
    tempObject.isDisarmed = disarmState;
}

extern "C" void ObjectFunctions::SetObjectSummonState(bool summonState) noexcept
{
    tempObject.isSummon = summonState;
}

extern "C" void ObjectFunctions::SetObjectPosition(double x, double y, double z) noexcept
{
    tempObject.position.pos[0] = x;
    tempObject.position.pos[1] = y;
    tempObject.position.pos[2] = z;
}

extern "C" void ObjectFunctions::SetObjectRotation(double x, double y, double z) noexcept
{
    tempObject.position.rot[0] = x;
    tempObject.position.rot[1] = y;
    tempObject.position.rot[2] = z;
}

extern "C" void ObjectFunctions::SetObjectActivatingPid(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    tempObject.activatingActor.guid = player->guid;
    tempObject.activatingActor.isPlayer = true;
}

extern "C" void ObjectFunctions::SetObjectDoorState(int doorState) noexcept
{
    tempObject.doorState = doorState;
}

extern "C" void ObjectFunctions::SetObjectDoorTeleportState(bool teleportState) noexcept
{
    tempObject.teleportState = teleportState;
}

extern "C" void ObjectFunctions::SetObjectDoorDestinationCell(const char* cellDescription) noexcept
{
    tempObject.destinationCell = Utils::getCellFromDescription(cellDescription);
}

extern "C" void ObjectFunctions::SetObjectDoorDestinationPosition(double x, double y, double z) noexcept
{
    tempObject.destinationPosition.pos[0] = x;
    tempObject.destinationPosition.pos[1] = y;
    tempObject.destinationPosition.pos[2] = z;
}

extern "C" void ObjectFunctions::SetObjectDoorDestinationRotation(double x, double z) noexcept
{
    tempObject.destinationPosition.rot[0] = x;
    tempObject.destinationPosition.rot[2] = z;
}

extern "C" void ObjectFunctions::SetPlayerAsObject(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    tempObject.guid = player->guid;
    tempObject.isPlayer = true;
}

extern "C" void ObjectFunctions::SetContainerItemRefId(const char* refId) noexcept
{
    tempContainerItem.refId = refId;
}

extern "C" void ObjectFunctions::SetContainerItemCount(int count) noexcept
{
    tempContainerItem.count = count;
}

extern "C" void ObjectFunctions::SetContainerItemCharge(int charge) noexcept
{
    tempContainerItem.charge = charge;
}

extern "C" void ObjectFunctions::SetContainerItemEnchantmentCharge(double enchantmentCharge) noexcept
{
    tempContainerItem.enchantmentCharge = enchantmentCharge;
}

extern "C" void ObjectFunctions::SetContainerItemSoul(const char* soul) noexcept
{
    tempContainerItem.soul = soul;
}

extern "C" void ObjectFunctions::SetContainerItemActionCountByIndex(unsigned int objectIndex, unsigned int itemIndex, int actionCount) noexcept
{
    writeObjectList.baseObjects.at(objectIndex).containerItems.at(itemIndex).actionCount = actionCount;
}

extern "C" void ObjectFunctions::AddObject() noexcept
{
    tempObject.droppedByPlayer = false;
    writeObjectList.baseObjects.push_back(tempObject);

    tempObject = emptyObject;
}

extern "C" void ObjectFunctions::AddContainerItem() noexcept
{
    tempObject.containerItems.push_back(tempContainerItem);

    tempContainerItem = emptyContainerItem;
}

extern "C" void ObjectFunctions::SendObjectActivate(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_ACTIVATE);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectPlace(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_PLACE);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectSpawn(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_SPAWN);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectDelete(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_DELETE);
    packet->setObjectList(&writeObjectList);
    
    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectLock(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_LOCK);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectTrap(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_TRAP);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectScale(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_SCALE);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendObjectState(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_OBJECT_STATE);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendDoorState(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_DOOR_STATE);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendDoorDestination(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_DOOR_DESTINATION);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendContainer(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_CONTAINER);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendVideoPlay(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_VIDEO_PLAY);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" void ObjectFunctions::SendConsoleCommand(bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    mwmp::ObjectPacket *packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_CONSOLE_COMMAND);
    packet->setObjectList(&writeObjectList);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}

extern "C" 
// All methods below are deprecated versions of methods from above

void ObjectFunctions::ReadLastObjectList() noexcept
{
    ReadReceivedObjectList();
}

extern "C" void ObjectFunctions::ReadLastEvent() noexcept
{
    ReadReceivedObjectList();
}

extern "C" void ObjectFunctions::InitializeObjectList(unsigned short pid) noexcept
{
    ClearObjectList();
    SetObjectListPid(pid);
}

extern "C" void ObjectFunctions::InitializeEvent(unsigned short pid) noexcept
{
    InitializeObjectList(pid);
}

extern "C" void ObjectFunctions::CopyLastObjectListToStore() noexcept
{
    CopyReceivedObjectListToStore();
}

extern "C" unsigned int ObjectFunctions::GetObjectChangesSize() noexcept
{
    return GetObjectListSize();
}

extern "C" unsigned char ObjectFunctions::GetEventAction() noexcept
{
    return GetObjectListAction();
}

extern "C" unsigned char ObjectFunctions::GetEventContainerSubAction() noexcept
{
    return GetObjectListContainerSubAction();
}

extern "C" unsigned int ObjectFunctions::GetObjectRefNumIndex(unsigned int index) noexcept
{
    return GetObjectRefNum(index);
}

extern "C" unsigned int ObjectFunctions::GetObjectSummonerRefNumIndex(unsigned int index) noexcept
{
    return GetObjectSummonerRefNum(index);
}

extern "C" void ObjectFunctions::SetEventCell(const char* cellDescription) noexcept
{
    SetObjectListCell(cellDescription);
}

extern "C" void ObjectFunctions::SetEventAction(unsigned char action) noexcept
{
    SetObjectListAction(action);
}

extern "C" void ObjectFunctions::SetEventConsoleCommand(const char* consoleCommand) noexcept
{
    SetObjectListConsoleCommand(consoleCommand);
}

extern "C" void ObjectFunctions::SetObjectRefNumIndex(int refNum) noexcept
{
    SetObjectRefNum(refNum);
}

extern "C" void ObjectFunctions::AddWorldObject() noexcept
{
    AddObject();
}
