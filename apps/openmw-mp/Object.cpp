//
// Created by koncord on 26.08.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>

#include "Networking.hpp"

#include "Object.hpp"
#include "Player.hpp"

using namespace std;

void Object::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Object>("Object",
                                         "refId", sol::property(&BaseObject::getRefId, &BaseObject::setRefId),
                                         "refNum", sol::property(&BaseObject::getRefNum, &BaseObject::setRefNum),
                                         "mpNum", sol::property(&BaseObject::getMpNum, &BaseObject::setMpNum),
                                         "guid", sol::property(&BaseObject::getGuid, &BaseObject::setGuid),
                                         "getPosition", &Object::getPosition,
                                         "setPosition", &Object::setPosition,
                                         "getRotation", &Object::getRotation,
                                         "setRotation", &Object::setRotation,
                                         "count", sol::property(&Object::getCount, &Object::setCount),
                                         "goldValue", sol::property(&Object::getGoldValue, &Object::setGoldValue),
                                         "scale", sol::property(&Object::getScale, &Object::setScale),
                                         "state", sol::property(&Object::getState, &Object::setState),
                                         "lockLevel", sol::property(&Object::getLockLevel, &Object::setLockLevel),
                                         "doorState", sol::property(&Object::getDoorState, &Object::setDoorState),
                                         "hasContainer", &Object::hasContainer,
                                         "setTeleportState", &Object::setTeleportState,
                                         "setDoorDestination", &Object::setDoorDestination,
                                         "setDisarmState", &Object::setDisarmState,
                                         "setMasterState", &Object::setMasterState
    );
}

Object::Object()
{

}

Object::~Object()
{

}

void Object::update()
{

}

tuple<float, float, float> Object::getPosition() const
{
    return make_tuple(object.position.pos[0], object.position.pos[1], object.position.pos[2]);
}

void Object::setPosition(float x, float y, float z)
{
    object.position.pos[0] = x;
    object.position.pos[1] = y;
    object.position.pos[2] = z;
    object.droppedByPlayer = false;
    changedObjectPlace = true;
}

tuple<float, float, float> Object::getRotation() const
{
    return make_tuple(object.position.rot[0], object.position.rot[1], object.position.rot[2]);
}

void Object::setRotation(float x, float y, float z)
{
    object.position.rot[0] = x;
    object.position.rot[1] = y;
    object.position.rot[2] = z;
    changedObjectPlace = true;
}

BaseObject::BaseObject(): changedBase(false), copied(false)
{

}

string BaseObject::getRefId() const
{
    return object.refId;
}

void BaseObject::setRefId(const string &refId)
{
    changedBase = true;
    object.refId = refId;
}

unsigned BaseObject::getRefNum() const
{
    return object.refNumIndex;
}

void BaseObject::setRefNum(unsigned refNum)
{
    changedBase = true;
    object.refNumIndex = refNum;
}

unsigned BaseObject::getMpNum() const
{
    return object.mpNum;
}

void BaseObject::setMpNum(unsigned mpNum)
{
    changedBase = true;
    object.mpNum = mpNum;
}

RakNet::RakNetGUID BaseObject::getGuid() const
{
    return object.guid;
}

void BaseObject::setGuid(const RakNet::RakNetGUID &guid)
{
    changedBase = true;
    object.guid = guid;
    object.isPlayer = true;
}

int Object::getCount() const
{
    return object.count;
}

void Object::setCount(int count)
{
    changedObjectPlace = true;
    object.count = count;
}

int Object::getCharge() const
{
    return object.charge;
}

void Object::setCharge(int charge)
{
    changedObjectPlace = true;
    object.charge = charge;

}

float Object::getEnchantmentCharge() const
{
    return object.enchantmentCharge;
}

void Object::setEnchantmentCharge(float enchantmentCharge)
{
    changedObjectPlace = true;
    object.enchantmentCharge = enchantmentCharge;

}

