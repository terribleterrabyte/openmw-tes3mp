#ifndef OPENMW_STATAPI_HPP
#define OPENMW_STATAPI_HPP

#define STATAPI \
    {"GetAttributeCount",       StatsFunctions::GetAttributeCount},\
    {"GetSkillCount",           StatsFunctions::GetSkillCount},\
    {"GetAttributeId",          StatsFunctions::GetAttributeId},\
    {"GetSkillId",              StatsFunctions::GetSkillId},\
    {"GetAttributeName",        StatsFunctions::GetAttributeName},\
    {"GetSkillName",            StatsFunctions::GetSkillName},\
    \
    {"GetName",                 StatsFunctions::GetName},\
    {"GetRace",                 StatsFunctions::GetRace},\
    {"GetHead",                 StatsFunctions::GetHead},\
    {"GetHair",                 StatsFunctions::GetHairstyle},\
    {"GetIsMale",               StatsFunctions::GetIsMale},\
    {"GetBirthsign",            StatsFunctions::GetBirthsign},\
    \
    {"GetLevel",                StatsFunctions::GetLevel},\
    {"GetLevelProgress",        StatsFunctions::GetLevelProgress},\
    \
    {"GetHealthBase",           StatsFunctions::GetHealthBase},\
    {"GetHealthCurrent",        StatsFunctions::GetHealthCurrent},\
    \
    {"GetMagickaBase",          StatsFunctions::GetMagickaBase},\
    {"GetMagickaCurrent",       StatsFunctions::GetMagickaCurrent},\
    \
    {"GetFatigueBase",          StatsFunctions::GetFatigueBase},\
    {"GetFatigueCurrent",       StatsFunctions::GetFatigueCurrent},\
    \
    {"GetAttributeBase",        StatsFunctions::GetAttributeBase},\
    {"GetAttributeModifier",    StatsFunctions::GetAttributeModifier},\
    \
    {"GetSkillBase",            StatsFunctions::GetSkillBase},\
    {"GetSkillModifier",        StatsFunctions::GetSkillModifier},\
    {"GetSkillProgress",        StatsFunctions::GetSkillProgress},\
    {"GetSkillIncrease",        StatsFunctions::GetSkillIncrease},\
    \
    {"GetBounty",               StatsFunctions::GetBounty},\
    \
    {"SetName",                 StatsFunctions::SetName},\
    {"SetRace",                 StatsFunctions::SetRace},\
    {"SetHead",                 StatsFunctions::SetHead},\
    {"SetHair",                 StatsFunctions::SetHairstyle},\
    {"SetIsMale",               StatsFunctions::SetIsMale},\
    {"SetBirthsign",            StatsFunctions::SetBirthsign},\
    {"SetResetStats",           StatsFunctions::SetResetStats},\
    \
    {"SetLevel",                StatsFunctions::SetLevel},\
    {"SetLevelProgress",        StatsFunctions::SetLevelProgress},\
    \
    {"SetHealthBase",           StatsFunctions::SetHealthBase},\
    {"SetHealthCurrent",        StatsFunctions::SetHealthCurrent},\
    {"SetMagickaBase",          StatsFunctions::SetMagickaBase},\
    {"SetMagickaCurrent",       StatsFunctions::SetMagickaCurrent},\
    {"SetFatigueBase",          StatsFunctions::SetFatigueBase},\
    {"SetFatigueCurrent",       StatsFunctions::SetFatigueCurrent},\
    \
    {"SetAttributeBase",        StatsFunctions::SetAttributeBase},\
    {"ClearAttributeModifier",  StatsFunctions::ClearAttributeModifier},\
    \
    {"SetSkillBase",            StatsFunctions::SetSkillBase},\
    {"ClearSkillModifier",      StatsFunctions::ClearSkillModifier},\
    {"SetSkillProgress",        StatsFunctions::SetSkillProgress},\
    {"SetSkillIncrease",        StatsFunctions::SetSkillIncrease},\
    \
    {"SetBounty",               StatsFunctions::SetBounty},\
    {"SetCharGenStage",         StatsFunctions::SetCharGenStage},\
    \
    {"SendBaseInfo",            StatsFunctions::SendBaseInfo},\
    \
    {"SendStatsDynamic",        StatsFunctions::SendStatsDynamic},\
    {"SendAttributes",          StatsFunctions::SendAttributes},\
    {"SendSkills",              StatsFunctions::SendSkills},\
    {"SendLevel",               StatsFunctions::SendLevel},\
    {"SendBounty",              StatsFunctions::SendBounty}

namespace StatsFunctions
{
    /**
    * \brief Get the number of attributes.
    *
    * The number is 8 before any dehardcoding is done in OpenMW.
    *
    * \return The number of attributes.
    */
    extern "C" int GetAttributeCount() noexcept;

