//
// Created by Sage Zimmerman on 5/18/21.
//

#include "search_destroy.h"

namespace BattleShip {

    sadAI::sadAI(board& boardObj, int designation) : randomAI(boardObj, designation), attack_mode(false) {

    }


    //  Attacks other player's ships, activates destroy mode when a ship is hit
    bool sadAI::AttackShip(player_ptr &other_player, coord &attack_coord, int &index_of_ship) {
        bool ship_destroyed = other_player->SetBoard().FireAtBoard(attack_coord, index_of_ship);
        if (IsLocationShip(attack_coord, other_player)) {
            BuildDestroyQueue(attack_coord);
            ActivateDestroyMode();
        }
        if (destroy_queue.empty()) {
            ActivateSearchMode();
        }
        return ship_destroyed;
    }


    // Asks the attack coordinates for sadAI
    coord sadAI::AskAttackCoord() {
        if (attack_mode) {
            auto attack_coord = destroy_queue.front();
            destroy_queue.erase(destroy_queue.begin());
            DeleteAttackLocation(attack_coord);
            return attack_coord;
        } else {
            return GetRandFiringCoord();  // deletes attacked location
        }
    }


    // If the coord to attack is present in destroy queue, returns true
    bool sadAI::CoordPresentInQueue(const coord& attack_coord) const {
        for (const coord& queue_coord : destroy_queue) {
            if (queue_coord.first == attack_coord.first and queue_coord.second == attack_coord.second) {
                return true;
            }
        }
        return false;
    }


    // Turns attack mode to true. Activates destroy mode
    void sadAI::ActivateDestroyMode() {
        attack_mode = true;
    }


    // Turns attack mode to false. Attacks board randomly
    void sadAI::ActivateSearchMode() {
        attack_mode = false;
    }


    // Checks a location in the other player's board is a ship
    bool sadAI::IsLocationShip(coord &hit_ship_coord, player_ptr &other_player) {
        return !(other_player->GetBoard().GetContents().at(hit_ship_coord.first).at(hit_ship_coord.second) == '*' or
                 other_player->GetBoard().GetContents().at(hit_ship_coord.first).at(hit_ship_coord.second) == 'O');
    }


    // Validates coord to be added to destroy queue is in bounds and hasn't been fired at
    bool sadAI::DestroyCoordValidation(coord destroy_ship_coord) {
        if (boardObj.areCoordsInBounds(destroy_ship_coord.first, destroy_ship_coord.second) &&
            !(boardObj.CoordWasAttacked(destroy_ship_coord))) {
            return true;
        }
        return false;
    }


    // Adds new coords to the destroy queue
    void sadAI::AddCoordToDestroyQ(int row_coord, int col_coord) {
        coord destroy_ship_coord = std::make_pair(row_coord, col_coord);
        if (DestroyCoordValidation(destroy_ship_coord)) {
            destroy_queue.push_back(destroy_ship_coord);
        }
    }


    // Makes and adds to destroy queue in destroy mode
    void sadAI::BuildDestroyQueue(coord hit_ship_coord) {
        int row_coord = hit_ship_coord.first;
        int col_coord = hit_ship_coord.second;

        auto coord_left = std::make_pair(row_coord, col_coord - 1);
        auto coord_up = std::make_pair(row_coord - 1, col_coord);
        auto coord_right = std::make_pair(row_coord, col_coord + 1);
        auto coord_down = std::make_pair(row_coord + 1, col_coord);

        std::vector<coord> temp = {coord_left, coord_up, coord_right, coord_down};
        for (coord& temp_coord : temp) {
            if (not CoordPresentInQueue(temp_coord)) {
                AddCoordToDestroyQ(temp_coord.first, temp_coord.second);
            }
        }
    }
}
