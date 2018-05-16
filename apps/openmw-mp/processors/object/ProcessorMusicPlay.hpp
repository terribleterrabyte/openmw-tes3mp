#ifndef OPENMW_PROCESSORMUSICPLAY_HPP
#define OPENMW_PROCESSORMUSICPLAY_HPP

#include "../ObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorMusicPlay final: public ObjectProcessor
    {
    public:
        ProcessorMusicPlay()
        {
            BPP_INIT(ID_MUSIC_PLAY)
        }
    };
}

#endif //OPENMW_PROCESSORMUSICPLAY_HPP
