//
// Created by Sage Zimmerman on 5/18/21.
//

#ifndef BATTLESHIP_RANDOM_H
#define BATTLESHIP_RANDOM_H

#include "../player.h"
#include "../ai_player.h"
#include <random>

namespace BattleShip {

    class randomAI : public baseAI {
    public:
        randomAI(board &boardObj, int designation);

        coord AskAttackCoord() override;

    protected:
        coord GetRandFiringCoord();

        void FindPossibleAttackLocations() override;

    private:
        const int GetRandomFiringIndex() const;
    };
}


#endif //BATTLESHIP_RANDOM_H
