#ifndef OPENMW_MECHANICSAPI_HPP
#define OPENMW_MECHANICSAPI_HPP

#include "../Types.hpp"

#define MECHANICSAPI \
    {"GetMiscellaneousChangeType", MechanicsFunctions::GetMiscellaneousChangeType},\
    \
    {"GetMarkCell",                 MechanicsFunctions::GetMarkCell},\
    {"GetMarkPosX",                 MechanicsFunctions::GetMarkPosX},\
    {"GetMarkPosY",                 MechanicsFunctions::GetMarkPosY},\
    {"GetMarkPosZ",                 MechanicsFunctions::GetMarkPosZ},\
    {"GetMarkRotX",                 MechanicsFunctions::GetMarkRotX},\
    {"GetMarkRotZ",                 MechanicsFunctions::GetMarkRotZ},\
    {"GetSelectedSpellId",          MechanicsFunctions::GetSelectedSpellId},\
    \
    {"DoesPlayerHavePlayerKiller",  MechanicsFunctions::DoesPlayerHavePlayerKiller},\
    {"GetPlayerKillerPid",          MechanicsFunctions::GetPlayerKillerPid},\
    {"GetPlayerKillerRefId",        MechanicsFunctions::GetPlayerKillerRefId},\
    {"GetPlayerKillerRefNum",       MechanicsFunctions::GetPlayerKillerRefNum},\
    {"GetPlayerKillerMpNum",        MechanicsFunctions::GetPlayerKillerMpNum},\
    {"GetPlayerKillerName",         MechanicsFunctions::GetPlayerKillerName},\
    \
    {"GetDrawState",                MechanicsFunctions::GetDrawState},\
    {"GetSneakState",               MechanicsFunctions::GetSneakState},\
    \
    {"SetMarkCell",                 MechanicsFunctions::SetMarkCell},\
    {"SetMarkPos",                  MechanicsFunctions::SetMarkPos},\
    {"SetMarkRot",                  MechanicsFunctions::SetMarkRot},\
    {"SetSelectedSpellId",          MechanicsFunctions::SetSelectedSpellId},\
    \
    {"SendMarkLocation",            MechanicsFunctions::SendMarkLocation},\
    {"SendSelectedSpell",           MechanicsFunctions::SendSelectedSpell},\
    \
    {"Jail",                        MechanicsFunctions::Jail},\
    {"Resurrect",                   MechanicsFunctions::Resurrect},\
    \
    {"GetDeathReason",              MechanicsFunctions::GetDeathReason},\
    {"GetPlayerKillerRefNumIndex",  MechanicsFunctions::GetPlayerKillerRefNumIndex}

namespace MechanicsFunctions
{
    /**
    * \brief Get the type of a PlayerMiscellaneous packet.
    *
    * \param pid The player ID.
    * \return The type.
    */
    extern "C" unsigned char GetMiscellaneousChangeType(unsigned short pid) noexcept;

    /**
    * \brief Get the cell description of a player's Mark cell.
    *
    * \param pid The player ID.
    * \return The cell description.
    */
    extern "C" const char *GetMarkCell(unsigned short pid) noexcept;

    /**
    * \brief Get the X position of a player's Mark.
    *
    * \param pid The player ID.
    * \return The X position.
    */
    extern "C" double GetMarkPosX(unsigned short pid) noexcept;

    /**
    * \brief Get the Y position of a player's Mark.
    *
    * \param pid The player ID.
    * \return The Y position.
    */
    extern "C" double GetMarkPosY(unsigned short pid) noexcept;

    /**
    * \brief Get the Z position of a player's Mark.
    *
    * \param pid The player ID.
    * \return The Z position.
    */
    extern "C" double GetMarkPosZ(unsigned short pid) noexcept;

    /**
    * \brief Get the X rotation of a player's Mark.
    *
    * \param pid The player ID.
    * \return The X rotation.
    */
    extern "C" double GetMarkRotX(unsigned short pid) noexcept;

    /**
    * \brief Get the Z rotation of a player's Mark.
    *
    * \param pid The player ID.
    * \return The X rotation.
    */
    extern "C" double GetMarkRotZ(unsigned short pid) noexcept;

    /**
    * \brief Get the ID of a player's selected spell.
    *
    * \param pid The player ID.
    * \return The spell ID.
    */
    extern "C" const char *GetSelectedSpellId(unsigned short pid) noexcept;

    /**
    * \brief Check whether the killer of a certain player is also a player.
    *
    * \param pid The player ID of the killed player.
    * \return Whether the player was killed by another player.
    */
    extern "C" bool DoesPlayerHavePlayerKiller(unsigned short pid) noexcept;

    /**
    * \brief Get the player ID of the killer of a certain player.
    *
    * \param pid The player ID of the killed player.
    * \return The player ID of the killer.
    */
    extern "C" int GetPlayerKillerPid(unsigned short pid) noexcept;

    /**
    * \brief Get the refId of the actor killer of a certain player.
    *
    * \param pid The player ID of the killed player.
    * \return The refId of the killer.
    */
    extern "C" const char *GetPlayerKillerRefId(unsigned short pid) noexcept;

