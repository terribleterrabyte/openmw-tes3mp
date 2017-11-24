//
// Created by koncord on 05.01.16.
//

#include <components/openmw-mp/NetworkMessages.hpp>

#include "Networking.hpp"

#include "Player.hpp"
#include "Inventory.hpp"
#include "Settings.hpp"

using namespace std;

void Player::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Player>("Player",
                                         "getPosition", &NetActor::getPosition,
                                         "setPosition", &NetActor::setPosition,
                                         "getRotation", &NetActor::getRotation,
                                         "setRotation", &NetActor::setRotation,

                                         "getHealth", &NetActor::getHealth,
                                         "setHealth", &NetActor::setHealth,
                                         "getMagicka", &NetActor::getMagicka,
                                         "setMagicka", &NetActor::setMagicka,
                                         "getFatigue", &NetActor::getFatigue,
                                         "setFatigue", &NetActor::setFatigue,

                                         "getCell", &NetActor::getCell,
                                         "getInventory", &NetActor::getInventory,

                                         "getPreviousCellPos", &Player::getPreviousCellPos,

                                         "kick", &Player::kick,
                                         "ban", &Player::ban,
                                         "address", sol::property(&Player::getIP),

                                         "getAvgPing", &Player::getAvgPing,

                                         "message", &Player::message,
                                         "cleanChat", &Player::cleanChat,

                                         "pid", sol::readonly_property(&Player::id),
                                         "guid", sol::readonly_property(&Player::getGUID),

                                         "name", sol::property(&Player::getName, &Player::setName),
                                         "setCharGenStages", &Player::setCharGenStages,
                                         "level", sol::property(&Player::getLevel, &Player::setLevel),
                                         "gender", sol::property(&Player::getGender, &Player::setGender),
                                         "race", sol::property(&Player::getRace, &Player::setRace),
                                         "head", sol::property(&Player::getHead, &Player::setHead),
                                         "hair", sol::property(&Player::getHair, &Player::setHair),
                                         "birthsign", sol::property(&Player::getBirthsign, &Player::setBirthsign),
                                         "bounty", sol::property(&Player::getBounty, &Player::setBounty),
                                         "levelProgress", sol::property(&Player::getLevelProgress, &Player::setLevelProgress),
                                         "creatureModel", sol::property(&Player::getCreatureModel, &Player::setCreatureModel),
                                         "isCreatureName",  sol::property(&Player::isCreatureName, &Player::creatureName),

                                         "resurrect", &Player::resurrect,
                                         "jail", &Player::jail,
                                         "werewolf",  sol::property(&Player::getWerewolfState, &Player::setWerewolfState),

                                         "getAttribute", &Player::getAttribute,
                                         "setAttribute", &Player::setAttribute,

                                         "getSkill", &Player::getSkill,
                                         "setSkill", &Player::setSkill,

                                         "getSkillIncrease", &Player::getSkillIncrease,
                                         "setSkillIncrease", &Player::setSkillIncrease,

                                         "getClass", &Player::getCharClass,
                                         "getSettings", &Player::getSettings,
                                         "getBooks", &Player::getBooks,
                                         "getGUI", &Player::getGUI,
                                         "getDialogue", &Player::getDialogue,
                                         "getFactions", &Player::getFactions,
                                         "getQuests", &Player::getQuests,
                                         "getSpells", &Player::getSpells,

                                         "getCellState", &Player::getCellState,
                                         "cellStateSize", &Player::cellStateSize,
                                         "addCellExplored", &Player::addCellExplored,
                                         "setAuthority", &Player::setAuthority,
                                         "customData", &Player::customData
    );
}

Player::Player(RakNet::RakNetGUID guid) : BasePlayer(guid), NetActor(), changedMap(false), cClass(this),
                                          settings(this), books(this), gui(this), dialogue(this), factions(this),
                                          quests(this), spells(this)
{
    basePlayer = this;
    netCreature = this;
    printf("Player::Player()\n");
    handshakeState = false;
    loadState = NOTLOADED;
    resetUpdateFlags();
    cell.blank();
    npc.blank();
    npcStats.blank();
    creatureStats.blank();
    charClass.blank();
    customData = mwmp::Networking::get().getState().getState()->create_table();
}

