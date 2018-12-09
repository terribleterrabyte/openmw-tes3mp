//
// Created by koncord on 29.08.16.
//

#include "CharClass.hpp"

#include <components/openmw-mp/NetworkMessages.hpp>

#include <apps/openmw-mp/Networking.hpp>
#include <apps/openmw-mp/Script/ScriptFunctions.hpp>

using namespace std;
using namespace ESM;

extern "C" const char *CharClassFunctions::GetDefaultClass(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->charClass.mId.c_str();
}

extern "C" const char *CharClassFunctions::GetClassName(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->charClass.mName.c_str();
}

extern "C" const char *CharClassFunctions::GetClassDesc(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, "");

    return player->charClass.mDescription.c_str();
}

extern "C" int CharClassFunctions::GetClassMajorAttribute(unsigned short pid, unsigned char slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (slot > 1)
        throw invalid_argument("Incorrect attribute slot id");

    return player->charClass.mData.mAttribute[slot];
}

extern "C" int CharClassFunctions::GetClassSpecialization(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return player->charClass.mData.mSpecialization;
}

extern "C" int CharClassFunctions::GetClassMajorSkill(unsigned short pid, unsigned char slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (slot > 4)
        throw invalid_argument("Incorrect skill slot id");

    return player->charClass.mData.mSkills[slot][1];
}

extern "C" int CharClassFunctions::GetClassMinorSkill(unsigned short pid, unsigned char slot) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    if (slot > 4)
        throw invalid_argument("Incorrect skill slot id");

    return player->charClass.mData.mSkills[slot][0];
}

extern "C" int CharClassFunctions::IsClassDefault(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, 0);

    return !player->charClass.mId.empty(); // true if default
}

extern "C" void CharClassFunctions::SetDefaultClass(unsigned short pid, const char *id) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->charClass.mId = id;
}

extern "C" void CharClassFunctions::SetClassName(unsigned short pid, const char *name) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->charClass.mName = name;
    player->charClass.mId = "";
}

extern "C" void CharClassFunctions::SetClassDesc(unsigned short pid, const char *desc) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->charClass.mDescription = desc;
}

extern "C" void CharClassFunctions::SetClassMajorAttribute(unsigned short pid, unsigned char slot, int attrId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (slot > 1)
        throw invalid_argument("Incorrect attribute slot id");

    player->charClass.mData.mAttribute[slot] = attrId;

}

extern "C" void CharClassFunctions::SetClassSpecialization(unsigned short pid, int spec) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    player->charClass.mData.mSpecialization = spec;
}

extern "C" void CharClassFunctions::SetClassMajorSkill(unsigned short pid, unsigned char slot, int skillId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (slot > 4)
        throw invalid_argument("Incorrect skill slot id");

    player->charClass.mData.mSkills[slot][1] = skillId;
}

extern "C" void CharClassFunctions::SetClassMinorSkill(unsigned short pid, unsigned char slot, int skillId) noexcept
{
    Player *player;
    GET_PLAYER(pid, player,);

    if (slot > 4)
        throw invalid_argument("Incorrect skill slot id");

    player->charClass.mData.mSkills[slot][0] = skillId;
}

extern "C" void CharClassFunctions::SendClass(unsigned short pid) noexcept
{
    Player *player;
    GET_PLAYER(pid, player, );

    mwmp::PlayerPacket *packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_CHARCLASS);
    packet->setPlayer(player);

    packet->Send(false);
}