int Object::getGoldValue() const
{
    return object.goldValue;
}

void Object::setGoldValue(int gold)
{
    changedObjectPlace = true;
    object.goldValue = gold;
}

float Object::getScale() const
{
    return object.scale;
}

void Object::setScale(float scale)
{
    changedObjectScale = true;
    object.scale = scale;
}

bool Object::getState() const
{
    return object.objectState;
}

void Object::setState(bool state)
{
    changedObjectState = true;
    object.objectState = state;
}

int Object::getDoorState() const
{
    return object.doorState;
}

void Object::setDoorState(int state)
{
    changedDoorState = true;
    object.doorState = state;
}

int Object::getLockLevel() const
{
    return object.lockLevel;
}

void Object::setLockLevel(int locklevel)
{
    changedObjectLock = true;
    object.lockLevel = locklevel;
}

bool Object::hasContainer() const
{
    return object.hasContainer;
}

void Object::setTeleportState(bool state)
{
    changedDoorDestination = true;
    object.teleportState = state;
}

void Object::setDoorDestination(const std::string &cellDescription, float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
    changedDoorDestination = true;
    object.destinationCell = Utils::getCellFromDescription(cellDescription);
    object.destinationPosition.pos[0] = posX;
    object.destinationPosition.pos[1] = posY;
    object.destinationPosition.pos[2] = posZ;
    object.destinationPosition.rot[0] = rotX;
    object.destinationPosition.rot[1] = rotY;
    object.destinationPosition.rot[2] = rotZ;
}

void Object::setDisarmState(bool state)
{
    changedObjectTrap = true;
    object.isDisarmed = state;
}

void Object::setMasterState(bool state)
{
    changedObjectSpawn = true;
    object.hasMaster = state;
}


// TODO: Make this actually reflect the capabilities offered by containers in 0.6.3
void Container::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Container>("Container",
                                            "refId", sol::property(&BaseObject::getRefId, &BaseObject::setRefId),
                                            "refNum", sol::property(&BaseObject::getRefNum, &BaseObject::setRefNum),
                                            "mpNum", sol::property(&BaseObject::getMpNum, &BaseObject::setMpNum),
                                            "getItem", &Container::getItem,
                                            "addItem", &Container::addItem,
                                            "setItem", &Container::setItem,
                                            "getActionCount", &Container::getActionCount
    );
}

Container::Container()
{

}

tuple<string, int, int, double> Container::getItem(int i) const
{
    auto &item = object.containerItems.at(i);
    return make_tuple(item.refId, item.count, item.charge, item.enchantmentCharge);
}

void Container::setItem(int i, const string &refId, int count, int charge, float enchantmentCharge)
{
    auto &item = object.containerItems.at(i);
    item.refId = refId;
    item.count = count;
    item.charge = charge;
    item.enchantmentCharge = enchantmentCharge;
    changed = true;
}

void Container::addItem(const string &refId, int count, int charge, float enchantmentCharge)
{
    mwmp::ContainerItem item;
    item.refId = refId;
    item.count = count;
    item.charge = charge;
    item.enchantmentCharge = enchantmentCharge;
    object.containerItems.push_back(item);
    changed = true;
}

int Container::getActionCount(int i) const
{
    return object.containerItems.at(i).actionCount;
}

size_t Container::size() const
{
    return object.containerItems.size();
}

