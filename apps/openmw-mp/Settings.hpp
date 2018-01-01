//
// Created by koncord on 12.08.17.
//

#pragma once

class LuaState;
class Player;


class GameSettings
{
public:
    static void Init(LuaState &lua);
public:

    explicit GameSettings(Player *player);
    ~GameSettings();

    void setConsoleAllowed(bool state);

    void setDifficulty(int difficulty);

    void setBedRestAllowed(bool state);

    void setWildernessRestAllowed(bool state);

    void setWaitAllowed(bool state);

    void update();
private:
    Player *player;
    bool changed;
};