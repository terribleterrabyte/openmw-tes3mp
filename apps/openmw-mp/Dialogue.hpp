//
// Created by koncord on 15.08.17.
//

#pragma once

#include <string>
#include "BaseMgr.hpp"

class LuaState;
class Player;

class Dialogue final: public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:
    explicit Dialogue(Player *player);

    void addTopic(const std::string &topicId);
    std::string getTopicId(unsigned int i) const;
    size_t size() const;

    void playAnimation(const std::string &groupname, int mode, int count, bool persist);
    void playSpeech(const std::string &sound);

    void reset();
private:
    void processUpdate() final;
};


