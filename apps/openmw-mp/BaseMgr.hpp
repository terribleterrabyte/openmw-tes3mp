//
// Created by koncord on 02.01.18.
//

#pragma once

class Player;

class BaseMgr
{
public:
    explicit BaseMgr(Player *player);
    void update();
protected:
    bool isChanged() const { return changed; };
    void setChanged();
    virtual void processUpdate() = 0;
    Player *player;
private:
    bool changed;
};
