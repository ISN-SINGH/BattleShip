//
// Created by Sage Zimmerman on 5/21/21.
//

#ifndef BATTLESHIP_GAME_TYPE_H
#define BATTLESHIP_GAME_TYPE_H
#include <string>
namespace BattleShip {
    void GetGameType(int &type_of_game);

    void AskGameType();

    int GetGameTypeChoice(bool &game_type_valid);

    bool StrToIntFormatValidation(std::string player_choice);

    bool IsStrNumber(std::string valid_read);

    bool TypeBoundsValidation(int type_of_game);

    void GetPlayerOneType(const int& type_of_game, int &player_type);

    void GetPlayerTwoType(const int& type_of_game, int &player_type);

    int GetAIType();

    void AskAIType();

}

#endif //BATTLESHIP_GAME_TYPE_H
