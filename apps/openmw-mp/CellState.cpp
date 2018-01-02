//
// Created by koncord on 25.08.17.
//

#include "Script/LuaState.hpp"

#include "CellState.hpp"

#include <utility>

void CellState::Init(LuaState &lua)
{
    lua.getState()->new_usertype<CellState>("CellState",
                                            "type", sol::property(&CellState::getStateType),
                                            "description", sol::property(&CellState::getDescription)
    );
}

CellState::CellState(mwmp::CellState state) : state(std::move(state))
{

}

mwmp::CellState::Type CellState::getStateType() const
{
    return state.type;
}

std::string CellState::getDescription() const
{
    return state.cell.getDescription();
}
