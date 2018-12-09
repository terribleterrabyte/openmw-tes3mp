#ifndef SCRIPTFUNCTIONS_HPP
#define SCRIPTFUNCTIONS_HPP

#include <Script/Functions/Actors.hpp>
#include <Script/Functions/Books.hpp>
#include <Script/Functions/Cells.hpp>
#include <Script/Functions/CharClass.hpp>
#include <Script/Functions/Chat.hpp>
#include <Script/Functions/Dialogue.hpp>
#include <Script/Functions/Factions.hpp>
#include <Script/Functions/GUI.hpp>
#include <Script/Functions/Items.hpp>
#include <Script/Functions/Mechanics.hpp>
#include <Script/Functions/Miscellaneous.hpp>
#include <Script/Functions/Objects.hpp>
#include <Script/Functions/Positions.hpp>
#include <Script/Functions/Public.hpp>
#include <Script/Functions/Quests.hpp>
#include <Script/Functions/RecordsDynamic.hpp>
#include <Script/Functions/Shapeshift.hpp>
#include <Script/Functions/Server.hpp>
#include <Script/Functions/Settings.hpp>
#include <Script/Functions/Spells.hpp>
#include <Script/Functions/Stats.hpp>
#include <Script/Functions/Timer.hpp>
#include <Script/Functions/Worldstate.hpp>
#include <RakNetTypes.h>
#include <tuple>
#include <apps/openmw-mp/Player.hpp>
#include "ScriptFunction.hpp"
#include "Types.hpp"

#include <components/openmw-mp/Log.hpp>

#define GET_PLAYER(pid, pl, retvalue) \
     pl = Players::getPlayer(pid); \
     if (player == 0) {\
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "%s: Player with pid \'%d\' not found\n", __PRETTY_FUNCTION__, pid);\
        /*ScriptFunctions::StopServer(1);*/ \
        return retvalue;\
}


class ScriptFunctions
{
public:
    static void GetArguments(std::vector<boost::any> &params, va_list args, const std::string &def);

    static constexpr ScriptFunctionData functions[]{
            {"CreateTimer",         TimerFunctions::CreateTimer},
            {"CreateTimerEx",       reinterpret_cast<Function<void>>(TimerFunctions::CreateTimerEx)},
            {"MakePublic",          PublicFunctions::MakePublic},
            {"CallPublic",          reinterpret_cast<Function<void>>(PublicFunctions::CallPublic)},

            {"StartTimer",          TimerFunctions::StartTimer},
            {"StopTimer",           TimerFunctions::StopTimer},
            {"RestartTimer",        TimerFunctions::RestartTimer},
            {"FreeTimer",           TimerFunctions::FreeTimer},
            {"IsTimerElapsed",      TimerFunctions::IsTimerElapsed},

            ACTORAPI,
            BOOKAPI,
            CELLAPI,
            CHARCLASSAPI,
            CHATAPI,
            DIALOGUEAPI,
            FACTIONAPI,
            GUIAPI,
            ITEMAPI,
            MECHANICSAPI,
            MISCELLANEOUSAPI,
            POSITIONAPI,
            QUESTAPI,
            RECORDSDYNAMICAPI,
            SHAPESHIFTAPI,
            SERVERAPI,
            SETTINGSAPI,
            SPELLAPI,
            STATAPI,
            OBJECTAPI,
            WORLDSTATEAPI
    };

    static constexpr ScriptCallbackData callbacks[]{
            {"OnServerInit",             Callback<>()},
            {"OnServerPostInit",         Callback<>()},
            {"OnServerExit",             Callback<bool>()},
            {"OnPlayerConnect",          Callback<unsigned short>()},
            {"OnPlayerDisconnect",       Callback<unsigned short>()},
            {"OnPlayerDeath",            Callback<unsigned short>()},
            {"OnPlayerResurrect",        Callback<unsigned short>()},
            {"OnPlayerCellChange",       Callback<unsigned short>()},
            {"OnPlayerAttribute",        Callback<unsigned short>()},
            {"OnPlayerSkill",            Callback<unsigned short>()},
            {"OnPlayerLevel",            Callback<unsigned short>()},
            {"OnPlayerBounty",           Callback<unsigned short>()},
            {"OnPlayerReputation",       Callback<unsigned short>()},
            {"OnPlayerEquipment",        Callback<unsigned short>()},
            {"OnPlayerInventory",        Callback<unsigned short>()},
            {"OnPlayerJournal",          Callback<unsigned short>()},
            {"OnPlayerFaction",          Callback<unsigned short>()},
            {"OnPlayerShapeshift",       Callback<unsigned short>()},
            {"OnPlayerSpellbook",        Callback<unsigned short>()},
            {"OnPlayerQuickKeys",        Callback<unsigned short>()},
            {"OnPlayerTopic",            Callback<unsigned short>()},
            {"OnPlayerDisposition",      Callback<unsigned short>()},
            {"OnPlayerBook",             Callback<unsigned short>()},
            {"OnPlayerItemUse",          Callback<unsigned short>()},
            {"OnPlayerMiscellaneous",    Callback<unsigned short>()},
            {"OnPlayerInput",            Callback<unsigned short>()},
            {"OnPlayerRest",             Callback<unsigned short>()},
            {"OnRecordDynamic",          Callback<unsigned short>()},
            {"OnCellLoad",               Callback<unsigned short, const char*>()},
            {"OnCellUnload",             Callback<unsigned short, const char*>()},
            {"OnCellDeletion",           Callback<const char*>()},
            {"OnContainer",              Callback<unsigned short, const char*>()},
            {"OnDoorState",              Callback<unsigned short, const char*>()},
            {"OnObjectActivate",         Callback<unsigned short, const char*>()},
            {"OnObjectPlace",            Callback<unsigned short, const char*>()},
            {"OnObjectState",            Callback<unsigned short, const char*>()},
            {"OnObjectSpawn",            Callback<unsigned short, const char*>()},
            {"OnObjectDelete",           Callback<unsigned short, const char*>()},
            {"OnObjectLock",             Callback<unsigned short, const char*>()},
            {"OnObjectScale",            Callback<unsigned short, const char*>()},
            {"OnObjectTrap",             Callback<unsigned short, const char*>()},
            {"OnVideoPlay",              Callback<unsigned short, const char*>()},
            {"OnActorList",              Callback<unsigned short, const char*>()},
            {"OnActorEquipment",         Callback<unsigned short, const char*>()},
            {"OnActorAI",                Callback<unsigned short, const char*>()},
            {"OnActorDeath",             Callback<unsigned short, const char*>()},
            {"OnActorCellChange",        Callback<unsigned short, const char*>()},
            {"OnActorTest",              Callback<unsigned short, const char*>()},
            {"OnPlayerSendMessage",      Callback<unsigned short, const char*>()},
            {"OnPlayerEndCharGen",       Callback<unsigned short>()},
            {"OnGUIAction",              Callback<unsigned short, int, const char*>()},
            {"OnWorldKillCount",         Callback<unsigned short>()},
            {"OnWorldMap",               Callback<unsigned short>()},
            {"OnWorldWeather",           Callback<unsigned short>() },
            {"OnMpNumIncrement",         Callback<int>()},
            {"OnRequestPluginList",      Callback<>()}
    };
};

#endif //SCRIPTFUNCTIONS_HPP