    /**
    * \brief Get the number of skills.
    *
    * The number is 27 before any dehardcoding is done in OpenMW.
    *
    * \return The number of skills.
    */
    extern "C" int GetSkillCount() noexcept;

    /**
    * \brief Get the numerical ID of an attribute with a certain name.
    *
    * If an invalid name is used, the ID returned is -1
    *
    * \param name The name of the attribute.
    * \return The ID of the attribute.
    */
    extern "C" int GetAttributeId(const char *name) noexcept;

    /**
    * \brief Get the numerical ID of a skill with a certain name.
    *
    * If an invalid name is used, the ID returned is -1
    *
    * \param name The name of the skill.
    * \return The ID of the skill.
    */
    extern "C" int GetSkillId(const char *name) noexcept;

    /**
    * \brief Get the name of the attribute with a certain numerical ID.
    *
    * If an invalid ID is used, "invalid" is returned.
    *
    * \param attributeId The ID of the attribute.
    * \return The name of the attribute.
    */
    extern "C" const char *GetAttributeName(unsigned short attributeId) noexcept;

    /**
    * \brief Get the name of the skill with a certain numerical ID.
    *
    * If an invalid ID is used, "invalid" is returned.
    *
    * \param skillId The ID of the skill.
    * \return The name of the skill.
    */
    extern "C" const char *GetSkillName(unsigned short skillId) noexcept;

    /**
    * \brief Get the name of a player.
    *
    * \param pid The player ID.
    * \return The name of the player.
    */
    extern "C" const char *GetName(unsigned short pid) noexcept;

    /**
    * \brief Get the race of a player.
    *
    * \param pid The player ID.
    * \return The race of the player.
    */
    extern "C" const char *GetRace(unsigned short pid) noexcept;

    /**
    * \brief Get the head mesh used by a player.
    *
    * \param pid The player ID.
    * \return The head mesh of the player.
    */
    extern "C" const char *GetHead(unsigned short pid) noexcept;

    /**
    * \brief Get the hairstyle mesh used by a player.
    *
    * \param pid The player ID.
    * \return The hairstyle mesh of the player.
    */
    extern "C" const char *GetHairstyle(unsigned short pid) noexcept;

    /**
    * \brief Check whether a player is male or not.
    *
    * \param pid The player ID.
    * \return Whether the player is male.
    */
    extern "C" int GetIsMale(unsigned short pid) noexcept;

    /**
    * \brief Get the birthsign of a player.
    *
    * \param pid The player ID.
    * \return The birthsign of the player.
    */
    extern "C" const char *GetBirthsign(unsigned short pid) noexcept;

    /**
    * \brief Get the character level of a player.
    *
    * \param pid The player ID.
    * \return The level of the player.
    */
    extern "C" int GetLevel(unsigned short pid) noexcept;

    /**
    * \brief Get the player's progress to their next character level.
    *
    * \param pid The player ID.
    * \return The level progress.
    */
    extern "C" int GetLevelProgress(unsigned short pid) noexcept;

    /**
    * \brief Get the base health of the player.
    *
    * \param pid The player ID.
    * \return The base health.
    */
    extern "C" double GetHealthBase(unsigned short pid) noexcept;

    /**
    * \brief Get the current health of the player.
    *
    * \param pid The player ID.
    * \return The current health.
    */
    extern "C" double GetHealthCurrent(unsigned short pid) noexcept;

    /**
    * \brief Get the base magicka of the player.
    *
    * \param pid The player ID.
    * \return The base magicka.
    */
    extern "C" double GetMagickaBase(unsigned short pid) noexcept;

    /**
    * \brief Get the current magicka of the player.
    *
    * \param pid The player ID.
    * \return The current magicka.
    */
    extern "C" double GetMagickaCurrent(unsigned short pid) noexcept;

    /**
    * \brief Get the base fatigue of the player.
    *
    * \param pid The player ID.
    * \return The base fatigue.
    */
    extern "C" double GetFatigueBase(unsigned short pid) noexcept;

    /**
    * \brief Get the current fatigue of the player.
    *
    * \param pid The player ID.
    * \return The current fatigue.
    */
    extern "C" double GetFatigueCurrent(unsigned short pid) noexcept;

    /**
    * \brief Get the base value of a player's attribute.
    *
    * \param pid The player ID.
    * \param attributeId The attribute ID.
    * \return The base value of the attribute.
    */
    extern "C" int GetAttributeBase(unsigned short pid, unsigned short attributeId) noexcept;

    /**
    * \brief Get the modifier value of a player's attribute.
    *
    * \param pid The player ID.
    * \param attributeId The attribute ID.
    * \return The modifier value of the attribute.
    */
    extern "C" int GetAttributeModifier(unsigned short pid, unsigned short attributeId) noexcept;

