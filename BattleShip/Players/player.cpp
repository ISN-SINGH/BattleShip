#include "player.h"


namespace BattleShip {
    player::player(board& boardObj) : boardObj(boardObj) {

    }

    const board& player::GetBoard() const {
        return boardObj;
    }


    board& player::SetBoard() {
        return boardObj;
    }

    // Used by both player and ai coord validation to make sure that any new ships being placed do not overlap
    //      with ships that have already been placed
    bool player::CheckShipOverlap(const int& coord1_int, const int& coord2_int, const char& orientation) const {
        for (const auto& ship : boardObj.GetShipsRemaining()) {
            char board_ship_orientation = ship.GetOrientation();
            int our_ship_length = boardObj.GetShipDetails().front().second;
            if (board_ship_orientation == 'h') {  // checks for overlap if ship on board is horizontal
                if (orientation == 'h') {  // ship being placed is horizontal
                    for (int i = ship.GetStartCoord().second; i <= ship.GetEndCoord().second; ++i) {
                        for (int j = 0; j < our_ship_length; ++j) {
                            if (coord2_int + j == i and coord1_int == ship.GetStartCoord().first) {
                                return false;
                            }
                        }
                    }
                } else {  // ship being placed is vertical
                    for (int i = ship.GetStartCoord().second; i <= ship.GetEndCoord().second; ++i) {
                        for (int j = 0; j < our_ship_length; ++j) {
                            if (coord1_int + j == ship.GetStartCoord().first and coord2_int == i) {
                                return false;
                            }
                        }
                    }
                }
            } else {  // checks for overlap if ship on board is vertical
                if (orientation == 'h') {
                    for (int i = ship.GetStartCoord().first; i <= ship.GetEndCoord().first; ++i) {
                        for (int j = 0; j < our_ship_length; ++j) {
                            if (coord2_int + j == ship.GetStartCoord().second and coord1_int == i) {
                                return false;
                            }
                        }
                    }
                } else {
                    for (int i = ship.GetStartCoord().first; i <= ship.GetEndCoord().first; ++i) {
                        for (int j = 0; j < our_ship_length; ++j) {
                            if (coord1_int + j == i and coord2_int == ship.GetStartCoord().second) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    // Used by both AIs and humans to attack the opponent's ship
    bool player::AttackShip(player_ptr &other_player, coord &attack_coord, int &index_of_ship) {
        bool ship_destroyed = other_player->SetBoard().FireAtBoard(attack_coord, index_of_ship);
        return ship_destroyed;
    }

}