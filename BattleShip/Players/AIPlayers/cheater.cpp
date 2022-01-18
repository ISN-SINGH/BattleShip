//
// Created by Sage Zimmerman on 5/18/21.
//

#include "cheater.h"

namespace BattleShip {

    cheaterAI::cheaterAI(board& player_board, int designation,
                         const std::vector<std::vector<char>>& other_player_content_of_board)
                         : baseAI(player_board, designation),
                         other_player_content_of_board(other_player_content_of_board) {

    }


    // Finds location of ships on other player's board
    void cheaterAI::FindPossibleAttackLocations() {
        int rows = GetBoard().GetNumRows();
        int cols = GetBoard().GetNumCols();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (other_player_content_of_board.at(i).at(j) != '*') {
                    possible_attack_locations.emplace_back(i, j);
                }
            }
        }
    }


    // Asks cheaterAI for attack coord from front of possible_attack_locations
    coord cheaterAI::AskAttackCoord() {
        static bool alreadyFoundAttackLocations = false;
        if (not alreadyFoundAttackLocations) {
            FindPossibleAttackLocations();
            alreadyFoundAttackLocations = true;
        }
        auto attack_location = possible_attack_locations.front();
        DeleteAttackLocation(attack_location);
        return attack_location;
    }

}