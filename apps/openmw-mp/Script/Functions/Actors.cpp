#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Base/BaseActor.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Utils.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>

#include <components/esm/creaturestats.hpp>

#include "Actors.hpp"

using namespace mwmp;

BaseActorList *readActorList;
BaseActorList writeActorList;

BaseActor tempActor;
const BaseActor emptyActor = {};

static std::string tempCellDescription;

extern "C" void ActorFunctions::ReadReceivedActorList() noexcept
{
    readActorList = mwmp::Networking::getPtr()->getReceivedActorList();
}

extern "C" void ActorFunctions::ReadCellActorList(const char* cellDescription) noexcept
{
    ESM::Cell esmCell = Utils::getCellFromDescription(cellDescription);
    Cell *serverCell = CellController::get()->getCell(&esmCell);
    readActorList = serverCell->getActorList();
}

extern "C" void ActorFunctions::ClearActorList() noexcept
{
    writeActorList.cell.blank();
    writeActorList.baseActors.clear();
}

extern "C" void ActorFunctions::SetActorListPid(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    writeActorList.guid = player->guid;
}

extern "C" void ActorFunctions::CopyReceivedActorListToStore() noexcept
{
    writeActorList = *readActorList;
}

extern "C" unsigned int ActorFunctions::GetActorListSize() noexcept
{
    return readActorList->count;
}

extern "C" unsigned char ActorFunctions::GetActorListAction() noexcept
{
    return readActorList->action;
}

extern "C" const char *ActorFunctions::GetActorCell(unsigned int index) noexcept
{
    tempCellDescription = readActorList->baseActors.at(index).cell.getDescription();
    return tempCellDescription.c_str();
}

extern "C" const char *ActorFunctions::GetActorRefId(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).refId.c_str();
}

extern "C" unsigned int ActorFunctions::GetActorRefNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).refNum;
}

extern "C" unsigned int ActorFunctions::GetActorMpNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).mpNum;
}

extern "C" double ActorFunctions::GetActorPosX(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.pos[0];
}

extern "C" double ActorFunctions::GetActorPosY(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.pos[1];
}

extern "C" double ActorFunctions::GetActorPosZ(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.pos[2];
}

extern "C" double ActorFunctions::GetActorRotX(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.rot[0];
}

extern "C" double ActorFunctions::GetActorRotY(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.rot[1];
}

extern "C" double ActorFunctions::GetActorRotZ(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).position.rot[2];
}

extern "C" double ActorFunctions::GetActorHealthBase(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[0].mBase;
}

extern "C" double ActorFunctions::GetActorHealthCurrent(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[0].mCurrent;
}

extern "C" double ActorFunctions::GetActorHealthModified(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[0].mMod;
}

extern "C" double ActorFunctions::GetActorMagickaBase(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[1].mBase;
}

extern "C" double ActorFunctions::GetActorMagickaCurrent(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[1].mCurrent;
}

extern "C" double ActorFunctions::GetActorMagickaModified(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[1].mMod;
}

extern "C" double ActorFunctions::GetActorFatigueBase(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[2].mBase;
}

extern "C" double ActorFunctions::GetActorFatigueCurrent(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[2].mCurrent;
}

extern "C" double ActorFunctions::GetActorFatigueModified(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).creatureStats.mDynamic[2].mMod;
}

extern "C" const char *ActorFunctions::GetActorEquipmentItemRefId(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].refId.c_str();
}

extern "C" int ActorFunctions::GetActorEquipmentItemCount(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].count;
}

extern "C" int ActorFunctions::GetActorEquipmentItemCharge(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].charge;
}

extern "C" double ActorFunctions::GetActorEquipmentItemEnchantmentCharge(unsigned int index, unsigned short slot) noexcept
{
    return readActorList->baseActors.at(index).equipmentItems[slot].enchantmentCharge;
}

extern "C" bool ActorFunctions::DoesActorHavePlayerKiller(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.isPlayer;
}

extern "C" int ActorFunctions::GetActorKillerPid(unsigned int index) noexcept
{
    Player *player = Players::getPlayer(readActorList->baseActors.at(index).killer.guid);

    if (player != nullptr)
        return player->getId();

    return -1;
}

