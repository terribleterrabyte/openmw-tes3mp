#ifndef OPENMW_NETWORKING_HPP
#define OPENMW_NETWORKING_HPP

#include <components/openmw-mp/Controllers/PlayerPacketController.hpp>
#include <components/openmw-mp/Controllers/ActorPacketController.hpp>
#include <components/openmw-mp/Controllers/ObjectPacketController.hpp>
#include <components/openmw-mp/Controllers/WorldstatePacketController.hpp>
#include <components/openmw-mp/Packets/PacketPreInit.hpp>
#include <apps/openmw-mp/Script/LuaState.hpp>
#include <apps/openmw-mp/Worldstate.hpp>

class MasterClient;
namespace  mwmp
{
    struct ChatChannel
    {
        ChatChannel()
        {
        }
        std::vector<std::weak_ptr<Player>> members;
    };

    class Networking
    {
    public:
        Networking(RakNet::RakPeerInterface *peer);
        ~Networking();

        void newPlayer(RakNet::RakNetGUID guid);
        void disconnectPlayer(RakNet::RakNetGUID guid);
        void kickPlayer(RakNet::RakNetGUID guid, bool sendNotification = true);
        
        void banAddress(const char *ipAddress);
        void unbanAddress(const char *ipAddress);
        RakNet::SystemAddress getSystemAddress(RakNet::RakNetGUID guid);

        void processPlayerPacket(RakNet::Packet *packet);
        void processActorPacket(RakNet::Packet *packet);
        void processObjectPacket(RakNet::Packet *packet);
        void processWorldstatePacket(RakNet::Packet *packet);
        bool update(RakNet::Packet *packet);

        unsigned short numberOfConnections() const;
        unsigned int maxConnections() const;
        int getAvgPing(RakNet::AddressOrGUID) const;

        int mainLoop();

        void stopServer(int code);

        PlayerPacketController *getPlayerPacketController() const;
        ActorPacketController *getActorPacketController() const;
        ObjectPacketController *getObjectPacketController() const;
        WorldstatePacketController *getWorldstatePacketController() const;

        LuaState &getState() {return luaState;}

        BaseActorList *getLastActorList();
        BaseObjectList *getLastObjectList();
        BaseWorldstate *getLastWorldstate();
        Worldstate *getServerWorldstate();

        int getCurrentMpNum();
        void setCurrentMpNum(int value);
        int incrementMpNum();

        bool getPluginEnforcementState();
        void setPluginEnforcementState(bool state);

        MasterClient *getMasterClient();
        void InitQuery(const std::string &queryAddr, unsigned short queryPort);
        void setServerPassword(std::string passw) noexcept;
        bool isPassworded() const;

        static Networking &get();
        static Networking *getPtr();

        void postInit();

        std::shared_ptr<ChatChannel> getChannel(unsigned id);
        unsigned createChannel();
        bool closeChannel(unsigned id);

    private:
        LuaState luaState;
        PacketPreInit::PluginContainer getPluginListSample();
        std::string serverPassword;
        static Networking *sThis;

        RakNet::RakPeerInterface *peer;
        RakNet::BitStream bsOut;
        std::unique_ptr<MasterClient> mclient;

        BaseActorList baseActorList;
        BaseObjectList baseObjectList;
        BaseWorldstate baseWorldstate;

        Worldstate serverWorldstate;

        std::unique_ptr<PlayerPacketController> playerPacketController;
        std::unique_ptr<ActorPacketController> actorPacketController;
        std::unique_ptr<ObjectPacketController> objectPacketController;
        std::unique_ptr<WorldstatePacketController> worldstatePacketController;

        bool running;
        int exitCode;
        PacketPreInit::PluginContainer samples;

        std::unordered_map<unsigned, std::shared_ptr<ChatChannel>> chatChannels;
    };
}


#endif //OPENMW_NETWORKING_HPP