Player::~Player()
{
    printf("Player::~Player()\n");
    CellController::get()->deletePlayer(this);
}

void Player::update()
{
    auto plPCtrl = mwmp::Networking::get().getPlayerPacketController();

    if (baseInfoChanged)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_BASEINFO);
        packet->setPlayer(basePlayer);
        packet->Send(false);
        packet->Send(true);
    }

    // Make sure we send a cell change before we send the position so the position isn't overridden
    if (cellAPI.isChangedCell())
    {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_CELL_CHANGE);
        packet->setPlayer(this);
        packet->Send(/*toOthers*/ false);
        cellAPI.resetChangedCell();
    }

    if (positionChanged)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_POSITION);
        packet->setPlayer(basePlayer);
        packet->Send(false);
    }

    // The character class can override values from below on the client, so send it first
    cClass.update();

    if (levelChanged)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_LEVEL);
        packet->setPlayer(basePlayer);
        packet->Send(false);
        packet->Send(true);
    }

    if (statsChanged)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_STATS_DYNAMIC);
        packet->setPlayer(basePlayer);
        packet->Send(false);
        packet->Send(true);
    }

    if (attributesChanged)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_ATTRIBUTE);
        packet->setPlayer(basePlayer);
        packet->Send(false);
        packet->Send(true);

        attributeChanges.attributeIndexes.clear();
    }

    if (skillsChanged)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_SKILL);
        packet->setPlayer(basePlayer);
        packet->Send(false);
        packet->Send(true);

        skillChanges.skillIndexes.clear();
    }

    if (inventory.isEquipmentChanged())
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_EQUIPMENT);
        packet->setPlayer(this);
        packet->Send(false);
        packet->Send(true);
        inventory.resetEquipmentFlag();
    }

    if (inventory.inventoryChangeType() != 0)
    {
        auto packet = plPCtrl->GetPacket(ID_PLAYER_INVENTORY);
        packet->setPlayer(this);
        packet->Send(/*toOthers*/ false);
        inventory.resetInventoryFlag();
    }

    if (changedMap)
    {
        auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_MAP);
        packet->setPlayer(this);
        packet->Send(/*toOthers*/ false);
        changedMap = false;
    }

    settings.update();
    books.update();
    gui.update();
    dialogue.update();
    factions.update();
    quests.update();
    spells.update();

    resetUpdateFlags();
}

unsigned short Player::getId()
{
    return id;
}

void Player::setId(unsigned short id)
{
    this->id = id;
}

bool Player::isHandshaked()
{
    return handshakeState;
}

void Player::setHandshake()
{
    handshakeState = true;
}

int Player::getLoadState()
{
    return loadState;
}

void Player::setLoadState(int state)
{
    loadState = state;
}

CellController::TContainer *Player::getCells()
{
    return &cells;
}

void Player::forEachLoaded(std::function<void(Player *pl, Player *other)> func)
{
    std::list <Player*> plList;

    for (auto &&cell : cells)
    {
        for (auto &&pl : *cell)
        {
            if (pl != nullptr && !pl->npc.mName.empty())
                plList.push_back(pl);
        }
    }

    plList.sort();
    plList.unique();

    for (auto &&pl : plList)
    {
        if (pl == this) continue;
        func(this, pl);
    }
}

void Player::sendToLoaded(mwmp::PlayerPacket *myPacket)
{
    std::list <Player*> plList;

    for (auto cell : cells)
        for (auto pl : *cell)
            plList.push_back(pl);

    plList.sort();
    plList.unique();

    for (auto pl : plList)
    {
        if (pl == this) continue;
        myPacket->setPlayer(this);
        myPacket->Send(pl->guid);
    }
}

void Player::kick() const
{
    mwmp::Networking::getPtr()->kickPlayer(guid);
}

void Player::ban() const
{
    auto netCtrl = mwmp::Networking::getPtr();
    RakNet::SystemAddress addr = netCtrl->getSystemAddress(guid);
    netCtrl->banAddress(addr.ToString(false));
}

