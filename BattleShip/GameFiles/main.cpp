#include "board.h"
#include "../Players/player.h"
#include "../Players/ai_player.h"
#include "setup.h"
#include "game.h"
#include "game_type.h"

#include <vector>
#include <memory>
#include <random>


std::mt19937 BattleShip::baseAI::rng;

int main(int argc, char* argv[]) {
    using player_ptr = std::unique_ptr<BattleShip::player>;
    std::string file_name;
    int board_rows, board_cols, num_ships;
    std::vector<std::pair<char, int>> ship_details;  //  holds names and lengths of all ships
    std::string player_name1, player_name2;
    int rand_seed = 0;
    int type_of_game = 0;
    int player1_type, player2_type;

    // Gets arguments from Command line and file
    BattleShip::ParseCLArgs(argv, file_name, argc, rand_seed);
    BattleShip::GetFileArgs(board_rows, board_cols, num_ships, ship_details, file_name);

    // Initializes random generator
    BattleShip::baseAI::rng.seed(rand_seed);

    // Creates board objects for players
    BattleShip::board board_p1(board_rows, board_cols, ship_details);
    BattleShip::board board_p2(board_rows, board_cols, ship_details);
    BattleShip::GetGameType(type_of_game);  // Gets type of game and players

    // Sets up Player 1 for game
    player_ptr p1ptr;
    BattleShip::GetPlayerOneType(type_of_game, player1_type);
    MakePlayer(type_of_game, player1_type, board_p1, p1ptr, board_p2);
    SetUpGame(p1ptr);

    // Sets up Player 2 for game
    player_ptr p2ptr;
    BattleShip::GetPlayerTwoType(type_of_game, player2_type);
    MakePlayer(type_of_game, player2_type, board_p2, p2ptr, board_p1);
    SetUpGame(p2ptr);

    // Players play BattleShip game
    PlayGame(p1ptr, p2ptr);
    return 0;
}
