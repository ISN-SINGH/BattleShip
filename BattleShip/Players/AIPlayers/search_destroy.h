//
// Created by Sage Zimmerman on 5/18/21.
//

#ifndef BATTLESHIP_SEARCH_DESTROY_H
#define BATTLESHIP_SEARCH_DESTROY_H

#include "../ai_player.h"
#include "random.h"

namespace BattleShip {

    class sadAI : public randomAI {
    public:
        sadAI(board &boardObj, int designation);

        coord AskAttackCoord() override;

        bool AttackShip(player_ptr &other_player, coord &attack_coord, int &index_of_ship) override;

    private:
        void ActivateDestroyMode();

        void ActivateSearchMode();

        bool CoordPresentInQueue(const coord &attack_coord) const;

        bool IsLocationShip(coord &hit_ship_coord, player_ptr &other_player);

        void AddCoordToDestroyQ(int row_coord, int col_coord);

        bool DestroyCoordValidation(coord destroy_ship_coord);

        void BuildDestroyQueue(coord hit_ship_coord);

        std::vector<coord> destroy_queue;

        bool attack_mode;
    };
}


#endif //BATTLESHIP_SEARCH_DESTROY_H
