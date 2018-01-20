//
// Created by koncord on 12.08.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>

#include "Script/LuaState.hpp"
#include "Networking.hpp"

#include "Settings.hpp"
#include "Player.hpp"

void GameSettings::Init(LuaState &lua)
{
    lua.getState()->new_usertype<GameSettings>("Settings",
                                           "setDifficulty", &GameSettings::setDifficulty,
                                           "setConsoleAllowed", &GameSettings::setConsoleAllowed,
                                           "setBedRestAllowed", &GameSettings::setBedRestAllowed,
                                           "setWildernessRestAllowed", &GameSettings::setWildernessRestAllowed,
                                           "setWaitAllowed", &GameSettings::setWaitAllowed
    );
}

GameSettings::GameSettings(Player *player) : BaseMgr(player)
{

}

void GameSettings::setConsoleAllowed(bool state)
{
    player->consoleAllowed = state;
    setChanged();
}

void GameSettings::setDifficulty(int difficulty)
{
    player->difficulty = difficulty;
    setChanged();
}

void GameSettings::setBedRestAllowed(bool state)
{
    player->bedRestAllowed = state;
    setChanged();
}

void GameSettings::setWildernessRestAllowed(bool state)
{
    player->wildernessRestAllowed = state;
    setChanged();
}

void GameSettings::setWaitAllowed(bool state)
{
    player->waitAllowed = state;
    setChanged();
}

void GameSettings::processUpdate()
{
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_SETTINGS);
    packet->setPlayer(player);
    packet->Send(false);
}
