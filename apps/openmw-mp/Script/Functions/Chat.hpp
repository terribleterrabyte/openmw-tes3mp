#ifndef OPENMW_CHATAPI_HPP
#define OPENMW_CHATAPI_HPP

#include "../Types.hpp"

#define CHATAPI \
    {"SendMessage",       ChatFunctions::SendMessage},\
    {"CleanChatForPid",   ChatFunctions::CleanChat},\
    {"CleanChat",         ChatFunctions::CleanChatForPid}

namespace ChatFunctions
{
    /**
    * \brief Send a message to a certain player.
    *
    * \param pid The player ID.
    * \param message The contents of the message.
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendMessage(unsigned short pid, const char *message, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    /**
    * \brief Remove all messages from chat for a certain player.
    *
    * \param pid The player ID.
    * \return void
    */
    extern "C" void CleanChatForPid(unsigned short pid);

    /**
    * \brief Remove all messages from chat for everyone on the server.
    *
    * \return void
    */
    extern "C" void CleanChat();
}

#endif //OPENMW_CHATAPI_HPP
