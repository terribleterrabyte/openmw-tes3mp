//
// Created by koncord on 01.04.17.
//

#ifndef OPENMW_PROCESSORPLAYERCHATMSG_HPP
#define OPENMW_PROCESSORPLAYERCHATMSG_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorChatMsg final: public PlayerProcessor
    {
    public:
        ProcessorChatMsg()
        {
            BPP_INIT(ID_CHAT_MESSAGE)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            auto &lua = Networking::get().getState();

            auto cmdExecResult = lua.getCmdCtrl().exec(player, player->chat.message, player->chat.channel);
            switch (cmdExecResult.first)
            {
                case CommandController::ExecResult::NOT_FOUND: // err cmd not found
                    player->message(player->chat.channel, "#FF0000Command not found.\n"); // inform player that command not found
                    break;
                case CommandController::ExecResult::NOT_CMD: // cmd length < 2 or message is not cmd
                    lua.getEventCtrl().Call<CoreEvent::ON_PLAYER_SENDMESSAGE>(player, player->chat.message, player->chat.channel);
                    break;
                case CommandController::ExecResult::SUCCESS: // returned true from function
                    break;
                case CommandController::ExecResult::FAIL: // returned false from function
                    player->message(player->chat.channel, "#B8860B"+cmdExecResult.second + "\n"); // show "help msg" to player
                    break;
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERCHATMSG_HPP