    /**
    * \brief Get the base value of a player's skill.
    *
    * \param pid The player ID.
    * \param skillId The skill ID.
    * \return The base value of the skill.
    */
    extern "C" int GetSkillBase(unsigned short pid, unsigned short skillId) noexcept;

    /**
    * \brief Get the modifier value of a player's skill.
    *
    * \param pid The player ID.
    * \param skillId The skill ID.
    * \return The modifier value of the skill.
    */
    extern "C" int GetSkillModifier(unsigned short pid, unsigned short skillId) noexcept;

    /**
    * \brief Get the progress the player has made towards increasing a certain skill by 1.
    *
    * \param pid The player ID.
    * \param skillId The skill ID.
    * \return The skill progress.
    */
    extern "C" double GetSkillProgress(unsigned short pid, unsigned short skillId) noexcept;

    /**
    * \brief Get the bonus applied to a certain attribute at the next level up as a result
    *        of associated skill increases.
    *
    * Although confusing, the term "skill increase" for this is taken from OpenMW itself.
    *
    * \param pid The player ID.
    * \param skillId The attribute ID.
    * \return The increase in the attribute caused by skills.
    */
    extern "C" int GetSkillIncrease(unsigned short pid, unsigned int attributeId) noexcept;

    /**
    * \brief Get the bounty of the player.
    *
    * \param pid The player ID.
    * \return The bounty.
    */
    extern "C" int GetBounty(unsigned short pid) noexcept;

    /**
    * \brief Set the name of a player.
    *
    * \param pid The player ID.
    * \param name The new name of the player.
    * \return void
    */
    extern "C" void SetName(unsigned short pid, const char *name) noexcept;

    /**
    * \brief Set the race of a player.
    *
    * \param pid The player ID.
    * \param race The new race of the player.
    * \return void
    */
    extern "C" void SetRace(unsigned short pid, const char *race) noexcept;

    /**
    * \brief Set the head mesh used by a player.
    *
    * \param pid The player ID.
    * \param head The new head mesh of the player.
    * \return void
    */
    extern "C" void SetHead(unsigned short pid, const char *head) noexcept;

    /**
    * \brief Set the hairstyle mesh used by a player.
    *
    * \param pid The player ID.
    * \param hairstyle The new hairstyle mesh of the player.
    * \return void
    */
    extern "C" void SetHairstyle(unsigned short pid, const char *hairstyle) noexcept;

    /**
    * \brief Set whether a player is male or not.
    *
    * \param pid The player ID.
    * \param state Whether the player is male.
    * \return void
    */
    extern "C" void SetIsMale(unsigned short pid, int state) noexcept;

    /**
    * \brief Set the birthsign of a player.
    *
    * \param pid The player ID.
    * \param name The new birthsign of the player.
    * \return void
    */
    extern "C" void SetBirthsign(unsigned short pid, const char *name) noexcept;

    /**
    * \brief Set whether the player's stats should be reset based on their
    *        current race as the result of a PlayerBaseInfo packet.
    *
    * This changes the resetState for that player in the server memory, but does not by itself
    * send a packet.
    *
    * \param pid The player ID.
    * \param resetStats The stat reset state.
    * \return void
    */
    extern "C" void SetResetStats(unsigned short pid, bool resetStats) noexcept;
    
    /**
    * \brief Set the character level of a player.
    *
    * \param pid The player ID.
    * \param value The new level of the player.
    * \return void
    */
    extern "C" void SetLevel(unsigned short pid, int value) noexcept;

    /**
    * \brief Set the player's progress to their next character level.
    *
    * \param pid The player ID.
    * \param value The new level progress of the player.
    * \return void
    */
    extern "C" void SetLevelProgress(unsigned short pid, int value) noexcept;

    /**
    * \brief Set the base health of a player.
    *
    * \param pid The player ID.
    * \param name The new base health of the player.
    * \return void
    */
    extern "C" void SetHealthBase(unsigned short pid, double value) noexcept;

    /**
    * \brief Set the current health of a player.
    *
    * \param pid The player ID.
    * \param name The new current health of the player.
    * \return void
    */
    extern "C" void SetHealthCurrent(unsigned short pid, double value) noexcept;

    /**
    * \brief Set the base magicka of a player.
    *
    * \param pid The player ID.
    * \param name The new base magicka of the player.
    * \return void
    */
    extern "C" void SetMagickaBase(unsigned short pid, double value) noexcept;

    /**
    * \brief Set the current magicka of a player.
    *
    * \param pid The player ID.
    * \param name The new current magicka of the player.
    * \return void
    */
    extern "C" void SetMagickaCurrent(unsigned short pid, double value) noexcept;

