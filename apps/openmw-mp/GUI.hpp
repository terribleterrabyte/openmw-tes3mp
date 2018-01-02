//
// Created by koncord on 15.08.17.
//

#pragma once

#include "Window.hpp"

class LuaState;
class Player;

class GUI
{
public:
    static void Init(LuaState &lua);
public:
    explicit GUI(Player *player);
    ~GUI();

    void update();

    void messageBox(int id, const char *label);

    void customMessageBox(int id, const char *label, const char *buttons);
    void inputDialog(int id, const char *label);
    void passwordDialog(int id, const char *label, const char *note);

    void listBox(int id, const char *label, const char *items);

    //state 0 - disallow, 1 - allow
    void setMapVisibility(unsigned short targetPID, unsigned short affectedPID, unsigned short state);
    void setMapVisibilityAll(unsigned short targetPID, unsigned short state);

    std::shared_ptr<Window> createWindow(short x, short y, sol::function fn, sol::this_environment te);
    void deleteWindow(std::shared_ptr<Window> window);
    void onGUIWindowAction();

    void addQuickKey(unsigned short slot, int type, const std::string &itemId);
    std::string getTopicId(unsigned int i) const;
    unsigned int getChanges() const;

private:
    Player *player;
    bool changed;
    std::unordered_map<int, std::shared_ptr<Window>> windows;
    int lastWindowId;
};

class QuickKey
{
    friend class QuickKeys;
public:
    static void Init(LuaState &lua);
public:
    explicit QuickKey(mwmp::QuickKey &quickKey);

    int getSlot() const;
    void setSlot(unsigned short slot);

    int getType() const;
    void setType(int slot);

    std::string getItemId() const;
    void setItemId(const std::string &itemId);

    mwmp::QuickKey quickKey;
};

class QuickKeys
{
public:
    static void Init(LuaState &lua);
public:
    explicit QuickKeys(Player *player);
    ~QuickKeys();

    void update();

    void addQuickKey(const QuickKey &quickKey);
    QuickKey getQuickKey(int id) const;
    void setQuickKey(int id, const QuickKey &quickKey);
    size_t size() const;
    void clear();

private:
    Player *player;
    bool changed;
};
