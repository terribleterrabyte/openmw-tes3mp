//
// Created by koncord on 12.08.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>

#include "Script/LuaState.hpp"
#include "Networking.hpp"

#include "CharClass.hpp"
#include "Player.hpp"

using namespace std;

void CharClass::Init(LuaState &lua)
{
    lua.getState()->new_usertype<CharClass>("Class",
                                            //"__gc", sol::destructor(deleter),
                                            "default", sol::property(&CharClass::getDefault, &CharClass::setDefault),
                                            "isCustom", &CharClass::isCustom,

                                            "name", sol::property(&CharClass::getName, &CharClass::setName),
                                            "description", sol::property(&CharClass::getDescription, &CharClass::setDescription),
                                            "specialization",
                                            sol::property(&CharClass::getSpecialization, &CharClass::setSpecialization),

                                            "getMajorAttributes", &CharClass::getMajorAttributes,
                                            "setMajorAttributes", &CharClass::setMajorAttributes,

                                            "getMinorSkills", &CharClass::getMinorSkills,
                                            "setMinorSkills", &CharClass::setMinorSkills,

                                            "getMajorSkills", &CharClass::getMajorSkills,
                                            "setMajorSkills", &CharClass::setMajorSkills
    );
}

CharClass::CharClass(Player *player) : BaseMgr(player)
{
}

string CharClass::getDefault() const
{
    return player->charClass.mId;
}

void CharClass::setDefault(const string &className)
{
    player->charClass.mId = className;
    setChanged();
    printf("CharClass::setDefault()\n");
}

bool CharClass::isCustom() const
{
    return player->charClass.mId.empty();
}

void CharClass::setName(const string &className)
{
    player->charClass.mName = className;
    setChanged();
}

string CharClass::getName() const
{
    return player->charClass.mName;
}

std::string CharClass::getDescription() const
{
    return player->charClass.mDescription;
}

void CharClass::setDescription(const string &desc)
{
    player->charClass.mDescription = desc;
    setChanged();
}

std::tuple<int, int> CharClass::getMajorAttributes() const
{
    const auto &data = player->charClass.mData;
    return make_tuple(data.mAttribute[0], data.mAttribute[1]);
}

void CharClass::setMajorAttributes(int first, int second)
{
    auto &data = player->charClass.mData;
    data.mAttribute[0] = first;
    data.mAttribute[1] = second;
    setChanged();
}

int CharClass::getSpecialization() const
{
    return player->charClass.mData.mSpecialization;
}

void CharClass::setSpecialization(int spec)
{
    auto &data = player->charClass.mData;
    data.mSpecialization = spec;
    setChanged();
}

std::tuple<int, int, int, int, int> CharClass::getMinorSkills() const
{
    const auto &data = player->charClass.mData;
    return make_tuple( data.mSkills[0][0],  data.mSkills[1][0],  data.mSkills[2][0],  data.mSkills[3][0], data.mSkills[4][0]);
}

void CharClass::setMinorSkills(int first, int second, int third, int fourth, int fifth)
{
    auto &data = player->charClass.mData;
    data.mSkills[0][0] = first;
    data.mSkills[1][0] = second;
    data.mSkills[2][0] = third;
    data.mSkills[3][0] = fourth;
    data.mSkills[4][0] = fifth;
    setChanged();
}

std::tuple<int, int, int, int, int> CharClass::getMajorSkills() const
{
    const auto &data = player->charClass.mData;
    return make_tuple( data.mSkills[0][1],  data.mSkills[1][1],  data.mSkills[2][1],  data.mSkills[3][1], data.mSkills[4][1]);
}

void CharClass::setMajorSkills(int first, int second, int third, int fourth, int fifth)
{
    auto &data = player->charClass.mData;
    data.mSkills[0][1] = first;
    data.mSkills[1][1] = second;
    data.mSkills[2][1] = third;
    data.mSkills[3][1] = fourth;
    data.mSkills[4][1] = fifth;
    setChanged();
}

void CharClass::processUpdate()
{
    printf("CharClass::update()\n");
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_CHARCLASS);
    packet->setPlayer(player);
    packet->Send(false);
}
