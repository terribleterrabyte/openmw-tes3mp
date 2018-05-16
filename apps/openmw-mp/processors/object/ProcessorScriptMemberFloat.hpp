#ifndef OPENMW_PROCESSORSCRIPTMEMBERFLOAT_HPP
#define OPENMW_PROCESSORSCRIPTMEMBERFLOAT_HPP

#include "../ObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorScriptMemberFloat final : public ObjectProcessor
    {
    public:
        ProcessorScriptMemberFloat()
        {
            BPP_INIT(ID_SCRIPT_MEMBER_FLOAT)
        }
    };
}

#endif //OPENMW_PROCESSORSCRIPTMEMBERFLOAT_HPP
