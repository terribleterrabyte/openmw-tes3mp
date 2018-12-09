#ifndef OPENMW_FACTIONAPI_HPP
#define OPENMW_FACTIONAPI_HPP

#define FACTIONAPI \
    {"ClearFactionChanges",      FactionFunctions::ClearFactionChanges},\
    \
    {"GetFactionChangesSize",    FactionFunctions::GetFactionChangesSize},\
    {"GetFactionChangesAction",  FactionFunctions::GetFactionChangesAction},\
    \
    {"GetFactionId",             FactionFunctions::GetFactionId},\
    {"GetFactionRank",           FactionFunctions::GetFactionRank},\
    {"GetFactionExpulsionState", FactionFunctions::GetFactionExpulsionState},\
    {"GetFactionReputation",     FactionFunctions::GetFactionReputation},\
    \
    {"SetFactionChangesAction",  FactionFunctions::SetFactionChangesAction},\
    {"SetFactionId",             FactionFunctions::SetFactionId},\
    {"SetFactionRank",           FactionFunctions::SetFactionRank},\
    {"SetFactionExpulsionState", FactionFunctions::SetFactionExpulsionState},\
    {"SetFactionReputation",     FactionFunctions::SetFactionReputation},\
    \
    {"AddFaction",               FactionFunctions::AddFaction},\
    \
    {"SendFactionChanges",       FactionFunctions::SendFactionChanges},\
    \
    {"InitializeFactionChanges", FactionFunctions::InitializeFactionChanges}

namespace FactionFunctions
{
    /**
    * \brief Clear the last recorded faction changes for a player.
    *
    * This is used to initialize the sending of new PlayerFaction packets.
    *
    * \param pid The player ID whose faction changes should be used.
    * \return void
    */
    extern "C" void ClearFactionChanges(unsigned short pid) noexcept;

    /**
    * \brief Get the number of indexes in a player's latest faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \return The number of indexes.
    */
    extern "C" unsigned int GetFactionChangesSize(unsigned short pid) noexcept;

    /**
    * \brief Get the action type used in a player's latest faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \return The action type (0 for RANK, 1 for EXPULSION, 2 for REPUTATION).
    */
    extern "C" unsigned char GetFactionChangesAction(unsigned short pid) noexcept;

    /**
    * \brief Get the factionId at a certain index in a player's latest faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \param index The index of the faction.
    * \return The factionId.
    */
    extern "C" const char *GetFactionId(unsigned short pid, unsigned int index) noexcept;

    /**
    * \brief Get the rank at a certain index in a player's latest faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \param index The index of the faction.
    * \return The rank.
    */
    extern "C" int GetFactionRank(unsigned short pid, unsigned int index) noexcept;

    /**
    * \brief Get the expulsion state at a certain index in a player's latest faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \param index The index of the faction.
    * \return The expulsion state.
    */
    extern "C" bool GetFactionExpulsionState(unsigned short pid, unsigned int index) noexcept;

    /**
    * \brief Get the reputation at a certain index in a player's latest faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \param index The index of the faction.
    * \return The reputation.
    */
    extern "C" int GetFactionReputation(unsigned short pid, unsigned int index) noexcept;

    /**
    * \brief Set the action type in a player's faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \param action The action (0 for RANK, 1 for EXPULSION, 2 for REPUTATION).
    * \return void
    */
    extern "C" void SetFactionChangesAction(unsigned short pid, unsigned char action) noexcept;

    /**
    * \brief Set the factionId of the temporary faction stored on the server.
    *
    * \param factionId The factionId.
    * \return void
    */
    extern "C" void SetFactionId(const char* factionId) noexcept;

    /**
    * \brief Set the rank of the temporary faction stored on the server.
    *
    * \param rank The rank.
    * \return void
    */
    extern "C" void SetFactionRank(unsigned int rank) noexcept;

    /**
    * \brief Set the expulsion state of the temporary faction stored on the server.
    *
    * \param expulsionState The expulsion state.
    * \return void
    */
    extern "C" void SetFactionExpulsionState(bool expulsionState) noexcept;

    /**
    * \brief Set the reputation of the temporary faction stored on the server.
    *
    * \param reputation The reputation.
    * \return void
    */
    extern "C" void SetFactionReputation(int reputation) noexcept;

    /**
    * \brief Add the server's temporary faction to the faction changes for a player.
    *
    * In the process, the server's temporary faction will automatically be cleared so a new one
    * can be set up.
    *
    * \param pid The player ID whose faction changes should be used.
    * \return void
    */
    extern "C" void AddFaction(unsigned short pid) noexcept;

    /**
    * \brief Send a PlayerFaction packet with a player's recorded faction changes.
    *
    * \param pid The player ID whose faction changes should be used.
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendFactionChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    // All methods below are deprecated versions of methods from above

    extern "C" void InitializeFactionChanges(unsigned short pid) noexcept;
}

#endif //OPENMW_FACTIONAPI_HPP
