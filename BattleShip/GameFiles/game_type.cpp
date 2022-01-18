//
// Created by Sage Zimmerman on 5/21/21.
//

#include "game_type.h"
#include <iostream>
#include <sstream>
namespace BattleShip {
    // Retrieves the type of game wanted by player
    void GetGameType(int &type_of_game) {
        bool game_type_valid = false;
        do {
            AskGameType();
            type_of_game = GetGameTypeChoice(game_type_valid);  //left here
            if (game_type_valid) {
                game_type_valid = TypeBoundsValidation(type_of_game);
            }
        } while (!game_type_valid);

    }


    // Outputs prompt for user for retrieving game type
    void AskGameType() {
        std::cout << "What type of game do you want to play?" << std::endl;
        std::cout << "1. Human vs Human" << std::endl << "2. Human vs AI"
                  << std::endl << "3. AI vs AI" << std::endl;
        std::cout << "Your choice: ";
    }


    // Gets input for game tye choice with validation
    int GetGameTypeChoice(bool &game_type_valid) {
        std::string player_choice;
        getline(std::cin, player_choice);
        game_type_valid = StrToIntFormatValidation(player_choice);
        if (game_type_valid) {
            int player_choice_int = stoi(player_choice);
            return player_choice_int;
        } else {
            return -1;  // If input is invalid, returns invalid type
        }
    }


    // Checks if player choice is in valid format (no extra characters after space)
    bool StrToIntFormatValidation(std::string player_choice) {
        std::string valid_read, invalid_read;
        std::stringstream line2parse(player_choice);
        if (line2parse >> valid_read) {
            if (!(line2parse >> invalid_read)) {
                return IsStrNumber(valid_read);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }


    // Checks the validly formatted input is an int
    bool IsStrNumber(std::string valid_read) {
        for (char const &c : valid_read) {
            if (std::isdigit(c) == 0) return false;
        }
        return true;
    }


    // Checks the game type is between 0 and 3 (0 == human player)
    bool TypeBoundsValidation(int type_of_game) {
        if (type_of_game > 0 && type_of_game <= 3) {
            return true;
        }
        return false;
    }


    // Gets Player 1's pointer type
    void GetPlayerOneType(const int& type_of_game, int &player_type) {
        if (type_of_game == 1) {
            player_type = 0;  // 0 player_type means the player is human and not an AI
        } else if (type_of_game == 2) {
            player_type = 0;
        } else {
            player_type = GetAIType();
        }
    }


    // Gets Player 2's pointer type
    void GetPlayerTwoType(const int& type_of_game, int &player_type) {
        if (type_of_game == 1) {
            player_type = 0;
        } else if (type_of_game == 2) {
            player_type = GetAIType();
        } else {
            player_type = GetAIType();
        }
    }

    int GetAIType() {
        std::string ai_type;
        bool is_ai_valid;
        int ai_type_int;
        do {
            AskAIType();
            getline(std::cin, ai_type);
            is_ai_valid = StrToIntFormatValidation(ai_type);
            if (is_ai_valid) {
                ai_type_int = stoi(ai_type);
                is_ai_valid = TypeBoundsValidation(ai_type_int);
            }
        } while (!is_ai_valid);
        return ai_type_int;
    }

    void AskAIType() {
        std::cout << "What AI do you want?" << std::endl <<
                  "1. Cheating AI" << std::endl <<
                  "2. Random AI" << std::endl <<
                  "3. Hunt Destroy AI" << std::endl;
        std::cout << "Your choice: ";
    }
}