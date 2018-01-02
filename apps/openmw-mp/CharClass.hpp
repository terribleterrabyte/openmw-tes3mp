//
// Created by koncord on 12.08.17.
//

#pragma once

#include <string>
#include <tuple>
#include "BaseMgr.hpp"

class LuaState;
class Player;

class CharClass final: public BaseMgr
{
public:
    static void Init(LuaState &lua);

public:
    explicit CharClass(Player *player);

    std::string getDefault() const;
    void setDefault(const std::string &className);
    bool isCustom() const;

    std::string getName() const;
    void setName(const std::string &className);

    std::string getDescription() const;
    void setDescription(const std::string &desc);

    std::tuple<int, int> getMajorAttributes() const;
    void setMajorAttributes(int first, int second);

    int getSpecialization() const;
    void setSpecialization(int spec);

    std::tuple<int, int, int, int, int> getMinorSkills() const;
    void setMinorSkills(int fisrt, int second, int third, int fourth, int fifth);

    std::tuple<int, int, int, int, int> getMajorSkills() const;
    void setMajorSkills(int fisrt, int second, int third, int fourth, int fifth);

private:
    void processUpdate() final;
};