extern "C" const char *ActorFunctions::GetActorKillerRefId(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.refId.c_str();
}

extern "C" unsigned int ActorFunctions::GetActorKillerRefNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.refNum;
}

extern "C" unsigned int ActorFunctions::GetActorKillerMpNum(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.mpNum;
}

extern "C" const char *ActorFunctions::GetActorKillerName(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).killer.name.c_str();
}

extern "C" bool ActorFunctions::DoesActorHavePosition(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).hasPositionData;
}

extern "C" bool ActorFunctions::DoesActorHaveStatsDynamic(unsigned int index) noexcept
{
    return readActorList->baseActors.at(index).hasStatsDynamicData;
}

extern "C" void ActorFunctions::SetActorListCell(const char* cellDescription) noexcept
{
    writeActorList.cell = Utils::getCellFromDescription(cellDescription);
}

extern "C" void ActorFunctions::SetActorListAction(unsigned char action) noexcept
{
    writeActorList.action = action;
}

extern "C" void ActorFunctions::SetActorCell(const char* cellDescription) noexcept
{
    tempActor.cell = Utils::getCellFromDescription(cellDescription);
}

extern "C" void ActorFunctions::SetActorRefId(const char* refId) noexcept
{
    tempActor.refId = refId;
}

extern "C" void ActorFunctions::SetActorRefNum(int refNum) noexcept
{
    tempActor.refNum = refNum;
}

extern "C" void ActorFunctions::SetActorMpNum(int mpNum) noexcept
{
    tempActor.mpNum = mpNum;
}

extern "C" void ActorFunctions::SetActorPosition(double x, double y, double z) noexcept
{
    tempActor.position.pos[0] = x;
    tempActor.position.pos[1] = y;
    tempActor.position.pos[2] = z;
}

extern "C" void ActorFunctions::SetActorRotation(double x, double y, double z) noexcept
{
    tempActor.position.rot[0] = x;
    tempActor.position.rot[1] = y;
    tempActor.position.rot[2] = z;
}

extern "C" void ActorFunctions::SetActorHealthBase(double value) noexcept
{
    tempActor.creatureStats.mDynamic[0].mBase = value;
}

extern "C" void ActorFunctions::SetActorHealthCurrent(double value) noexcept
{
    tempActor.creatureStats.mDynamic[0].mCurrent = value;
}

extern "C" void ActorFunctions::SetActorHealthModified(double value) noexcept
{
    tempActor.creatureStats.mDynamic[0].mMod = value;
}

extern "C" void ActorFunctions::SetActorMagickaBase(double value) noexcept
{
    tempActor.creatureStats.mDynamic[1].mBase = value;
}

extern "C" void ActorFunctions::SetActorMagickaCurrent(double value) noexcept
{
    tempActor.creatureStats.mDynamic[1].mCurrent = value;
}

extern "C" void ActorFunctions::SetActorMagickaModified(double value) noexcept
{
    tempActor.creatureStats.mDynamic[1].mMod = value;
}

extern "C" void ActorFunctions::SetActorFatigueBase(double value) noexcept
{
    tempActor.creatureStats.mDynamic[2].mBase = value;
}

extern "C" void ActorFunctions::SetActorFatigueCurrent(double value) noexcept
{
    tempActor.creatureStats.mDynamic[2].mCurrent = value;
}

extern "C" void ActorFunctions::SetActorFatigueModified(double value) noexcept
{
    tempActor.creatureStats.mDynamic[2].mMod = value;
}

extern "C" void ActorFunctions::SetActorSound(const char* sound) noexcept
{
    tempActor.sound = sound;
}

extern "C" void ActorFunctions::SetActorAIAction(unsigned int action) noexcept
{
    tempActor.aiAction = action;
}

extern "C" void ActorFunctions::SetActorAITargetToPlayer(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    tempActor.hasAiTarget = true;
    tempActor.aiTarget.isPlayer = true;

    tempActor.aiTarget.guid = player->guid;
}

extern "C" void ActorFunctions::SetActorAITargetToObject(int refNum, int mpNum) noexcept
{
    tempActor.hasAiTarget = true;
    tempActor.aiTarget.isPlayer = false;

    tempActor.aiTarget.refNum = refNum;
    tempActor.aiTarget.mpNum = mpNum;
}

