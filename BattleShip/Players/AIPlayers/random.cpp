//
// Created by Sage Zimmerman on 5/18/21.
//

#include "random.h"


namespace BattleShip {

    randomAI::randomAI(board& boardObj, int designation) : baseAI(boardObj, designation) {

    }


    // Gets Random coord for randomAI and sadAI
    coord randomAI::GetRandFiringCoord() {
        const int index = GetRandomFiringIndex();
        auto attack_coord = possible_attack_locations.at(index);
        DeleteAttackLocation(attack_coord);  // erases attack location
        return attack_coord;
    }


    // Gets index of random coord in list of possible_attack_locations
    const int randomAI::GetRandomFiringIndex() const {  // max size shrinks every turn
        int max_size = possible_attack_locations.size() - 1;
        int rand_int = getRandomInt(0, max_size, rng);
        return rand_int;
    }


    // Finds initial possible attack locations in a new board
    void randomAI::FindPossibleAttackLocations() {
        for (int i = 0; i < boardObj.GetNumRows(); ++i) {
            for (int j = 0; j < boardObj.GetNumCols(); ++j) {
                possible_attack_locations.emplace_back(i, j);
            }
        }
    }


    // Asks attack coordinates for randomAI
    coord randomAI::AskAttackCoord() {
        coord attack_coord = GetRandFiringCoord();
        DeleteAttackLocation(attack_coord);
        return attack_coord;
    }

}