void Player::cleanChat()
{
    chatMessage.clear();

    auto packet = mwmp::Networking::get().getPlayerPacketController();
    packet->GetPacket(ID_CHAT_MESSAGE)->setPlayer(this);
    packet->GetPacket(ID_CHAT_MESSAGE)->Send(false);
}

std::string Player::getIP() const
{
    RakNet::SystemAddress addr = mwmp::Networking::getPtr()->getSystemAddress(guid);
    return addr.ToString(false);
}

int Player::getAvgPing()
{
    return mwmp::Networking::get().getAvgPing(guid);
}

std::string Player::getName()
{
    return npc.mName;
}

void Player::setName(const std::string &name)
{
    npc.mName = name;
    baseInfoChanged = true;
}

void Player::setCharGenStages(int currentStage, int endStage)
{
    charGenState.currentStage = currentStage;
    charGenState.endStage = endStage;
    charGenState.isFinished = false;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_CHARGEN);
    packet->setPlayer(this);
    packet->Send(false);
}

void Player::message(const std::string &message, bool toAll)
{
   chatMessage = message;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_CHAT_MESSAGE);
    packet->setPlayer(this);

    packet->Send(false);
    if (toAll)
        packet->Send(true);
}

int Player::getLevel() const
{
    return creatureStats.mLevel;
}

void Player::setLevel(int level)
{
    creatureStats.mLevel = level;
    levelChanged = true;
}

int Player::getGender() const
{
    return npc.isMale();
}

void Player::setGender(int gender)
{
    npc.setIsMale(gender);
    baseInfoChanged = true;
}

std::string Player::getRace() const
{
    return npc.mRace;
}

void Player::setRace(const std::string &race)
{
    LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Setting race for %s: %s -> %s", npc.mName.c_str(), npc.mRace.c_str(), race.c_str());

    npc.mRace = race;
    baseInfoChanged = true;
}

std::string Player::getHead() const
{
    return npc.mHead;
}

void Player::setHead(const std::string &head)
{
    npc.mHead = head;
    baseInfoChanged = true;
}

std::string Player::getHair() const
{
    return npc.mHair;
}

void Player::setHair(const std::string &hair)
{
    npc.mHair = hair;
    baseInfoChanged = true;
}

std::string Player::getBirthsign() const
{
    return birthsign;
}

void Player::setBirthsign(const std::string &sign)
{
    birthsign = sign;
    baseInfoChanged = true;
}

int Player::getBounty() const
{
    return npcStats.mBounty;
}

void Player::setBounty(int bounty)
{
    npcStats.mBounty = bounty;
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_BOUNTY);
    packet->setPlayer(this);
    packet->Send(false);
    packet->Send(true);
}

int Player::getLevelProgress() const
{
    return npcStats.mLevelProgress;
}

void Player::setLevelProgress(int progress)
{
    npcStats.mLevelProgress = progress;
    levelChanged = true;
}

std::string Player::getCreatureModel() const
{
    return creatureModel;
}

void Player::setCreatureModel(const std::string &model)
{
    creatureModel = model;
    baseInfoChanged = true;
}

void Player::creatureName(bool useName)
{
    useCreatureName = useName;
    baseInfoChanged = true;
}

bool Player::isCreatureName() const
{
    return useCreatureName;
}

std::tuple<int, int> Player::getAttribute(unsigned short id) const
{
    if (id >= ESM::Attribute::Length)
        return make_tuple(0, 0);

    return make_tuple(creatureStats.mAttributes[id].mBase, creatureStats.mAttributes[id].mCurrent);
}

void Player::setAttribute(unsigned short id, int base, int current)
{
    if (id >= ESM::Attribute::Length)
        return;

    creatureStats.mAttributes[id].mBase = base;
    creatureStats.mAttributes[id].mCurrent = current;

    if (std::find(attributeChanges.attributeIndexes.begin(), attributeChanges.attributeIndexes.end(), id) == attributeChanges.attributeIndexes.end())
        attributeChanges.attributeIndexes.push_back(id);

    attributesChanged = true;
}

