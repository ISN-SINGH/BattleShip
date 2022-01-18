//
// Created by Sage Zimmerman on 5/18/21.
//

#ifndef BATTLESHIP_CHEATER_H
#define BATTLESHIP_CHEATER_H

#include "../ai_player.h"

namespace BattleShip {
    class cheaterAI : public baseAI {
    public:
        cheaterAI(board &player_board, int designation,
                  const std::vector<std::vector<char>> &other_player_content_of_board);

        void FindPossibleAttackLocations() override;

        coord AskAttackCoord() override;

    private:
        const std::vector<std::vector<char>> &other_player_content_of_board;
    };
}

#endif //BATTLESHIP_CHEATER_H
