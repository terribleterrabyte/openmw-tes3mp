#ifndef OPENMW_PROCESSORRECORDDYNAMIC_HPP
#define OPENMW_PROCESSORRECORDDYNAMIC_HPP

#include "../PlayerProcessor.hpp"

namespace mwmp
{
    class ProcessorRecordDynamic final : public PlayerProcessor
    {
    public:
        using OldDState = ESM::StatState<float>;
        ProcessorRecordDynamic()
        {
            BPP_INIT(ID_RECORD_DYNAMIC)

            Networking::get().getState().getState()->new_usertype<OldDState>("OldDState",
                                                                             "base", &OldDState::mBase,
                                                                             "current", &OldDState::mCurrent,
                                                                             "mod", &OldDState::mMod,
                                                                             "damage", &OldDState::mDamage,
                                                                             "progress", &OldDState::mProgress);
        }

        void PreReading(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            std::copy(std::begin(player->creatureStats.mDynamic),
                      std::end(player->creatureStats.mDynamic),
                      oldValues.begin()
            );

        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            Networking::get().getState().getEventCtrl().Call<CoreEvent::ON_RECORD_DYNAMIC, true>(&oldValues, player);
        }
    private:
        std::array<OldDState, 3> oldValues;
    };
}

#endif //OPENMW_PROCESSORRECORDDYNAMIC_HPP