std::tuple<int, int, float> Player::getSkill(unsigned short id) const
{
    if (id >= ESM::Skill::Length)
        return make_tuple(0, 0, 0.0f);

    const auto &skill = npcStats.mSkills[id];

    return make_tuple(skill.mBase, skill.mCurrent, skill.mProgress);
}

void Player::setSkill(unsigned short id, int base, int current, float progress)
{
    if (id >= ESM::Skill::Length)
        return;

    auto &skill = npcStats.mSkills[id];
    skill.mBase = base;
    skill.mCurrent = current;
    skill.mProgress = progress;

    skillChanges.skillIndexes.push_back(id);

    skillsChanged = true;
}

int Player::getSkillIncrease(unsigned short attributeId) const
{
    return npcStats.mSkillIncrease[attributeId];
}

void Player::setSkillIncrease(unsigned short attributeId, int increase)
{
    if (attributeId >= ESM::Attribute::Length)
        return;

    npcStats.mSkillIncrease[attributeId] = increase;

    if (std::find(attributeChanges.attributeIndexes.begin(), attributeChanges.attributeIndexes.end(), attributeId) == attributeChanges.attributeIndexes.end())
        attributeChanges.attributeIndexes.push_back(attributeId);

    attributesChanged = true;
}

CharClass &Player::getCharClass(sol::this_state thisState)
{
    return cClass;
}

GameSettings &Player::getSettings()
{
    return settings;
}

Books &Player::getBooks()
{
    return books;
}

GUI &Player::getGUI()
{
    return gui;
}

Dialogue &Player::getDialogue()
{
    return dialogue;
}

Factions &Player::getFactions()
{
    return factions;
}

Quests &Player::getQuests()
{
    return quests;
}

Spells &Player::getSpells()
{
    return spells;
}

std::tuple<float, float, float> Player::getPreviousCellPos() const
{
    return make_tuple(previousCellPosition.pos[0], previousCellPosition.pos[1], previousCellPosition.pos[2]);
}

void Player::resurrect(unsigned int type)
{
    resurrectType = type;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_RESURRECT);
    packet->setPlayer(this);
    packet->Send(false);
    packet->Send(true);
}

void Player::jail(int jailDays, bool ignoreJailTeleportation, bool ignoreJailSkillIncreases,
                  const std::string &jailProgressText, const std::string &jailEndText)
{
    this->jailDays = jailDays;
    this->ignoreJailTeleportation = ignoreJailTeleportation;
    this->ignoreJailSkillIncreases = ignoreJailSkillIncreases;
    this->jailProgressText = jailProgressText;
    this->jailEndText = jailEndText;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_JAIL);
    packet->setPlayer(this);
    packet->Send(false);
}

bool Player::getWerewolfState() const
{
    return isWerewolf;
}

void Player::setWerewolfState(bool state)
{
    isWerewolf = state;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_SHAPESHIFT);
    packet->setPlayer(this);
    packet->Send(false);
    packet->Send(true);
}

size_t Player::cellStateSize() const
{
    return cellStateChanges.cellStates.size();
}

void Player::addCellExplored(const std::string &cellDescription)
{
    auto cellExplored = Utils::getCellFromDescription(cellDescription);
    mapChanges.cellsExplored.push_back(cellExplored);
    changedMap = true;
}

CellState Player::getCellState(int i)
{
    return CellState(cellStateChanges.cellStates.at(i));
}

void Player::setAuthority()
{
    mwmp::BaseActorList writeActorList;
    writeActorList.cell = cell;
    writeActorList.guid = guid;

    Cell *serverCell = CellController::get()->getCell(&cell);
    if (serverCell != nullptr)
    {
        serverCell->setAuthority(guid);

        mwmp::ActorPacket *authorityPacket = mwmp::Networking::get().getActorPacketController()->GetPacket(ID_ACTOR_AUTHORITY);
        authorityPacket->setActorList(&writeActorList);
        authorityPacket->Send(writeActorList.guid);

        // Also send this to everyone else who has the cell loaded
        serverCell->sendToLoaded(authorityPacket, &writeActorList);
    }
}