void ObjectController::Init(LuaState &lua)
{
    sol::table objectCtrl = lua.getState()->create_table("ObjectCtrl");

    objectCtrl.set_function("sendObjects", [&lua](shared_ptr<Player> player, shared_ptr<vector<shared_ptr<Object>>> objects,
                                                  const std::string &cellDescription) {
        return lua.getObjectCtrl().sendObjects(player, objects, Utils::getCellFromDescription(cellDescription));
    });

    objectCtrl.set_function("sendContainers", [&lua](shared_ptr<Player> player, shared_ptr<vector<shared_ptr<Container>>> objects,
                                                     const std::string &cellDescription) {
        return lua.getObjectCtrl().sendContainers(player, objects, Utils::getCellFromDescription(cellDescription));
    });

    objectCtrl.set_function("sendConsoleCommand", [&lua](shared_ptr<Player> player, shared_ptr<vector<shared_ptr<Object>>> objects,
                                                         const std::string &cellDescription, const std::string &command,
                                                         bool broadcast) {
        return lua.getObjectCtrl().sendConsoleCommand(player, objects, Utils::getCellFromDescription(cellDescription),
                                                      command, broadcast);
    });
    objectCtrl.set_function("requestContainers", [&lua](shared_ptr<Player> player) {
        lua.getObjectCtrl().requestContainers(player);
    });


}

shared_ptr<vector<shared_ptr<Object>>> ObjectController::copyObjects(mwmp::BaseObjectList &objectList)
{
    auto objects = make_shared<vector<shared_ptr<Object>>>();

    for (auto &obj : objectList.baseObjects)
    {
        auto object = new Object;
        object->copied = true;
        object->object = obj;
        objects->emplace_back(object);
    }
    return objects;
}

shared_ptr<vector<shared_ptr<Container>>> ObjectController::copyContainers(mwmp::BaseObjectList &objectList)
{
    auto containers = make_shared<vector<shared_ptr<Container>>>();

    for (auto &obj : objectList.baseObjects)
    {
        auto container = new Container;
        container->copied = true;
        container->object = obj;
        containers->emplace_back(container);
    }
    return containers;
}

void ObjectController::sendObjects(shared_ptr<Player> player, shared_ptr<vector<shared_ptr<Object>>> objects, const ESM::Cell &cell, bool broadcast)
{
    enum Type
    {
        DOOR_STATE = 0,
        DOOR_DESTINATION,
        OBJECT_STATE,
        OBJECT_SCALE,
        OBJECT_TRAP,
        OBJECT_LOCK,
        OBJECT_DELETE,
        OBJECT_SPAWN,
        OBJECT_PLACE,
        LAST
    };
    mwmp::BaseObjectList objectLists[Type::LAST];
    bool changed[Type::LAST];

    for (auto &objectList : objectLists)
    {
        objectList.action = mwmp::BaseObjectList::Action::Set;
        objectList.guid = player->guid;
        objectList.cell = cell;
    }


    for (auto &object : *objects)
    {
        //sendObject(player.get(), object.get());

        bool validNewObjOrCopy = (!object->copied && object->changedBase) || object->copied;

        if (object->changedDoorState && validNewObjOrCopy)
        {
            changed[Type::DOOR_STATE] = true;
            objectLists[Type::DOOR_STATE].baseObjects.push_back(object->object);
        }
        if (object->changedDoorDestination && validNewObjOrCopy)
        {
            changed[Type::DOOR_DESTINATION] = true;
            objectLists[Type::DOOR_DESTINATION].baseObjects.push_back(object->object);
        }
        if (object->changedObjectState && validNewObjOrCopy)
        {
            changed[Type::OBJECT_STATE] = true;
            objectLists[Type::OBJECT_STATE].baseObjects.push_back(object->object);
        }
        if (object->changedObjectScale && validNewObjOrCopy)
        {
            changed[Type::OBJECT_SCALE] = true;
            objectLists[Type::OBJECT_SCALE].baseObjects.push_back(object->object);
        }
        if (object->changedObjectTrap && validNewObjOrCopy)
        {
            changed[Type::OBJECT_TRAP] = true;
            objectLists[Type::OBJECT_TRAP].baseObjects.push_back(object->object);
        }
        if (object->changedObjectLock && validNewObjOrCopy)
        {
            changed[Type::OBJECT_LOCK] = true;
            objectLists[Type::OBJECT_LOCK].baseObjects.push_back(object->object);
        }
        if (object->changedObjectDelete && validNewObjOrCopy)
        {
            changed[Type::OBJECT_DELETE] = true;
            objectLists[Type::OBJECT_DELETE].baseObjects.push_back(object->object);
        }
        if (object->changedObjectSpawn && validNewObjOrCopy)
        {
            changed[Type::OBJECT_SPAWN] = true;
            objectLists[Type::OBJECT_SPAWN].baseObjects.push_back(object->object);
        }
        if (object->changedObjectPlace && validNewObjOrCopy)
        {
            changed[Type::OBJECT_PLACE] = true;
            objectLists[Type::OBJECT_PLACE].baseObjects.push_back(object->object);
        }
    }

    auto worldCtrl = mwmp::Networking::get().getObjectPacketController();

    if (changed[Type::DOOR_STATE])
    {
        auto packet = worldCtrl->GetPacket(ID_DOOR_STATE);
        auto &objectList = objectLists[Type::DOOR_STATE];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::DOOR_DESTINATION])
    {
        auto packet = worldCtrl->GetPacket(ID_DOOR_DESTINATION);
        auto &objectList = objectLists[Type::DOOR_DESTINATION];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_STATE])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_STATE);
        auto &objectList = objectLists[Type::OBJECT_STATE];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_SCALE])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_SCALE);
        auto &objectList = objectLists[Type::OBJECT_SCALE];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_TRAP])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_TRAP);
        auto &objectList = objectLists[Type::OBJECT_TRAP];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_LOCK])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_LOCK);
        auto &objectList = objectLists[Type::OBJECT_LOCK];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_DELETE])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_DELETE);
        auto &objectList = objectLists[Type::OBJECT_DELETE];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_SCALE])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_SPAWN);
        auto &objectList = objectLists[Type::OBJECT_SCALE];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
    if (changed[Type::OBJECT_PLACE])
    {
        auto packet = worldCtrl->GetPacket(ID_OBJECT_PLACE);
        auto &objectList = objectLists[Type::OBJECT_PLACE];
        packet->setObjectList(&objectList);
        packet->Send(false);

        if (broadcast)
            packet->Send(true);
    }
}

