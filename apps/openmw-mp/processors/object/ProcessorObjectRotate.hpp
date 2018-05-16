#ifndef OPENMW_PROCESSOROBJECTROTATE_HPP
#define OPENMW_PROCESSOROBJECTROTATE_HPP

#include "../ObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectRotate final: public ObjectProcessor
    {
    public:
        ProcessorObjectRotate()
        {
            BPP_INIT(ID_OBJECT_ROTATE)
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTROTATE_HPP
