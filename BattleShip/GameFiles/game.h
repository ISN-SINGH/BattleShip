#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H


#include "../Players/player.h"
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <memory>
namespace BattleShip {
    using player_ptr = std::unique_ptr<BattleShip::player>;

    void PlayGame(player_ptr &p1ptr, player_ptr &p2ptr);

    bool GameMustContinue(player_ptr &p1ptr, player_ptr &p2ptr);

    bool PairIsInts(std::string &row_coord, std::string &col_coord);

    void HitOrMissResponse(player_ptr &p1ptr, player_ptr &p2ptr, bool &shipWasDestroyed, int &index_of_ship_hit,
                           const coord &attack_coord);
}


#endif
