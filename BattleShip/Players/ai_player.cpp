//
// Created by Sage Zimmerman on 5/18/21.
//

#include "ai_player.h"
#include <sstream>

namespace BattleShip {

    baseAI::baseAI(board &boardObj, int designation) : designation(designation),
                                                       player(boardObj) {

    }


    // Firing Board output for all AIs
    void baseAI::PrintFiringBoard(int during_game = 0) const {
        if (during_game != 0) {  // only print owner during game
            std::cout << "AI " << designation << "'s Firing Board" << std::endl;
        }

        for (int i = 0; i < boardObj.GetNumCols(); ++i) {
            if (i == 0) {
                std::cout << "  " << i;
            } else {
                std::cout << " " << i;
            }
        }
        std::cout << " " << std::endl;

        for (int i = 0; i < boardObj.GetNumRows(); ++i) {
            std::cout << i << " ";
            for (int j = 0; j < boardObj.GetNumCols(); ++j) {
                std::cout << boardObj.GetFiringBoard().at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }

        if (during_game != 0) {
            std::cout << std::endl << std::endl;  // always 2 newlines after firing board
        }
    }


    // Prints board with ships for AIs
    void baseAI::PrintFullBoard(int during_game = 0) const {
        if (during_game != 0) { // only print owner during game
            std::cout << "AI " << designation << "'s Placement Board" << std::endl;
        } else {
            std::cout << "AI " << designation << "'s Board" << std::endl;
        }

        for (int i = 0; i < boardObj.GetNumCols(); ++i) {
            if (i == 0) {
                std::cout << "  " << i;
            } else {
                std::cout << " " << i;
            }
        }
        std::cout << " " << std::endl;

        for (int i = 0; i < boardObj.GetNumRows(); ++i) {
            std::cout << i << " ";
            for (int j = 0; j < boardObj.GetNumCols(); ++j) {
                std::cout << boardObj.GetContents().at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }
        if (during_game == 0) {
            std::cout << std::endl;
        }
    }


    // Sets up board (places ships) for all AI players
    void baseAI::SetupPlayer(int player_num) {
        do {
            char orientation;
            auto ship_pair = boardObj.GetShipDetails().front();
            coord placement_coord;
            do {
                orientation = AIOrientationSelection();
                placement_coord = GetRandomShipPlacementCoord(ship_pair.second, orientation);
            } while (!CheckShipOverlap(placement_coord.first, placement_coord.second, orientation));
            boardObj.MakeShip(placement_coord, orientation);
            PrintFullBoard();

        } while (not boardObj.GetShipDetails().empty());
        FindPossibleAttackLocations();
    }


    // Randomly selects an orientation for a ship
    char baseAI::AIOrientationSelection() {
        int random_integer = getRandomInt(0, 1, rng);
        if (random_integer == 0) {
            return 'h';
        } else {
            return 'v';
        }
    }


    // Gets random row and column location to place ships in for all AIs
    const coord baseAI::GetRandomShipPlacementCoord(int ship_length, char orientation) const {
        int max_row = FindPossibleRowPlacement(ship_length, orientation);
        int max_col = FindPossibleColPlacement(ship_length, orientation);
        int rand_row = getRandomInt(0, max_row, rng);
        int rand_col = getRandomInt(0, max_col, rng);

        return std::make_pair(rand_row, rand_col);
    }


    // Finds possible valid row locations depending on orientation
    const int baseAI::FindPossibleRowPlacement(int ship_length, char orientation) const {
        if (orientation == 'h') {
            return boardObj.GetNumRows() - 1;
        } else {
            return boardObj.GetNumRows() - ship_length;
        }
    }


    // Finds possible valid column locations depending on orientation
    const int baseAI::FindPossibleColPlacement(int ship_length, char orientation) const {
        if (orientation == 'h') {
            return boardObj.GetNumCols() - ship_length;
        } else {
            return boardObj.GetNumCols() - 1;
        }
    }


    // Deletes attacked location from vector of possible attack locations after usage
    void baseAI::DeleteAttackLocation(const coord &attack_location) {
        for (int i = 0; i < possible_attack_locations.size(); ++i) {
            const coord temp_coord = possible_attack_locations.at(i);
            if (temp_coord.first == attack_location.first and
                temp_coord.second == attack_location.second) {
                possible_attack_locations.erase(possible_attack_locations.begin() + i);
            }
        }
    }


    // Gets the name and designation (AI 1 or 2) of all AIs
    const std::string baseAI::GetName() const {
        std::stringstream write_to;
        write_to << "AI " << designation;
        return write_to.str();
    }

}
