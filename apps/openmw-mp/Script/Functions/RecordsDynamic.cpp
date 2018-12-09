#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Base/BaseWorldstate.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Player.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Script/Functions/Worldstate.hpp>
#include <fstream>

#include "RecordsDynamic.hpp"

using namespace std;
using namespace mwmp;

SpellRecord tempSpell;
PotionRecord tempPotion;
EnchantmentRecord tempEnchantment;
CreatureRecord tempCreature;
NpcRecord tempNpc;
ArmorRecord tempArmor;
BookRecord tempBook;
ClothingRecord tempClothing;
MiscellaneousRecord tempMiscellaneous;
WeaponRecord tempWeapon;

BaseOverrides tempOverrides;

ESM::ENAMstruct tempEffect;
ESM::PartReference tempBodyPart;
mwmp::Item tempInventoryItem;

const ESM::EffectList emptyEffectList = {};

extern "C" const ESM::EffectList& GetRecordEffects(unsigned int recordIndex)
{
    unsigned short recordsType = RecordsDynamicFunctions::GetRecordType();

    if (recordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(recordIndex).data.mEffects;
    else if (recordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(recordIndex).data.mEffects;
    else if (recordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(recordIndex).data.mEffects;

    return emptyEffectList;
}

extern "C" void RecordsDynamicFunctions::ClearRecords() noexcept
{
    WorldstateFunctions::writeWorldstate.spellRecords.clear();
    WorldstateFunctions::writeWorldstate.potionRecords.clear();
    WorldstateFunctions::writeWorldstate.enchantmentRecords.clear();
    WorldstateFunctions::writeWorldstate.creatureRecords.clear();
    WorldstateFunctions::writeWorldstate.npcRecords.clear();
    WorldstateFunctions::writeWorldstate.armorRecords.clear();
    WorldstateFunctions::writeWorldstate.bookRecords.clear();
    WorldstateFunctions::writeWorldstate.clothingRecords.clear();
    WorldstateFunctions::writeWorldstate.miscellaneousRecords.clear();
    WorldstateFunctions::writeWorldstate.weaponRecords.clear();
}

extern "C" unsigned short RecordsDynamicFunctions::GetRecordType() noexcept
{
    return WorldstateFunctions::readWorldstate->recordsType;
}

extern "C" unsigned int RecordsDynamicFunctions::GetRecordCount() noexcept
{
    return WorldstateFunctions::readWorldstate->recordsCount;
}

extern "C" unsigned int RecordsDynamicFunctions::GetRecordEffectCount(unsigned int recordIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.size();
}

extern "C" int RecordsDynamicFunctions::GetRecordSubtype(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(index).data.mData.mType;
    else if (readRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(index).data.mData.mType;

    return -1;
}

extern "C" const char *RecordsDynamicFunctions::GetRecordId(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(index).data.mId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(index).data.mId.c_str();

    return "invalid";
}

extern "C" const char *RecordsDynamicFunctions::GetRecordBaseId(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(index).baseId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).baseId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(index).baseId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::ARMOR)
        return WorldstateFunctions::readWorldstate->armorRecords.at(index).baseId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::BOOK)
        return WorldstateFunctions::readWorldstate->bookRecords.at(index).baseId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        return WorldstateFunctions::readWorldstate->clothingRecords.at(index).baseId.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::WEAPON)
        return WorldstateFunctions::readWorldstate->weaponRecords.at(index).baseId.c_str();

    return "invalid";
}

extern "C" const char *RecordsDynamicFunctions::GetRecordName(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(index).data.mName.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mName.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::ARMOR)
        return WorldstateFunctions::readWorldstate->armorRecords.at(index).data.mName.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::BOOK)
        return WorldstateFunctions::readWorldstate->bookRecords.at(index).data.mName.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        return WorldstateFunctions::readWorldstate->clothingRecords.at(index).data.mName.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::WEAPON)
        return WorldstateFunctions::readWorldstate->weaponRecords.at(index).data.mName.c_str();

    return "invalid";
}

extern "C" const char *RecordsDynamicFunctions::GetRecordModel(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mModel.c_str();

    return "invalid";
}

