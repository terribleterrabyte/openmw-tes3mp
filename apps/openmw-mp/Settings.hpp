//
// Created by koncord on 12.08.17.
//

#pragma once

#include "BaseMgr.hpp"

class LuaState;
class Player;


class GameSettings final: public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:

    explicit GameSettings(Player *player);

    void setConsoleAllowed(bool state);

    void setDifficulty(int difficulty);

    void setBedRestAllowed(bool state);

    void setWildernessRestAllowed(bool state);

    void setWaitAllowed(bool state);


private:
    void processUpdate() final;
};