extern "C" void ActorFunctions::SetActorAICoordinates(double x, double y, double z) noexcept
{
    tempActor.aiCoordinates.pos[0] = x;
    tempActor.aiCoordinates.pos[1] = y;
    tempActor.aiCoordinates.pos[2] = z;
}

extern "C" void ActorFunctions::SetActorAIDistance(unsigned int distance) noexcept
{
    tempActor.aiDistance = distance;
}

extern "C" void ActorFunctions::SetActorAIDuration(unsigned int duration) noexcept
{
    tempActor.aiDuration = duration;
}

extern "C" void ActorFunctions::SetActorAIRepetition(bool shouldRepeat) noexcept
{
    tempActor.aiShouldRepeat = shouldRepeat;
}

extern "C" void ActorFunctions::EquipActorItem(unsigned short slot, const char *refId, unsigned int count, int charge, double enchantmentCharge) noexcept
{
    tempActor.equipmentItems[slot].refId = refId;
    tempActor.equipmentItems[slot].count = count;
    tempActor.equipmentItems[slot].charge = charge;
    tempActor.equipmentItems[slot].enchantmentCharge = enchantmentCharge;
}

extern "C" void ActorFunctions::UnequipActorItem(unsigned short slot) noexcept
{
    ActorFunctions::EquipActorItem(slot, "", 0, -1, -1);
}

extern "C" void ActorFunctions::AddActor() noexcept
{
    writeActorList.baseActors.push_back(tempActor);

    tempActor = emptyActor;
}

extern "C" void ActorFunctions::SendActorList() noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_LIST);
    actorPacket->setActorList(&writeActorList);
    actorPacket->Send(writeActorList.guid);
}

extern "C" void ActorFunctions::SendActorAuthority() noexcept
{
    Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

    if (serverCell != nullptr)
    {
        serverCell->setAuthority(writeActorList.guid);

        mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AUTHORITY);
        actorPacket->setActorList(&writeActorList);
        actorPacket->Send(writeActorList.guid);

        // Also send this to everyone else who has the cell loaded
        serverCell->sendToLoaded(actorPacket, &writeActorList);
    }
}

extern "C" void ActorFunctions::SendActorPosition(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_POSITION);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

extern "C" void ActorFunctions::SendActorStatsDynamic(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_STATS_DYNAMIC);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

extern "C" void ActorFunctions::SendActorEquipment(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_EQUIPMENT);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

extern "C" void ActorFunctions::SendActorSpeech(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_SPEECH);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

extern "C" void ActorFunctions::SendActorAI(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AI);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

extern "C" void ActorFunctions::SendActorCellChange(bool sendToOtherVisitors, bool skipAttachedPlayer) noexcept
{
    mwmp::ActorPacket *actorPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_CELL_CHANGE);
    actorPacket->setActorList(&writeActorList);

    if (!skipAttachedPlayer)
        actorPacket->Send(writeActorList.guid);

    if (sendToOtherVisitors)
    {
        Cell *serverCell = CellController::get()->getCell(&writeActorList.cell);

        if (serverCell != nullptr)
        {
            serverCell->sendToLoaded(actorPacket, &writeActorList);
        }
    }
}

extern "C" // All methods below are deprecated versions of methods from above

void ActorFunctions::ReadLastActorList() noexcept
{
    ReadReceivedActorList();
}

extern "C" void ActorFunctions::InitializeActorList(unsigned short pid) noexcept
{
    ClearActorList();
    SetActorListPid(pid);
}

extern "C" void ActorFunctions::CopyLastActorListToStore() noexcept
{
    CopyLastActorListToStore();
}

extern "C" unsigned int ActorFunctions::GetActorRefNumIndex(unsigned int index) noexcept
{
    return GetActorRefNum(index);
}

extern "C" unsigned int ActorFunctions::GetActorKillerRefNumIndex(unsigned int index) noexcept
{
    return GetActorKillerRefNum(index);
}

extern "C" void ActorFunctions::SetActorRefNumIndex(int refNum) noexcept
{
    tempActor.refNum = refNum;
}
