#ifndef OPENMW_SERVERCELLCONTROLLER_HPP
#define OPENMW_SERVERCELLCONTROLLER_HPP

#include <deque>
#include <string>
#include <components/esm/records.hpp>
#include <components/openmw-mp/Base/BaseEvent.hpp>
#include <components/openmw-mp/Packets/Actor/ActorPacket.hpp>
#include <components/openmw-mp/Packets/Object/ObjectPacket.hpp>

class Player;
class Cell;


class CellController
{
private:
    CellController() = default;
    ~CellController();
public:
    CellController(const CellController&) = delete;
    CellController(CellController&&) = delete;
    CellController& operator=(const CellController&) = delete;
    CellController& operator=(CellController&&) = delete;

    static CellController &get();
public:
    typedef std::deque<Cell*> TContainer;
    typedef TContainer::iterator TIter;

    Cell *addCell(const ESM::Cell &cellData);
    void removeCell(Cell *);

    void removePlayer(Cell *cell, Player *player);
    void deletePlayer(Player *player);

    Cell *getCell(const ESM::Cell &esmCell);
    Cell *getCellByXY(int x, int y);
    Cell *getCellByName(const std::string &cellName);

    void update(Player *player);

private:
    TContainer cells;
};

#endif //OPENMW_SERVERCELLCONTROLLER_HPP
