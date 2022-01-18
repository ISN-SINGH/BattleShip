#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include <utility>

namespace BattleShip {
    using coord = std::pair<int, int>;

    class board;

    class ship {
    public:
        ship(char ship_type, coord start_coord, coord end_coord);

        bool IsDestroyed(const board &player_board) const;

        const coord &GetStartCoord() const;

        const coord &GetEndCoord() const;

        const char &GetShipType() const;

        bool wasHit(const coord &attackCoord) const;

        char GetOrientation() const;

    private:
        char ship_type;

        coord start_coord;

        coord end_coord;
    };
}

#endif
