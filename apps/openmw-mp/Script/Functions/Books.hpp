#ifndef OPENMW_BOOKAPI_HPP
#define OPENMW_BOOKAPI_HPP

#define BOOKAPI \
    {"ClearBookChanges",       BookFunctions::ClearBookChanges},\
    \
    {"GetBookChangesSize",     BookFunctions::GetBookChangesSize},\
    \
    {"AddBook",                BookFunctions::AddBook},\
    \
    {"GetBookId",              BookFunctions::GetBookId},\
    \
    {"SendBookChanges",        BookFunctions::SendBookChanges},\
    \
    {"InitializeBookChanges",  BookFunctions::InitializeBookChanges}

namespace BookFunctions
{

    /**
    * \brief Clear the last recorded book changes for a player.
    *
    * This is used to initialize the sending of new PlayerBook packets.
    *
    * \param pid The player ID whose book changes should be used.
    * \return void
    */
    extern "C" void ClearBookChanges(unsigned short pid) noexcept;

    /**
    * \brief Get the number of indexes in a player's latest book changes.
    *
    * \param pid The player ID whose book changes should be used.
    * \return The number of indexes.
    */
    extern "C" unsigned int GetBookChangesSize(unsigned short pid) noexcept;

    /**
    * \brief Add a new book to the book changes for a player.
    *
    * \param pid The player ID whose book changes should be used.
    * \param bookId The bookId of the book.
    * \return void
    */
    extern "C" void AddBook(unsigned short pid, const char* bookId) noexcept;

    /**
    * \brief Get the bookId at a certain index in a player's latest book changes.
    *
    * \param pid The player ID whose book changes should be used.
    * \param index The index of the book.
    * \return The bookId.
    */
    extern "C" const char *GetBookId(unsigned short pid, unsigned int index) noexcept;

    /**
    * \brief Send a PlayerBook packet with a player's recorded book changes.
    *
    * \param pid The player ID whose book changes should be used.
    * \param sendToOtherPlayers Whether this packet should be sent to players other than the
    *                           player attached to the packet (false by default).
    * \param skipAttachedPlayer Whether the packet should skip being sent to the player attached
    *                           to the packet (false by default).
    * \return void
    */
    extern "C" void SendBookChanges(unsigned short pid, bool sendToOtherPlayers, bool skipAttachedPlayer) noexcept;

    // All methods below are deprecated versions of methods from above

    extern "C" void InitializeBookChanges(unsigned short pid) noexcept;
}

#endif //OPENMW_BOOKAPI_HPP
