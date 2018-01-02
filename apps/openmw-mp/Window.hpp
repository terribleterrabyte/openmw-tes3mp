//
// Created by koncord on 21.11.17.
//

#pragma once

#include <components/openmw-mp/Base/BasePlayer.hpp>
#include <apps/openmw-mp/Script/LuaState.hpp>
#include "BaseMgr.hpp"

class Player;

class Window final: public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:
    Window(Player *player, int id);


    void setSize(short x, short y);
    void setCallback(sol::function);

    int getID();

    void show();
    void clear();

    void call(const mwmp::BasePlayer::GUIWindow &window);

    void addButton(short x, short y, const std::string &label, sol::optional<bool> active);
    void addLabel(short x, short y, const std::string &label);
    void addEditBox(short x, short y, short w, short h, const std::string &id, sol::optional<bool> active);
    void addPassiveListBox(short x, short y, short w, short h,const std::string &id, sol::table data, sol::optional<bool> active);
    void addActiveListBox(short x, short y, short w, short h,const std::string &id, sol::table data, sol::optional<bool> active);
    void addSlider(short x, short y, short w, short h,const std::string &id, sol::optional<bool> active);

private:
    void processUpdate() final;
    sol::function callback;
    mwmp::BasePlayer::GUIWindow guiWindow;
};


