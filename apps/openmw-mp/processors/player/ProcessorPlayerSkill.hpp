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
        using OldSState = ESM::StatState<int>;
    public:
        ProcessorPlayerSkill()
        {
            BPP_INIT(ID_PLAYER_SKILL)
            Networking::get().getState().getState()->new_usertype<OldSState>("OldSState",
                                                                             "base", &OldSState::mBase,
                                                                             "current", &OldSState::mCurrent,
                                                                             "mod", &OldSState::mMod,
                                                                             "damage", &OldSState::mDamage,
                                                                             "progress", &OldSState::mProgress);
        }

        void PreReading(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            if (!player->creatureStats.mDead)
                std::copy(std::begin(player->npcStats.mSkills),
                          std::end(player->npcStats.mSkills),
                          oldValues.begin()
                );
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            if (!player->creatureStats.mDead)
            {
                //myPacket->Send(player, true);
                Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_SKILL, true>(&oldValues, player.get());
                player->sendToLoaded(packet);
            }
        }
    private:
        std::array<OldSState, ESM::Skill::Length> oldValues;
    };
}

#endif //OPENMW_PROCESSORPLAYERSKILL_HPP
