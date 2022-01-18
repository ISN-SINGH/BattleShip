//
// Created by Sage Zimmerman on 5/18/21.
//

#ifndef BATTLESHIP_AI_PLAYER_H
#define BATTLESHIP_AI_PLAYER_H

#include "player.h"
#include <random>
#include <iostream>

namespace BattleShip {

    using player_ptr = std::unique_ptr<BattleShip::player>;
    typedef std::mersenne_twister_engine<uint_fast32_t,
            32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253>
            mt19937;


    template<typename mt19937>
    int getRandomInt(int min, int max, mt19937 &rng) {
        std::uniform_int_distribution<int> dist(min, max);
        int random_num = dist(rng);
        return random_num;
    }


    class baseAI : public player {
    public:
        static mt19937 rng;

        baseAI(board &boardObj, int designation);

        void PrintFullBoard(int during_game) const override;

        void PrintFiringBoard(int during_game) const override;

        virtual void FindPossibleAttackLocations() = 0;

        void SetupPlayer(int player_num = 0) override;

        const std::string GetName() const override;

    protected:
        std::vector<coord> possible_attack_locations;
        int designation;

        void DeleteAttackLocation(const coord &attack_location);

    private:
        const int FindPossibleColPlacement(int ship_length, char orientation) const;

        const int FindPossibleRowPlacement(int ship_length, char orientation) const;

        const coord GetRandomShipPlacementCoord(int ship_length, char orientation) const;

        char AIOrientationSelection();
    };
}

#endif //BATTLESHIP_AI_PLAYER_H
