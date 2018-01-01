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
                                           "setBedRestAllowed", &GameSettings::setConsoleAllowed,
                                           "setWildernessRestAllowed", &GameSettings::setWildernessRestAllowed,
                                           "setWaitAllowed", &GameSettings::setWaitAllowed
    );
}

GameSettings::GameSettings(Player *player) : player(player), changed(false)
{

}

GameSettings::~GameSettings()
{
}

void GameSettings::setConsoleAllowed(bool state)
{
    player->consoleAllowed = state;
    changed = true;
}

void GameSettings::setDifficulty(int difficulty)
{
    player->difficulty = difficulty;
    changed = true;
}

void GameSettings::setBedRestAllowed(bool state)
{
    player->bedRestAllowed = state;
    changed = true;
}

void GameSettings::setWildernessRestAllowed(bool state)
{
    player->wildernessRestAllowed = state;
    changed = true;
}

void GameSettings::setWaitAllowed(bool state)
{
    player->waitAllowed = state;
    changed = true;
}

void GameSettings::update()
{
    if (!changed)
        return;
    changed = false;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GAME_SETTINGS);
    packet->setPlayer(player);
    packet->Send(false);
}
