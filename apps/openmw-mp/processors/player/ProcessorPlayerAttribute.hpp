//
// Created by koncord on 01.04.17.
//

#ifndef OPENMW_PROCESSORPLAYERATTRIBUTE_HPP
#define OPENMW_PROCESSORPLAYERATTRIBUTE_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorPlayerAttribute final: public PlayerProcessor
    {
    public:
        using OldAState = ESM::StatState<int>;
        ProcessorPlayerAttribute()
        {
            BPP_INIT(ID_PLAYER_ATTRIBUTE)

            Networking::get().getState().getState()->new_usertype<OldAState>("OldAState",
                                                                             "base", &OldAState::mBase,
                                                                             "current", &OldAState::mCurrent,
                                                                             "mod", &OldAState::mMod,
                                                                             "damage", &OldAState::mDamage);
        }

        void PreReading(PlayerPacket &packet, const std::shared_ptr<Player> &player)
        {
            if (!player->creatureStats.mDead)
                std::copy(std::begin(player->creatureStats.mAttributes),
                          std::end(player->creatureStats.mAttributes),
                          oldValues.begin()
                );

        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            if (!player->creatureStats.mDead)
            {
                //myPacket->Send(player, true);
                Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_PLAYER_ATTRIBUTE, true>(&oldValues, player.get());

                player->sendToLoaded(packet);
            }
        }
    private:
        std::array<OldAState, ESM::Attribute::Length> oldValues;
    };
}

#endif //OPENMW_PROCESSORPLAYERATTRIBUTE_HPP