    /**
    * \brief Get the refNum of the actor killer of a certain player.
    *
    * \param pid The player ID of the killed player.
    * \return The refNum of the killer.
    */
    extern "C" unsigned int GetPlayerKillerRefNum(unsigned short pid) noexcept;

    /**
    * \brief Get the mpNum of the actor killer of a certain player.
    *
    * \param pid The player ID of the killed player.
    * \return The mpNum of the killer.
    */
    extern "C" unsigned int GetPlayerKillerMpNum(unsigned short pid) noexcept;

    /**
    * \brief Get the name of the actor killer of a certain player.
    *
    * \param pid The player ID of the killed player.
    * \return The name of the killer.
    */
    extern "C" const char *GetPlayerKillerName(unsigned short pid) noexcept;

    /**
    * \brief Get the draw state of a player (0 for nothing, 1 for drawn weapon,
    *        2 for drawn spell).
    *
    * \param pid The player ID.
    * \return The draw state.
    */
    extern "C" unsigned int GetDrawState(unsigned short pid) noexcept;

    /**
    * \brief Get the sneak state of a player.
    *
    * \param pid The player ID.
    * \return Whether the player is sneaking.
    */
    extern "C" bool GetSneakState(unsigned short pid) noexcept;

    /**
    * \brief Set the Mark cell of a player.
    *
    * This changes the Mark cell recorded for that player in the server memory, but does not by itself
    * send a packet.
    *
    * The cell is determined to be an exterior cell if it fits the pattern of a number followed
    * by a comma followed by another number.
    *
    * \param pid The player ID.
    * \param cellDescription The cell description.
    * \return void
    */
    extern "C" void SetMarkCell(unsigned short pid, const char *cellDescription) noexcept;

    /**
    * \brief Set the Mark position of a player.
    *
    * This changes the Mark positional coordinates recorded for that player in the server memory, but
    * does not by itself send a packet.
    *
    * \param pid The player ID.
    * \param x The X position.
    * \param y The Y position.
    * \param z The Z position.
    * \return void
    */
    extern "C" void SetMarkPos(unsigned short pid, double x, double y, double z) noexcept;

    /**
    * \brief Set the Mark rotation of a player.
    *
    * This changes the Mark positional coordinates recorded for that player in the server memory, but
    * does not by itself send a packet.
    *
    * \param pid The player ID.
    * \param x The X rotation.
    * \param z The Z rotation.
    * \return void
    */
    extern "C" void SetMarkRot(unsigned short pid, double x, double z) noexcept;

    /**
    * \brief Set the ID of a player's selected spell.
    *
    * This changes the spell ID recorded for that player in the server memory, but does not by itself
    * send a packet.
    *
    * \param pid The player ID.
    * \param spellId The spell ID.
    * \return void
    */
    extern "C" void SetSelectedSpellId(unsigned short pid, const char *spellId) noexcept;

    /**
    * \brief Send a PlayerMiscellaneous packet with a Mark location to a player.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendMarkLocation(unsigned short pid);

    /**
    * \brief Send a PlayerMiscellaneous packet with a selected spell ID to a player.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendSelectedSpell(unsigned short pid);

    /**
    * \brief Send a PlayerJail packet about a player.
    *
    * This is similar to the player being jailed by a guard, but provides extra parameters for
    * increased flexibility.
    *
    * It is only sent to the player being jailed, as the other players will be informed of the
    * jailing's actual consequences via other packets sent by the affected client.
    *
    * \param pid The player ID.
    * \param jailDays The number of days to spend jailed, where each day affects one skill point.
    * \param ignoreJailTeleportation Whether the player being teleported to the nearest jail
    *                                marker should be overridden.
    * \param ignoreJailSkillIncrease Whether the player's Sneak and Security skills should be
    *                                prevented from increasing as a result of the jailing,
    *                                overriding default behavior.
    * \param jailProgressText The text that should be displayed while jailed.
    * \param jailEndText The text that should be displayed once the jailing period is over.
    * \return void
    */
    extern "C" void Jail(unsigned short pid, int jailDays, bool ignoreJailTeleportation, bool ignoreJailSkillIncreases,
                     const char* jailProgressText, const char* jailEndText) noexcept;

    /**
    * \brief Send a PlayerResurrect packet about a player.
    *
    * This sends the packet to all players connected to the server.
    *
    * \param pid The player ID.
    * \param type The type of resurrection (0 for REGULAR, 1 for IMPERIAL_SHRINE,
    *             2 for TRIBUNAL_TEMPLE).
    * \return void
    */
    extern "C" void Resurrect(unsigned short pid, unsigned int type) noexcept;

    // All methods below are deprecated versions of methods from above

    extern "C" const char *GetDeathReason(unsigned short pid) noexcept;
    extern "C" unsigned int GetPlayerKillerRefNumIndex(unsigned short pid) noexcept;
}

#endif //OPENMW_MECHANICSAPI_HPP
