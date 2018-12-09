#include "Miscellaneous.hpp"

#include <components/misc/stringops.hpp>
#include <components/openmw-mp/Log.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>

#include <iostream>
using namespace std;

static std::string tempFilename;

extern "C" bool MiscellaneousFunctions::DoesFileExist(const char *filePath) noexcept
{
    return boost::filesystem::exists(filePath);
}

extern "C" const char *MiscellaneousFunctions::GetCaseInsensitiveFilename(const char *folderPath, const char *filename) noexcept
{
    if (!boost::filesystem::exists(folderPath)) return "invalid";

    boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end

    for (boost::filesystem::directory_iterator itr(folderPath); itr != end_itr; ++itr)
    {
        if (Misc::StringUtils::ciEqual(itr->path().filename().string(), filename))
        {
            tempFilename = itr->path().filename().string();
            return tempFilename.c_str();
        }
    }
    return "invalid";
}

extern "C" unsigned int MiscellaneousFunctions::GetLastPlayerId() noexcept
{
    return Players::getLastPlayerId();
}

extern "C" int MiscellaneousFunctions::GetCurrentMpNum() noexcept
{
    return mwmp::Networking::getPtr()->getCurrentMpNum();
}

extern "C" void MiscellaneousFunctions::SetCurrentMpNum(int mpNum) noexcept
{
    mwmp::Networking::getPtr()->setCurrentMpNum(mpNum);
}

extern "C" void MiscellaneousFunctions::LogMessage(unsigned short level, const char *message) noexcept
{
    LOG_MESSAGE_SIMPLE(level, "[Script]: %s", message);
}

extern "C" void MiscellaneousFunctions::LogAppend(unsigned short level, const char *message) noexcept
{
    LOG_APPEND(level, "[Script]: %s", message);
}
