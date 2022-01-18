#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <vector>
#include <string>
#include "ship.h"


namespace BattleShip {
    using coord = std::pair<int, int>;

    class ship;

    class board {
    public:
        board(const int &board_rows, const int &board_cols, const std::vector<std::pair<char, int>> &ship_details);

        void MakeShip(const coord &start_coord, const char &orientation);

        const std::vector<std::pair<char, int>> &GetShipDetails() const;

        const std::vector<std::vector<char>> &GetContents() const;

        const std::vector<std::vector<char>> &GetFiringBoard() const;

        bool FireAtBoard(coord attack_coord, int &index_of_ship);

        void RemoveDestroyedShip(const int &ship_index);

        bool AllShipsDestroyed() const;

        const std::vector<ship> &GetShipsRemaining() const;

        const int &GetNumRows() const;

        const int &GetNumCols() const;

        const bool areCoordsInBounds(const int &row_coord, const int &col_coord) const;

        void ShotMissed(const coord &attack_coord);

        void ShotHit(const coord &attack_coord);

        bool CoordWasAttacked(const coord &attack_coord) const;

        void SortShipDetails();


    private:
        const int num_cols;

        const int num_rows;

        std::vector<std::vector<char>> contents_of_board; // the 2d board to print

        std::vector<std::vector<char>> firing_board;      // all attempted attacks

        std::vector<ship> ships_remaining;                // all ships that haven't been destroyed

        std::vector<std::pair<char, int>> ship_details;   // contains ship names and lengths in pairs

        static bool SortAlgorithm(std::pair<char, int> &s1, std::pair<char, int> &s2);

        void PlaceOnBoard(const ship &temp_ship);

        coord FindEndCoord(int ship_length, coord start_coord, char orientation) const;
    };
}


#endif
