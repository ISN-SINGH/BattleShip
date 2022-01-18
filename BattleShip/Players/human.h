#ifndef BATTLESHIP_HUMAN_H
#define BATTLESHIP_HUMAN_H

#include "player.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <chrono>

namespace BattleShip {
     using player_ptr = std::unique_ptr<BattleShip::player>;
        class human : public player {
        public:
            human(board& boardObj);

            void PrintFiringBoard(int during_game = 0) const override;

            void PrintFullBoard(int during_game = 0) const override;

            const std::string GetName() const override;

            void SetName(const std::string& name);

            coord AskAttackCoord() override;

            void SetupPlayer(int player_num) override;

            void EnterHuman(int player_num);

            void GetOrientAndCoords(char &orientation, coord &player_coords);

            char GetVertOrHor(bool &is_orientation_valid);

            coord AskPlayerCoords(bool &are_coords_valid, char &orientation, bool &is_format_valid);

            coord GetPlayerCoords(bool &are_coords_valid, char &orientation, bool &is_format_valid);

            bool CoordValidation(const std::string& row_coord, const std::string& col_coord,
                                 int& coord1_int, int& coord2_int, char& orientation, bool &is_format_valid);

            bool CheckOutOfBounds(int& coord1_int, int& coord2_int, char& orientation);

            bool OrientationValidation(std::string &orientation);


        private:
            std::string name;
        };
}

#endif //BATTLESHIP_HUMAN_H
