#ifndef MAIN_CPP_SETUP_H
#define MAIN_CPP_SETUP_H

#include "../Players/player.h"


namespace BattleShip {
    using player_ptr = std::unique_ptr<BattleShip::player>;

    void EnterPlayer(player_ptr& player, int player_num);

    void SetUpGame(player_ptr &ptr1);

    void PlayerSetUp(const player_ptr &player, char &orientation, coord &player_coords);

    char GetVertOrHor(bool &is_orientation_valid, const player_ptr &curr_player);

    bool OrientationValidation(std::string &orientation);

    coord AskPlayerCoords(bool &are_coords_valid, const player_ptr &player, char &orientation, bool &is_format_valid);

    void GetFileArgs(int &board_rows, int &board_cols, int &num_ships,
                     std::vector<std::pair<char, int>> &ship_details, std::string &file_name);

    bool CoordValidation(const player_ptr &player, const std::string &row_coord, const std::string &col_coord,
                         int &coord1_int, int &coord2_int, char &orientation, bool &is_format_valid);

    void ParseCLArgs(char **&argv, std::string &file_name, int argc, int &rand_seed);

    void GetFileArgs(int& board_rows, int& board_cols, int& num_ships,
                     std::vector<std::pair<char, int>>& ship_details, std::string& file_name);

    coord GetPlayerCoords(bool &are_coords_valid, const player_ptr &player, char &orientation, bool &is_format_valid);

    bool CheckOutOfBounds(const player_ptr& player, int& coord1_int, int& coord2_int, char& orientation);


    bool CheckShipOverlap(const player_ptr& player, const int& coord1_int, const int& coord2_int);

    void MakePlayer(int& type_of_game, int& player_type, board& player_board,
                    player_ptr& playerPtrInitial, board &playerPtrOther);

    void MakeAIPlayer(int player_type, board& player_board,
                      player_ptr& playerPtr, board &playerPtr2, bool other_player_created);
}

#endif
