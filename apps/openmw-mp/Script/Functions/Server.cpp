#include "Server.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>
#include <components/openmw-mp/Version.hpp>

#include <apps/openmw-mp/Script/ScriptFunctions.hpp>
#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/MasterClient.hpp>


extern "C" void ServerFunctions::StopServer(int code) noexcept
{
    mwmp::Networking::getPtr()->stopServer(code);
}

extern "C" void ServerFunctions::Kick(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Kicking player %s (%i)", player->npc.mName.c_str(), player->getId());
    mwmp::Networking::getPtr()->kickPlayer(player->guid);
    player->setLoadState(Player::KICKED);
}

extern "C" void ServerFunctions::BanAddress(const char *ipAddress) noexcept
{
    mwmp::Networking::getPtr()->banAddress(ipAddress);
}

extern "C" void ServerFunctions::UnbanAddress(const char *ipAddress) noexcept
{
    mwmp::Networking::getPtr()->unbanAddress(ipAddress);
}

extern "C" const char *ServerFunctions::GetServerVersion() noexcept
{
    return TES3MP_VERSION;
}

extern "C" const char *ServerFunctions::GetProtocolVersion() noexcept
{
    static std::string version = std::to_string(TES3MP_PROTO_VERSION);
    return version.c_str();
}

extern "C" int ServerFunctions::GetAvgPing(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, -1);
    return mwmp::Networking::get().getAvgPing(player->guid);
}

extern "C" const char *ServerFunctions::GetIP(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");
    RakNet::SystemAddress addr = mwmp::Networking::getPtr()->getSystemAddress(player->guid);
    return addr.ToString(false);
}

extern "C" unsigned short ServerFunctions::GetPort() noexcept
{
    return mwmp::Networking::get().getPort();
}

extern "C" unsigned int ServerFunctions::GetMaxPlayers() noexcept
{
    return mwmp::Networking::get().maxConnections();
}

extern "C" bool ServerFunctions::HasPassword() noexcept
{
    return mwmp::Networking::get().isPassworded();
}

extern "C" bool ServerFunctions::GetPluginEnforcementState() noexcept
{
    return mwmp::Networking::getPtr()->getPluginEnforcementState();
}

extern "C" bool ServerFunctions::GetScriptErrorIgnoringState() noexcept
{
    return mwmp::Networking::getPtr()->getScriptErrorIgnoringState();
}

extern "C" void ServerFunctions::SetGameMode(const char *gameMode) noexcept
{
    if (mwmp::Networking::getPtr()->getMasterClient())
        mwmp::Networking::getPtr()->getMasterClient()->SetModname(gameMode);
}

extern "C" void ServerFunctions::SetHostname(const char *name) noexcept
{
    if (mwmp::Networking::getPtr()->getMasterClient())
        mwmp::Networking::getPtr()->getMasterClient()->SetHostname(name);
}

extern "C" void ServerFunctions::SetServerPassword(const char *password) noexcept
{
    mwmp::Networking::getPtr()->setServerPassword(password);
}

extern "C" void ServerFunctions::SetPluginEnforcementState(bool state) noexcept
{
    mwmp::Networking::getPtr()->setPluginEnforcementState(state);
}

extern "C" void ServerFunctions::SetScriptErrorIgnoringState(bool state) noexcept
{
    mwmp::Networking::getPtr()->setScriptErrorIgnoringState(state);
}

extern "C" void ServerFunctions::SetRuleString(const char *key, const char *value) noexcept
{
    auto mc = mwmp::Networking::getPtr()->getMasterClient();
    if (mc)
        mc->SetRuleString(key, value);
}

extern "C" void ServerFunctions::SetRuleValue(const char *key, double value) noexcept
{
    auto mc = mwmp::Networking::getPtr()->getMasterClient();
    if (mc)
        mc->SetRuleValue(key, value);
}

extern "C" void ServerFunctions::AddPluginHash(const char *pluginName, const char *hashStr) noexcept
{
    auto &samples = mwmp::Networking::getPtr()->getSamples();
    auto it = std::find_if(samples.begin(), samples.end(), [&pluginName](mwmp::PacketPreInit::PluginPair &item) {
        return item.first == pluginName;
    });
    if (it != samples.end())
        it->second.push_back((unsigned) std::stoul(hashStr));
    else
    {
        mwmp::PacketPreInit::HashList hashList;

        unsigned hash = 0;

        if (strlen(hashStr) != 0)
        {
            hash = (unsigned) std::stoul(hashStr);
            hashList.push_back(hash);
        }
        samples.emplace_back(pluginName, hashList);

        auto mclient = mwmp::Networking::getPtr()->getMasterClient();
        if (mclient)
            mclient->PushPlugin({pluginName, hash});
    }
}