    /**
    * \brief Set the base fatigue of a player.
    *
    * \param pid The player ID.
    * \param name The new base fatigue of the player.
    * \return void
    */
    extern "C" void SetFatigueBase(unsigned short pid, double value) noexcept;

    /**
    * \brief Set the current fatigue of a player.
    *
    * \param pid The player ID.
    * \param name The new current fatigue of the player.
    * \return void
    */
    extern "C" void SetFatigueCurrent(unsigned short pid, double value) noexcept;

    /**
    * \brief Set the base value of a player's attribute.
    *
    * \param pid The player ID.
    * \param attributeId The attribute ID.
    * \param value The new base value of the player's attribute.
    * \return void
    */
    extern "C" void SetAttributeBase(unsigned short pid, unsigned short attributeId, int value) noexcept;

    /**
    * \brief Clear the modifier value of a player's attribute.
    *
    * There's no way to set a modifier to a specific value because it can come from
    * multiple different sources, but clearing it is a straightforward process that
    * dispels associated effects on a client and, if necessary, unequips associated
    * items.
    *
    * \param pid The player ID.
    * \param attributeId The attribute ID.
    * \return void
    */
    extern "C" void ClearAttributeModifier(unsigned short pid, unsigned short attributeId) noexcept;

    /**
    * \brief Set the base value of a player's skill.
    *
    * \param pid The player ID.
    * \param skillId The skill ID.
    * \param value The new base value of the player's skill.
    * \return void
    */
    extern "C" void SetSkillBase(unsigned short pid, unsigned short skillId, int value) noexcept;    

    /**
    * \brief Clear the modifier value of a player's skill.
    *
    * There's no way to set a modifier to a specific value because it can come from
    * multiple different sources, but clearing it is a straightforward process that
    * dispels associated effects on a client and, if necessary, unequips associated
    * items.
    *
    * \param pid The player ID.
    * \param skillId The skill ID.
    * \return void
    */
    extern "C" void ClearSkillModifier(unsigned short pid, unsigned short skillId) noexcept;

    /**
    * \brief Set the progress the player has made towards increasing a certain skill by 1.
    *
    * \param pid The player ID.
    * \param skillId The skill ID.
    * \param value The progress value.
    * \return void
    */
    extern "C" void SetSkillProgress(unsigned short pid, unsigned short skillId, double value) noexcept;

    /**
    * \brief Set the bonus applied to a certain attribute at the next level up as a result
    *        of associated skill increases.
    *
    * Although confusing, the term "skill increase" for this is taken from OpenMW itself.
    *
    * \param pid The player ID.
    * \param skillId The attribute ID.
    * \param value The increase in the attribute caused by skills.
    * \return void
    */
    extern "C" void SetSkillIncrease(unsigned short pid, unsigned int attributeId, int value) noexcept;

    /**
    * \brief Set the bounty of a player.
    *
    * \param pid The player ID.
    * \param value The new bounty.
    * \return void
    */
    extern "C" void SetBounty(unsigned short pid, int value) noexcept;

    /**
    * \brief Set the current and ending stages of character generation for a player.
    *
    * This is used to repeat part of character generation or to only go through part of it.
    *
    * \param pid The player ID.
    * \param currentStage The new current stage.
    * \param endStage The new ending stage.
    * \return void
    */
    extern "C" void SetCharGenStage(unsigned short pid, int currentStage, int endStage) noexcept;

    /**
    * \brief Send a PlayerBaseInfo packet with a player's name, race, head mesh,
    *        hairstyle mesh, birthsign and stat reset state.
    *
    * It is always sent to all players.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendBaseInfo(unsigned short pid) noexcept;

    /**
    * \brief Send a PlayerStatsDynamic packet with a player's dynamic stats (health,
    *        magicka and fatigue).
    *
    * It is always sent to all players.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendStatsDynamic(unsigned short pid) noexcept;

    /**
    * \brief Send a PlayerAttribute packet with a player's attributes and bonuses
    *        to those attributes at the next level up (the latter being called
    *        "skill increases" as in OpenMW).
    *
    * It is always sent to all players.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendAttributes(unsigned short pid) noexcept;

    /**
    * \brief Send a PlayerSkill packet with a player's skills.
    *
    * It is always sent to all players.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendSkills(unsigned short pid) noexcept;

    /**
    * \brief Send a PlayerLevel packet with a player's character level and
    *        progress towards the next level up
    *
    * It is always sent to all players.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendLevel(unsigned short pid) noexcept;

    /**
    * \brief Send a PlayerBounty packet with a player's bounty.
    *
    * It is always sent to all players.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void SendBounty(unsigned short pid) noexcept;
}

#endif //OPENMW_STATAPI_HPP