extern "C" const char *RecordsDynamicFunctions::GetRecordIcon(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mIcon.c_str();

    return "invalid";
}

extern "C" const char *RecordsDynamicFunctions::GetRecordScript(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mScript.c_str();

    return "invalid";
}

extern "C" const char *RecordsDynamicFunctions::GetRecordEnchantmentId(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::ARMOR)
        return WorldstateFunctions::readWorldstate->armorRecords.at(index).data.mEnchant.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::BOOK)
        return WorldstateFunctions::readWorldstate->bookRecords.at(index).data.mEnchant.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        return WorldstateFunctions::readWorldstate->clothingRecords.at(index).data.mEnchant.c_str();
    else if (readRecordsType == mwmp::RECORD_TYPE::WEAPON)
        return WorldstateFunctions::readWorldstate->weaponRecords.at(index).data.mEnchant.c_str();

    return "invalid";
}

extern "C" int RecordsDynamicFunctions::GetRecordEnchantmentCharge(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::ARMOR)
        return WorldstateFunctions::readWorldstate->armorRecords.at(index).data.mData.mEnchant;
    else if (readRecordsType == mwmp::RECORD_TYPE::BOOK)
        return WorldstateFunctions::readWorldstate->bookRecords.at(index).data.mData.mEnchant;
    else if (readRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        return WorldstateFunctions::readWorldstate->clothingRecords.at(index).data.mData.mEnchant;
    else if (readRecordsType == mwmp::RECORD_TYPE::WEAPON)
        return WorldstateFunctions::readWorldstate->weaponRecords.at(index).data.mData.mEnchant;

    return -1;
}

