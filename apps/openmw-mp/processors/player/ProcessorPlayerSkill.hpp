//
// Created by koncord on 01.04.17.
//

#ifndef OPENMW_PROCESSORPLAYERSKILL_HPP
#define OPENMW_PROCESSORPLAYERSKILL_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerSkill final: public PlayerProcessor
    {
    public:
        ProcessorPlayerSkill()
        {
            BPP_INIT(ID_PLAYER_SKILL)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            if (!player->creatureStats.mDead)
            {
                //myPacket->Send(player, true);
                player->sendToLoaded(packet);

                Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_SKILL>(player.get());
            }
        }
    };
}

#endif //OPENMW_PROCESSORPLAYERSKILL_HPP
