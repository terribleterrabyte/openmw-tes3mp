//
// Created by koncord on 15.08.17.
//

#pragma once

#include <string>
#include "BaseMgr.hpp"

class LuaState;
class Player;

class Books final: public BaseMgr
{
public:
    static void Init(LuaState &lua);
public:
    explicit Books(Player *player);
    void addBook(const std::string &bookId);
    std::string getBookId(unsigned i) const;
    unsigned getChanges() const;
    void reset();

private:
    void processUpdate() final;
};