extern "C" int RecordsDynamicFunctions::GetRecordAutoCalc(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mData.mAutoCalc;
    else if (readRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(index).data.mData.mAutocalc;

    return -1;
}

extern "C" int RecordsDynamicFunctions::GetRecordCharge(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(index).data.mData.mCharge;

    return -1;
}

extern "C" int RecordsDynamicFunctions::GetRecordCost(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(index).data.mData.mCost;
    else if (readRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        return WorldstateFunctions::readWorldstate->enchantmentRecords.at(index).data.mData.mCost;

    return -1;
}

extern "C" int RecordsDynamicFunctions::GetRecordFlags(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::SPELL)
        return WorldstateFunctions::readWorldstate->spellRecords.at(index).data.mData.mFlags;

    return -1;
}

extern "C" int RecordsDynamicFunctions::GetRecordValue(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mData.mValue;

    return -1;
}

extern "C" double RecordsDynamicFunctions::GetRecordWeight(unsigned int index) noexcept
{
    unsigned short readRecordsType = RecordsDynamicFunctions::GetRecordType();

    if (readRecordsType == mwmp::RECORD_TYPE::POTION)
        return WorldstateFunctions::readWorldstate->potionRecords.at(index).data.mData.mWeight;

    return -1;
}

extern "C" unsigned int RecordsDynamicFunctions::GetRecordEffectId(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mEffectID;
}

extern "C" int RecordsDynamicFunctions::GetRecordEffectAttribute(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mAttribute;
}

extern "C" int RecordsDynamicFunctions::GetRecordEffectSkill(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mSkill;
}

extern "C" unsigned int RecordsDynamicFunctions::GetRecordEffectRangeType(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mRange;
}

extern "C" int RecordsDynamicFunctions::GetRecordEffectArea(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mArea;
}

extern "C" int RecordsDynamicFunctions::GetRecordEffectDuration(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mDuration;
}

extern "C" int RecordsDynamicFunctions::GetRecordEffectMagnitudeMax(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mMagnMax;
}

extern "C" int RecordsDynamicFunctions::GetRecordEffectMagnitudeMin(unsigned int recordIndex, unsigned int effectIndex) noexcept
{
    return GetRecordEffects(recordIndex).mList.at(effectIndex).mMagnMin;
}

extern "C" void RecordsDynamicFunctions::SetRecordType(unsigned int type) noexcept
{
    WorldstateFunctions::writeWorldstate.recordsType = type;
}

extern "C" void RecordsDynamicFunctions::SetRecordId(const char* id) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mId = id;

    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set id for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordBaseId(const char* baseId) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.baseId = baseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.baseId = baseId;
    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set baseId for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordInventoryBaseId(const char* inventoryBaseId) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.inventoryBaseId = inventoryBaseId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.inventoryBaseId = inventoryBaseId;
    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set inventoryBaseId for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordSubtype(unsigned int subtype) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.data.mData.mType = subtype;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.data.mData.mType = subtype;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mData.mType = subtype;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mData.mType = subtype;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mData.mType = subtype;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mType = subtype;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set subtype for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasSubtype = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordName(const char* name) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mName = name;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mName = name;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set name for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasName = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordModel(const char* model) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mModel = model;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mModel = model;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set model for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasModel = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordIcon(const char* icon) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mIcon = icon;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mIcon = icon;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mIcon = icon;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mIcon = icon;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mIcon = icon;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mIcon = icon;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set icon for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasIcon = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordScript(const char* script) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mScript = script;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mScript = script;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set script for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasScript = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordEnchantmentId(const char* enchantmentId) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mEnchant = enchantmentId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mEnchant = enchantmentId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mEnchant = enchantmentId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mEnchant = enchantmentId;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set enchantment id for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasEnchantmentId = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordEnchantmentCharge(int enchantmentCharge) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mData.mEnchant = enchantmentCharge;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mData.mEnchant = enchantmentCharge;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mData.mEnchant = enchantmentCharge;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mEnchant = enchantmentCharge;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set enchantment charge for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasEnchantmentCharge = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordAutoCalc(int autoCalc) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mData.mAutoCalc = autoCalc;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.data.mData.mAutocalc = autoCalc;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
    {
        if (autoCalc)
        {
            tempNpc.data.mFlags |= ESM::NPC::Autocalc;
            tempNpc.data.mNpdtType = ESM::NPC::NPC_WITH_AUTOCALCULATED_STATS;
        }
        else
        {
            tempNpc.data.mFlags &= ~ESM::NPC::Autocalc;
            tempNpc.data.mNpdtType = ESM::NPC::NPC_DEFAULT;
        }
    }
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set autoCalc for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasAutoCalc = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordCharge(int charge) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.data.mData.mCharge = charge;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set charge for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasCharge = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordCost(int cost) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.data.mData.mCost = cost;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.data.mData.mCost = cost;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set cost for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasCost = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordFlags(int flags) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.data.mData.mFlags = flags;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mFlags = flags;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mFlags = flags;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mFlags = flags;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set flags for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasFlags = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordValue(int value) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mData.mValue = value;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mData.mValue = value;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mData.mValue = value;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mData.mValue = value;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mData.mValue = value;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mValue = value;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set value for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasValue = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordWeight(double weight) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mData.mWeight = weight;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mData.mWeight = weight;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mData.mWeight = weight;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mData.mWeight = weight;
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mData.mWeight = weight;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mWeight = weight;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set weight for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasWeight = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordArmorRating(int armorRating) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mData.mArmor = armorRating;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set armor rating for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasArmorRating = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordHealth(int health) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mData.mHealth = health;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mHealth = health;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mData.mHealth = health;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mNpdt.mHealth = health;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set health for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasHealth = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordDamageChop(unsigned int minDamage, unsigned int maxDamage) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
    {
        tempWeapon.data.mData.mChop[0] = minDamage;
        tempWeapon.data.mData.mChop[1] = maxDamage;
    }
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set chop damage for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasDamageChop = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordDamageSlash(unsigned int minDamage, unsigned int maxDamage) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
    {
        tempWeapon.data.mData.mSlash[0] = minDamage;
        tempWeapon.data.mData.mSlash[1] = maxDamage;
    }
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set slash damage for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasDamageSlash = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordDamageThrust(unsigned int minDamage, unsigned int maxDamage) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
    {
        tempWeapon.data.mData.mThrust[0] = minDamage;
        tempWeapon.data.mData.mThrust[1] = maxDamage;
    }
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set thrust damage for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasDamageThrust = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordReach(double reach) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mReach = reach;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set reach for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasReach = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordSpeed(double speed) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        tempWeapon.data.mData.mSpeed = speed;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set speed for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasSpeed = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordKeyState(bool keyState) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
        tempMiscellaneous.data.mData.mIsKey = keyState;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set key state for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasKeyState = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordScrollState(bool scrollState) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mData.mIsScroll = scrollState;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set scroll state for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasScrollState = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordSkillId(int skillId) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mData.mSkillId = skillId;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set skill id for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasSkillId = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordText(const char* text) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        tempBook.data.mText = text;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set text for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasText = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordHair(const char* hair) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mHair = hair;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set hair for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasHair = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordHead(const char* head) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mHead = head;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set head for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasHead = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordGender(unsigned int gender) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
    {
        tempNpc.data.setIsMale(gender);
    }
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set gender for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasGender = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordRace(const char* race) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mRace = race;
    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set race for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordClass(const char* charClass) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mClass = charClass;
    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set character class for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordFaction(const char* faction) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mFaction = faction;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set faction for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasFaction = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordLevel(int level) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mData.mLevel = level;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mNpdt.mLevel = level;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set level for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasLevel = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordMagicka(int magicka) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mData.mMana = magicka;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mNpdt.mMana = magicka;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set magicka for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasMagicka = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordFatigue(int fatigue) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mData.mFatigue = fatigue;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mNpdt.mFatigue = fatigue;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set fatigue for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasFatigue = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordAIFight(int aiFight) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.data.mAiData.mFight = aiFight;
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.data.mAiData.mFight = aiFight;
    else
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set AI fight for record type %i which lacks that property", writeRecordsType);
        return;
    }

    tempOverrides.hasAiFight = true;
}

