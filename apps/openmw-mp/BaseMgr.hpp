//
// Created by koncord on 02.01.18.
//

#pragma once

class Player;
class Worldstate;

class BaseMgr
{
public:
    explicit BaseMgr(Player *player);
    explicit BaseMgr(Worldstate *worldstate);
    void update();
protected:
    bool isChanged() const { return changed; };
    void setChanged();
    virtual void processUpdate() = 0;
    Player *player;
    Worldstate *worldstate;
private:
    bool changed;
};
