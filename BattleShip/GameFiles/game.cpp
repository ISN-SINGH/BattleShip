//
// Created by ishan on 5/11/2021.
//


#include "game.h"

namespace BattleShip {
    using player_ptr = std::unique_ptr<BattleShip::player>;

    // Runs after the game has been set up
    void PlayGame(player_ptr &p1ptr, player_ptr &p2ptr) {
        while (true) {
            int index_of_ship_hit = -1;
            bool shipWasDestroyed;

            coord attack_coord = p1ptr->AskAttackCoord();
            shipWasDestroyed = p1ptr->AttackShip(p2ptr, attack_coord, index_of_ship_hit);
            HitOrMissResponse(p1ptr, p2ptr, shipWasDestroyed, index_of_ship_hit, attack_coord);
            if (not GameMustContinue(p1ptr, p2ptr)) {
                std::cout << p1ptr->GetName() << " won the game!" << std::endl;
                break;
            }

            attack_coord = p2ptr->AskAttackCoord();
            shipWasDestroyed = p2ptr->AttackShip(p1ptr, attack_coord, index_of_ship_hit);
            HitOrMissResponse(p2ptr, p1ptr, shipWasDestroyed, index_of_ship_hit, attack_coord);
            if (not GameMustContinue(p1ptr, p2ptr)) {
                std::cout << std::endl << p2ptr->GetName() << " won the game!" << std::endl;
                break;
            }
        }
    }


    // Outputs firing board and placement board after shots have been fired by player
    // Informs player if they have hit a ship or missed and if a ship is destroyed
    void HitOrMissResponse (player_ptr& p1ptr, player_ptr& p2ptr, bool& shipWasDestroyed, int& index_of_ship_hit, const coord& attack_coord) {
        if (index_of_ship_hit == -1) {  // no ship hit
            p1ptr->SetBoard().ShotMissed(attack_coord);
            p1ptr->PrintFiringBoard(1);
            p1ptr->PrintFullBoard(1);
            std::cout << "Missed." << std::endl << std::endl;
        } else {  // ship hit
            p1ptr->SetBoard().ShotHit(attack_coord);
            p1ptr->PrintFiringBoard(1);
            p1ptr->PrintFullBoard(1);
            char ship_type = p2ptr->GetBoard().GetShipsRemaining().at(index_of_ship_hit).GetShipType();
            std::cout << p1ptr->GetName() << " hit " << p2ptr->GetName() << "'s " << ship_type << "!" << std::endl;
            if (shipWasDestroyed) {  // ship hit and destroyed
                std::cout << p1ptr->GetName() << " destroyed " << p2ptr->GetName() << "'s " << ship_type << "!"
                          << std::endl;
                p2ptr->SetBoard().RemoveDestroyedShip(index_of_ship_hit);
            }
            std::cout << std::endl;
        }
    }


    // Game will only end if either player's ships have all been destroyed
    bool GameMustContinue(player_ptr &p1ptr, player_ptr &p2ptr) {
        return (not p1ptr->GetBoard().AllShipsDestroyed()) &&
               (not p2ptr->GetBoard().AllShipsDestroyed());
    }


    // Checks that both row and col coordinates are integers
    bool PairIsInts(std::string &row_coord, std::string &col_coord) {
        for (const char& letter : row_coord) {
            if (not std::isdigit(letter)) {
                return false;
            }
        }

        for (const char& letter : col_coord) {
            if (not std::isdigit(letter)) {
                return false;
            }
        }
        return true;
    }
}