extern "C" void RecordsDynamicFunctions::SetRecordIdByIndex(unsigned int index, const char* id) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        WorldstateFunctions::writeWorldstate.spellRecords.at(index).data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        WorldstateFunctions::writeWorldstate.potionRecords.at(index).data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        WorldstateFunctions::writeWorldstate.enchantmentRecords.at(index).data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        WorldstateFunctions::writeWorldstate.armorRecords.at(index).data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        WorldstateFunctions::writeWorldstate.bookRecords.at(index).data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        WorldstateFunctions::writeWorldstate.clothingRecords.at(index).data.mId = id;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        WorldstateFunctions::writeWorldstate.weaponRecords.at(index).data.mId = id;
    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set id for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordEnchantmentIdByIndex(unsigned int index, const char* enchantmentId) noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        WorldstateFunctions::writeWorldstate.armorRecords.at(index).data.mEnchant = enchantmentId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
        WorldstateFunctions::writeWorldstate.bookRecords.at(index).data.mEnchant = enchantmentId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        WorldstateFunctions::writeWorldstate.clothingRecords.at(index).data.mEnchant = enchantmentId;
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
        WorldstateFunctions::writeWorldstate.weaponRecords.at(index).data.mEnchant = enchantmentId;
    else
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Tried to set enchantmentId for record type %i which lacks that property", writeRecordsType);
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectId(unsigned int effectId) noexcept
{
    tempEffect.mEffectID = effectId;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectAttribute(int attributeId) noexcept
{
    tempEffect.mAttribute = attributeId;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectSkill(int skillId) noexcept
{
    tempEffect.mSkill = skillId;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectRangeType(unsigned int rangeType) noexcept
{
    tempEffect.mRange = rangeType;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectArea(int area) noexcept
{
    tempEffect.mArea = area;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectDuration(int duration) noexcept
{
    tempEffect.mDuration = duration;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectMagnitudeMax(int magnitudeMax) noexcept
{
    tempEffect.mMagnMax = magnitudeMax;
}

extern "C" void RecordsDynamicFunctions::SetRecordEffectMagnitudeMin(int magnitudeMin) noexcept
{
    tempEffect.mMagnMin = magnitudeMin;
}

extern "C" void RecordsDynamicFunctions::SetRecordBodyPartType(unsigned int partType) noexcept
{
    tempBodyPart.mPart = partType;
}

extern "C" void RecordsDynamicFunctions::SetRecordBodyPartIdForMale(const char* partId) noexcept
{
    tempBodyPart.mMale = partId;
}

extern "C" void RecordsDynamicFunctions::SetRecordBodyPartIdForFemale(const char* partId) noexcept
{
    tempBodyPart.mFemale = partId;
}

extern "C" void RecordsDynamicFunctions::SetRecordInventoryItemId(const char* itemId) noexcept
{
    tempInventoryItem.refId = itemId;
}

extern "C" void RecordsDynamicFunctions::SetRecordInventoryItemCount(unsigned int count) noexcept
{
    tempInventoryItem.count = count;
}

extern "C" void RecordsDynamicFunctions::AddRecord() noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
    {
        tempSpell.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.spellRecords.push_back(tempSpell);
        tempSpell = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
    {
        tempPotion.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.potionRecords.push_back(tempPotion);
        tempPotion = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
    {
        tempEnchantment.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.enchantmentRecords.push_back(tempEnchantment);
        tempEnchantment = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
    {
        tempCreature.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.creatureRecords.push_back(tempCreature);
        tempCreature = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
    {
        tempNpc.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.npcRecords.push_back(tempNpc);
        tempNpc = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
    {
        tempArmor.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.armorRecords.push_back(tempArmor);
        tempArmor = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::BOOK)
    {
        tempBook.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.bookRecords.push_back(tempBook);
        tempBook = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
    {
        tempClothing.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.clothingRecords.push_back(tempClothing);
        tempClothing = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::MISCELLANEOUS)
    {
        tempMiscellaneous.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.miscellaneousRecords.push_back(tempMiscellaneous);
        tempMiscellaneous = {};
    }
    else if (writeRecordsType == mwmp::RECORD_TYPE::WEAPON)
    {
        tempWeapon.baseOverrides = tempOverrides;
        WorldstateFunctions::writeWorldstate.weaponRecords.push_back(tempWeapon);
        tempWeapon = {};
    }

    tempOverrides = {};
}

extern "C" void RecordsDynamicFunctions::AddRecordEffect() noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::SPELL)
        tempSpell.data.mEffects.mList.push_back(tempEffect);
    else if (writeRecordsType == mwmp::RECORD_TYPE::POTION)
        tempPotion.data.mEffects.mList.push_back(tempEffect);
    else if (writeRecordsType == mwmp::RECORD_TYPE::ENCHANTMENT)
        tempEnchantment.data.mEffects.mList.push_back(tempEffect);

    tempOverrides.hasEffects = true;
    tempEffect = {};
}

extern "C" void RecordsDynamicFunctions::AddRecordBodyPart() noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::ARMOR)
        tempArmor.data.mParts.mParts.push_back(tempBodyPart);
    else if (writeRecordsType == mwmp::RECORD_TYPE::CLOTHING)
        tempClothing.data.mParts.mParts.push_back(tempBodyPart);

    tempOverrides.hasBodyParts = true;
    tempBodyPart = {};
}

extern "C" void RecordsDynamicFunctions::AddRecordInventoryItem() noexcept
{
    unsigned short writeRecordsType = WorldstateFunctions::writeWorldstate.recordsType;

    if (writeRecordsType == mwmp::RECORD_TYPE::CREATURE)
        tempCreature.inventory.push_back(tempInventoryItem);
    else if (writeRecordsType == mwmp::RECORD_TYPE::NPC)
        tempNpc.inventory.push_back(tempInventoryItem);

    tempOverrides.hasInventory = true;
    tempInventoryItem = {};
}

extern "C" void RecordsDynamicFunctions::SendRecordDynamic(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    WorldstateFunctions::writeWorldstate.guid = player->guid;

    mwmp::WorldstatePacket *packet = mwmp::Networking::get().getWorldstatePacketController()->GetPacket(ID_RECORD_DYNAMIC);
    packet->setWorldstate(&WorldstateFunctions::writeWorldstate);

    if (!skipAttachedPlayer)
        packet->Send(false);
    if (sendToOtherPlayers)
        packet->Send(true);
}
