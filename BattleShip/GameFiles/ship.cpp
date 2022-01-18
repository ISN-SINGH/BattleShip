#include "ship.h"
#include "board.h"

namespace BattleShip {

    ship::ship(char ship_type, coord start_coord, coord end_coord) :
            ship_type(ship_type), start_coord(start_coord), end_coord(end_coord) {

    }


    // Gets the start coordinate of the ship entered by player
    const coord& ship::GetStartCoord() const {
        return start_coord;
    }


    // Gets the last coordinate the ship ends on in the board after placement
    const coord& ship::GetEndCoord() const {
        return end_coord;
    }


    // Gets the ship name
    const char& ship::GetShipType() const {
        return ship_type;
    }


    // If all tiles that the ship lies on have been attacked, the ship was destroyed, return true
    bool ship::IsDestroyed(const board& player_board) const {
        const auto& board_contents = player_board.GetContents();

        if (GetOrientation() == 'h') {  // horizontal check
            for (int i = start_coord.second; i <= end_coord.second; ++i) {
                if (board_contents.at(start_coord.first).at(i) != 'X') {
                    return false;
                }
            }
            return true;
        } else {  // vertical check
            for (int i = start_coord.first; i <= end_coord.first; ++i) {
                if (board_contents.at(i).at(start_coord.second) != 'X') {
                    return false;
                }
            }
            return true;
        }
    }


    // Returns the orientation of the ship, either horizontal or vertical
    char ship::GetOrientation() const {
        if (start_coord.first == end_coord.first) {
            return 'h';
        } else {
            return 'v';
        }
    }


    // Given an attack coordinate, returns if the ship lies on that coordinate
    bool ship::wasHit(const coord& attackCoord) const {
        if (GetOrientation() == 'h') {
            if (attackCoord.first != start_coord.first) {  // rows don't match
                return false;
            } else {
                for (int i = start_coord.second; i <= end_coord.second; ++i) {
                    if (attackCoord.second == i) {
                        return true;
                    }
                }
                return false;
            }
        } else {
            if (attackCoord.second != start_coord.second) {  // columns don't match
                return false;
            } else {
                for (int i = start_coord.first; i <= end_coord.first; ++i) {
                    if (attackCoord.first == i) {
                        return true;
                    }
                }
                return false;
            }
        }
    }
}