void ObjectController::sendConsoleCommand(shared_ptr<Player> player, shared_ptr<vector<shared_ptr<Object>>> objects,
    const ESM::Cell &cell, const std::string &consoleCommand, bool broadcast)
{

    mwmp::BaseObjectList objectList;
    objectList.cell = cell;
    objectList.consoleCommand = consoleCommand;
    objectList.guid = player->guid;

    for (auto &object : *objects)
        objectList.baseObjects.push_back(object->object);

    auto packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_CONSOLE_COMMAND);
    packet->setObjectList(&objectList);
    packet->Send(false);

    if (broadcast)
        packet->Send(true);
}

void ObjectController::sendContainers(shared_ptr<Player> player, shared_ptr<vector<shared_ptr<Container>>> objects,
    const ESM::Cell &cell, bool broadcast)
{

    mwmp::BaseObjectList objectList;
    objectList.cell = cell;
    objectList.action = mwmp::BaseObjectList::Action::Set;
    objectList.guid = player->guid;

    for (auto &object : *objects)
    {
        bool validNewObjOrCopy = (!object->copied && object->changedBase) || object->copied;
        if (object->changed && validNewObjOrCopy)
            objectList.baseObjects.push_back(object->object);
    }

    auto packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_CONTAINER);
    packet->setObjectList(&objectList);
    packet->Send(false);

    if (broadcast)
        packet->Send(true);
}

void ObjectController::requestContainers(shared_ptr<Player> player)
{
    mwmp::BaseObjectList objectList;
    objectList.action = mwmp::BaseObjectList::Action::Request;
    objectList.guid = player->guid;
    objectList.cell = player->cell;

    auto packet = mwmp::Networking::get().getObjectPacketController()->GetPacket(ID_CONTAINER);
    packet->setObjectList(&objectList);
    packet->Send(objectList.guid);
}
