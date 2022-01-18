#include "setup.h"
#include "../Players/human.h"
#include "../Players/AIPlayers/search_destroy.h"
#include "../Players/AIPlayers/cheater.h"
#include <iostream>
#include <random>
#include <chrono>

namespace BattleShip {
    // Sets up the game (player objects, board with all ships) to be ready to play
    // Doesn't matter if player is AI or human
    void SetUpGame(player_ptr &player) {
        static bool firstPlayerSetup = false;
        player->SetBoard().SortShipDetails();
        if (not firstPlayerSetup) {
            player->SetupPlayer(1);
            firstPlayerSetup = true;
        } else {
            player->SetupPlayer(2);
        }
    }


    // Gets all information from the starting file and puts details of ships into ship_details
    void GetFileArgs(int& board_rows, int& board_cols, int& num_ships,
                     std::vector<std::pair<char, int>>& ship_details, std::string& file_name) {
        std::string ship_and_length;
        char ship_type;
        int ship_type_length;
        std::ifstream fileReader;
        fileReader.open(file_name);


        fileReader >> board_rows;
        fileReader >> board_cols;
        fileReader >> num_ships;

        for (int i = 0; i < num_ships; ++i) {
            fileReader >> ship_type;
            fileReader >> ship_type_length;
            ship_details.push_back(std::make_pair(ship_type, ship_type_length));
        }
        fileReader.close();
    }


    // Gets the name of the file to be parsed from command line
    void ParseCLArgs(char **&argv, std::string &file_name, int argc, int &rand_seed) {
        if (argc == 2) {
            file_name = argv[1];
            rand_seed = std::chrono::system_clock::now().time_since_epoch().count();
        } else if (argc == 3) {
            file_name = argv[1];
            std::string seed_string = argv[2];
            rand_seed = stoi(seed_string);
        } else {
            exit(0);
        }
    }


    // Makes player objects (Human or AI)
    void MakePlayer(int& type_of_game, int& player_type,
                    board& player_board, player_ptr& playerPtr, board& other_board) {
        static bool other_player_created = false;
        // makes player objects unique pointers
        if (type_of_game == 1) {
            playerPtr = std::make_unique<BattleShip::human>(player_board);
        } else if (type_of_game == 2) {
            if (other_player_created == true) {  // making player ai 1, player 2
                MakeAIPlayer(player_type, player_board, playerPtr, other_board,
                             other_player_created = false); // Set = false so that AI opponent has designation 1
            } else {
                playerPtr = std::make_unique<BattleShip::human>(player_board);
                other_player_created = true;
            }
        } else {
            MakeAIPlayer(player_type, player_board, playerPtr, other_board, other_player_created);
            if (not other_player_created) {  // making player ai 2, player 2
                other_player_created = true;
            }
        }
    }


    // Specified function for making different types of AI players
    void MakeAIPlayer(int player_type, board& player_board, player_ptr& playerPtr,
                      board& other_board, bool other_player_created) {
        int designation;
        if (other_player_created) {
            designation = 2;
        } else {
            designation = 1;
        }

        if (player_type == 1) {
            playerPtr = std::make_unique<BattleShip::cheaterAI>(player_board, designation, other_board.GetContents());
        } else if (player_type == 2) {
            playerPtr = std::make_unique<BattleShip::randomAI>(player_board, designation);
        } else {
            playerPtr = std::make_unique<BattleShip::sadAI>(player_board, designation);
        }
    }

}