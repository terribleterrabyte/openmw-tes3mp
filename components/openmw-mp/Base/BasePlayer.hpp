//
// Created by koncord on 07.01.16.
//

#ifndef OPENMW_BASEPLAYER_HPP
#define OPENMW_BASEPLAYER_HPP

#include <components/esm/loadcell.hpp>
#include <components/esm/loadcrea.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/esm/npcstats.hpp>
#include <components/esm/loadclas.hpp>
#include <components/esm/loadspel.hpp>
#include <components/esm/activespells.hpp>

#include <components/openmw-mp/Base/BaseStructs.hpp>
#include <components/openmw-mp/Base/BaseNetCreature.hpp>

#include <RakNetTypes.h>

namespace mwmp
{
    struct Chat
    {
        enum class Action: uint8_t {
            print = 0,
            clear,
            addchannel,
            setchannel,
            closechannel,
            renamechannel
        };
        unsigned channel;
        Action action;
        std::string message;
    };

    struct CurrentContainer
    {
        std::string refId;
        unsigned refNumIndex;
        unsigned mpNum;
        bool loot;
    };

    struct JournalItem
    {
        std::string quest;
        int index;
        enum class Type: uint8_t
        {
            Entry = 0,
            Index = 1
        };

        std::string actorRefId;

        Type type;
    };

    struct Faction
    {
        enum ChangesMask
        {
            Rank = 1,
            Expulsion = 2,
            Reputation = 4
        };

        inline bool isRankChanged() const { return (changes & ChangesMask::Rank) > 0; }
        inline bool isExpulsionChanged() const { return (changes & ChangesMask::Expulsion) > 0; }
        inline bool isReputationChanged() const { return (changes & ChangesMask::Reputation) > 0; }
        inline void rankChanged() { changes |= ChangesMask::Rank; };
        inline void expulsionChanged() { changes |= ChangesMask::Expulsion; };
        inline void reputationChanged() { changes |= ChangesMask::Reputation; };

        std::string factionId;
        int rank;
        int reputation;
        bool isExpelled;

        uint8_t changes = 0;
    };

    struct Topic
    {
        std::string topicId;
    };

    struct Kill
    {
        std::string refId;
        int number;
    };

    struct Book
    {
        std::string bookId;
    };

    struct QuickKey
    {
        std::string itemId;

        enum class Type: uint8_t
        {   
            Item = 0,
            Magic,
            MagicItem,
            Unassigned
        };

        unsigned short slot;
        Type type;
    };

    struct CellState
    {
        ESM::Cell cell;

        enum class Type: uint8_t
        {
            Load = 0,
            Unload
        };

        Type type;
    };

    struct JournalChanges
    {
        std::vector<JournalItem> journalItems;
    };

    struct FactionChanges
    {
        std::vector<Faction> factions;
    };

    struct TopicChanges
    {
        std::vector<Topic> topics;
    };

    struct KillChanges
    {
        std::vector<Kill> kills;
    };

    struct BookChanges
    {
        std::vector<Book> books;
    };

    struct MapChanges
    {
        std::vector<ESM::Cell> cellsExplored;
    };

    struct SpellbookChanges
    {
        std::vector<ESM::Spell> spells;

        enum class Type: int8_t
        {
            None = -1,
            Set = 0,
            Add,
            Remove
        };
        Type action;
    };

    struct QuickKeyChanges
    {
        std::vector<QuickKey> quickKeys;
    };

    struct CellStateChanges
    {
        std::vector<CellState> cellStates;
    };

    enum class ResurrectType : uint8_t
    {
        Regular = 0,
        ImperialShrine,
        TribunalTemple
    };

    enum class MiscellaneousChangeType : uint8_t
    {
        MarkLocation = 0,
        SelectedSpell
    };

    class BasePlayer : public mwmp::BaseNetCreature
    {
    public:

        struct CharGenState
        {
            int currentStage, endStage;
            bool isFinished;
        };

        struct GUIMessageBox
        {
            enum class Type: uint8_t
            {
                MessageBox = 0,
                CustomMessageBox,
                InputDialog,
                PasswordDialog,
                ListBox
            };

            uint64_t id;
            Type type;

            std::string label;
            std::string note;
            std::string buttons;

            std::string data;
        };

        struct GUIWindow
        {
            int32_t id;
            short width, height;
            enum class WidgetType: uint8_t
            {
                Button,
                Editbox,
                Label,
                ListBoxActive,
                ListBoxPassive,
                Slider
            };

            struct Widget
            {
                WidgetType type;
                std::string name;
                bool disabled;
                short posX, posY;
                short width, height;
                std::vector<std::string> data;
            };

            std::vector<Widget> widgets;
        };

        BasePlayer(RakNet::RakNetGUID guid) : guid(guid)
        {
            spellbookChanges.action = SpellbookChanges::Type::None;
            isWerewolf = false;
            exchangeFullInfo = false;
            displayCreatureName = false;
            resetStats = false;
            enforcedLogLevel = -1;
        }

        BasePlayer()
        {

        }

        ~BasePlayer()
        {

        }

        RakNet::RakNetGUID guid;
        GUIMessageBox guiMessageBox;
        int month;
        int day;
        GUIWindow guiWindow;
        double hour;

        // Track only the indexes of the attributes that have been changed,
        // with the attribute values themselves being stored in creatureStats.mAttributes
        std::vector<int> attributeIndexChanges;

        // Track only the indexes of the skills that have been changed,
        // with the skill values themselves being stored in npcStats.mSkills
        std::vector<int> skillIndexChanges;

        bool exchangeFullInfo;

        SpellbookChanges spellbookChanges;
        QuickKeyChanges quickKeyChanges;
        JournalChanges journalChanges;
        FactionChanges factionChanges;
        TopicChanges topicChanges;
        KillChanges killChanges;
        BookChanges bookChanges;
        MapChanges mapChanges;
        CellStateChanges cellStateChanges;

        ESM::ActiveSpells activeSpells;
        CurrentContainer currentContainer;

        struct
        {
            int currentWeather, nextWeather;
            float updateTime, transitionFactor;
        } weather;

        int difficulty;
        int enforcedLogLevel;
        float physicsFramerate;
        bool consoleAllowed;
        bool bedRestAllowed;
        bool wildernessRestAllowed;
        bool waitAllowed;

        bool ignorePosPacket;

        ESM::Position previousCellPosition;

        ESM::NPC npc;
        ESM::NpcStats npcStats;
        ESM::Creature creature;
        ESM::Class charClass;
        std::string birthsign;
        Chat chat;
        CharGenState charGenState;
        std::string passw;

        std::string sound;
        Animation animation;

        bool resetStats;
        float scale;
        bool isWerewolf;

        bool displayCreatureName;
        std::string creatureRefId;

        std::string deathReason;

        int jailDays;
        bool ignoreJailTeleportation;
        bool ignoreJailSkillIncreases;
        std::string jailProgressText;
        std::string jailEndText;

        ResurrectType resurrectType;
        MiscellaneousChangeType miscellaneousChangeType;

        ESM::Cell markCell;
        ESM::Position markPosition;
        std::string selectedSpellId;

        bool isReceivingQuickKeys;
        bool isPlayingAnimation;
        bool diedSinceArrestAttempt;
    };
}

#endif //OPENMW_BASEPLAYER_HPP
