#ifndef OPENMW_DIALOGUEAPI_HPP
#define OPENMW_DIALOGUEAPI_HPP

#define DIALOGUEAPI \
    {"ClearTopicChanges",       DialogueFunctions::ClearTopicChanges},\
    \
    {"GetTopicChangesSize",     DialogueFunctions::GetTopicChangesSize},\
    \
    {"AddTopic",                DialogueFunctions::AddTopic},\
    \
    {"GetTopicId",              DialogueFunctions::GetTopicId},\
    \
    {"SendTopicChanges",        DialogueFunctions::SendTopicChanges},\
    \
    {"PlayAnimation",           DialogueFunctions::PlayAnimation},\
    {"PlaySpeech",              DialogueFunctions::PlaySpeech},\
    \
    {"InitializeTopicChanges",  DialogueFunctions::InitializeTopicChanges}

namespace DialogueFunctions
{
    /**
    * \brief Clear the last recorded topic changes for a player.
    *
    * This is used to initialize the sending of new PlayerTopic packets.
    *
    * \param pid The player ID whose topic changes should be used.
    * \return void
    */
    extern "C" void ClearTopicChanges(unsigned short pid) noexcept;

    /**
    * \brief Get the number of indexes in a player's latest topic changes.
    *
    * \param pid The player ID whose topic changes should be used.
    * \return The number of indexes.
    */
    extern "C" unsigned int GetTopicChangesSize(unsigned short pid) noexcept;

    /**
    * \brief Add a new topic to the topic changes for a player.
    *
    * \param pid The player ID whose topic changes should be used.
    * \param topicId The topicId of the topic.
    * \return void
    */
    extern "C" void AddTopic(unsigned short pid, const char* topicId) noexcept;

    /**
    * \brief Get the topicId at a certain index in a player's latest topic changes.
    *
    * \param pid The player ID whose topic changes should be used.
    * \param index The index of the topic.
    * \return The topicId.
    */
    extern "C" const char *GetTopicId(unsigned short pid, unsigned int index) noexcept;

    /**
    * \brief Send a PlayerTopic packet with a player's recorded topic changes.
    *
    * \param pid The player ID whose topic changes should be used.
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendTopicChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Play a certain animation on a player's character by sending a PlayerAnimation
    *        packet.
    *
    * \param pid The player ID of the character playing the animation.
    * \param groupname The groupname of the animation.
    * \param mode The mode of the animation.
    * \param count The number of times the animation should be played.
    * \param bool Whether the animation should persist or not.
    * \return void
    */
    extern "C" void PlayAnimation(unsigned short pid, const char* groupname, int mode, int count, bool persist) noexcept;

    /**
    * \brief Play a certain sound for a player as spoken by their character by sending
    *        a PlayerSpeech packet.
    *
    * \param pid The player ID of the character playing the sound.
    * \param sound The path of the sound file.
    * \return void
    */
    extern "C" void PlaySpeech(unsigned short pid, const char* sound) noexcept;

    // All methods below are deprecated versions of methods from above

    extern "C" void InitializeTopicChanges(unsigned short pid) noexcept;
}

#endif //OPENMW_DIALOGUEAPI_HPP
