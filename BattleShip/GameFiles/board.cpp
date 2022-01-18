#include "board.h"
#include <algorithm>

namespace BattleShip {
    // Board constructor that also initializes blank 2D char vector
    board::board(const int &board_rows, const int &board_cols, const std::vector<std::pair<char, int>> &ship_details) :
            num_cols(board_cols), num_rows(board_rows), ship_details(ship_details) {
        std::vector<char> temp_line;

        for (int j = 0; j < board_cols; ++j) {
            temp_line.push_back('*');
        }

        for (int i = 0; i < board_rows; ++i) {
            contents_of_board.push_back(temp_line);
            firing_board.push_back(temp_line);
        }
    }


    // Gets rid of a ship from ships_remaining if it is fully destroyed
    bool board::AllShipsDestroyed() const {
        return ships_remaining.empty();
    }


    // Fires at given coordinate
    // If a ship is hit, index_of_ship will be set to the index of the ship that was hit in ships remaining
    // If no ship is hit index_of_ship will be -1
    // If the ship that was hit was destroyed return true, else if no ship was hit or ship was not destroyed return false
    bool board::FireAtBoard(coord attack_coord, int &index_of_ship) {
        for (int i = 0; i < ships_remaining.size(); ++i) {
            const auto &curr_ship = ships_remaining.at(i);
            if (curr_ship.wasHit(attack_coord)) {
                index_of_ship = i;  // ship hit
                contents_of_board.at(attack_coord.first).at(attack_coord.second) = 'X';
                if (curr_ship.IsDestroyed(*this)) {
                    return true;  // ship hit and destroyed
                }
                return false;  // ship hit but not destroyed
            }
        }
        index_of_ship = -1; // no ship hit
        contents_of_board.at(attack_coord.first).at(attack_coord.second) = 'O';
        return false;
    }


    // Gets rid of a ship from ships_remaining if it is fully destroyed
    void board::RemoveDestroyedShip(const int &ship_index) {
        ships_remaining.erase(ships_remaining.begin() + ship_index);
    }


    // Adds a ship to ship_remaining and prints it to the contents_of_board
    // Uses the first ship from ship_details, once used removes it
    void board::MakeShip(const coord &start_coord, const char &orientation) {
        char ship_type = ship_details.front().first;
        int ship_length = ship_details.front().second;
        coord end_coord = FindEndCoord(ship_length, start_coord, orientation);
        ship_details.erase(ship_details.begin());  // no longer needed

        ships_remaining.emplace_back(ship_type, start_coord, end_coord);
        PlaceOnBoard(ships_remaining.back());
    }


    // Calculates the end coordinate of a ship prior to constructing ship object
    coord board::FindEndCoord(int ship_length, coord start_coord, char orientation) const {
        if (orientation == 'h') {
            int end_col = start_coord.second + (ship_length - 1);
            return std::make_pair(start_coord.first, end_col);
        } else {  // must be 'v'
            int end_row = start_coord.first + (ship_length - 1);
            return std::make_pair(end_row, start_coord.second);
        }
    }


    // Removes first element of ship_details
    const std::vector<ship>& board::GetShipsRemaining() const {
        return ships_remaining;
    }


    // Places ship onto contents_of_board using orientation
    void board::PlaceOnBoard(const ship &temp_ship) {
        int start_row, start_col, end_row, end_col;
        start_row = temp_ship.GetStartCoord().first;
        start_col = temp_ship.GetStartCoord().second;
        end_row = temp_ship.GetEndCoord().first;
        end_col = temp_ship.GetEndCoord().second;

        if (start_row == end_row) {  // put ship horizontally
            for (int col = start_col; col <= end_col; ++col) {
                contents_of_board.at(start_row).at(col) = temp_ship.GetShipType();
            }
        } else if (start_col == end_col) {  // put ship vertically
            for (int row = start_row; row <= end_row; ++row) {
                contents_of_board.at(row).at(start_col) = temp_ship.GetShipType();
            }
        }

    }


    // Allows public users to read from ship_details but not edit
    const std::vector<std::pair<char, int>> &board::GetShipDetails() const {
        return ship_details;
    }


    // Gets Contents of board for public users
    const std::vector<std::vector<char>>& board::GetContents() const {
        return contents_of_board;
    }


    // Gets the firing board contents for public users
    const std::vector<std::vector<char>>& board::GetFiringBoard() const {
        return firing_board;
    }


    // Gets the number of rows for public users
    const int &board::GetNumRows() const {
        return num_rows;
    }


    // Gets the number of columns for public users
    const int &board::GetNumCols() const {
        return num_cols;
    }


    // Makes sur that a coordinate the player enters is within bounds
    const bool board::areCoordsInBounds(const int &row_coord, const int &col_coord) const {
        return (row_coord < GetNumRows() && row_coord >= 0 &&
                col_coord < GetNumCols() && col_coord >= 0);
    }


    // Updates firing board to have a miss at given attack coordinate
    void board::ShotMissed(const coord &attack_coord) {
        firing_board.at(attack_coord.first).at(attack_coord.second) = 'O';
    }


    // Updates firing board to have a hit at given attack coordinate
    void board::ShotHit(const coord &attack_coord) {
        firing_board.at(attack_coord.first).at(attack_coord.second) = 'X';
    }


    // Used in input validation to make sure that player is not attacking a tile they have already attacked
    bool board::CoordWasAttacked(const coord &attack_coord) const {
        return (firing_board.at(attack_coord.first).at(attack_coord.second) != '*');
    }


    // Sorts ship_details in ASCII order
    void board::SortShipDetails() {
        std::sort(ship_details.begin(), ship_details.end(), SortAlgorithm);
    }


    // Shorts ships to place on board in alphabetical order
    bool board::SortAlgorithm(std::pair<char, int> &s1, std::pair<char, int> &s2) {
        return s1.first < s2.first;
    }
}
