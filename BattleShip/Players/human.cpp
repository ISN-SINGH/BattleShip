#include "human.h"
#include "../GameFiles/game.h"
#include <iostream>
#include <limits>

namespace BattleShip {

    human::human(board& boardObj) : player(boardObj) {}

    // during_game differentiates printing the board during setup vs during game
    // defaults to 0 meaning that the setup version should be printed
    // if not 0, print the board as if the game was being played with titles above the boards
    void human::PrintFiringBoard(int during_game) const {
        if (during_game != 0) {  // only print owner during game
            std::cout << name << "'s Firing Board" << std::endl;
        }

        for (int i = 0; i < boardObj.GetNumCols(); ++i) {
            if (i == 0) {
                std::cout << "  " << i;
            } else {
                std::cout << " " << i;
            }
        }
        std::cout << " " << std::endl;

        for (int i = 0; i < boardObj.GetNumRows(); ++i) {
            std::cout << i << " ";
            for (int j = 0; j < boardObj.GetNumCols(); ++j) {
                std::cout << boardObj.GetFiringBoard().at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }

        if (during_game != 0) {
            std::cout << std::endl << std::endl;  // always 2 newlines after firing board
        }
    }


    // Prints board with ships
    void human::PrintFullBoard(int during_game) const {
        if (during_game != 0) {
            std::cout << name << "'s Placement Board" << std::endl;
        }

        for (int i = 0; i < boardObj.GetNumCols(); ++i) {
            if (i == 0) {
                std::cout << "  " << i;
            } else {
                std::cout << " " << i;
            }
        }
        std::cout << " " << std::endl;

        for (int i = 0; i < boardObj.GetNumRows(); ++i) {
            std::cout << i << " ";
            for (int j = 0; j < boardObj.GetNumCols(); ++j) {
                std::cout << boardObj.GetContents().at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }
    }


    // Sets up player board, asking where/how to place ships
    void human::SetupPlayer(int player_num) {
        int num_ships = boardObj.GetShipDetails().size();
        EnterHuman(player_num);
        for (int i = 0; i < num_ships; ++i) {
            char orientation;
            coord player_coord;

            GetOrientAndCoords(orientation, player_coord);
            boardObj.MakeShip(player_coord, orientation);
        }
        PrintFullBoard();
    }


    // Player enters their name which is set to the owner of the board and the player object's name
    void human::EnterHuman(int player_num) {
        std::string player_name;
        std::cout << "Player " << player_num << " please enter your name: ";
        std::cin >> player_name;
        SetName(player_name);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }


    // Sets name to player input
    void human::SetName(const std::string& name) {
        this->name = name;
    }


    // Gets attack coord input from user
    coord human::AskAttackCoord() {
        PrintFiringBoard(1);
        PrintFullBoard(1);
        while (true) {
            std::cout << name << ", where would you like to fire?" << std::endl <<
                      "Enter your attack coordinate in the form row col: ";

            std::string player_coord_string;
            getline(std::cin, player_coord_string);
            std::stringstream line2parse(player_coord_string);
            std::string row_coord, col_coord, should_not_read;

            int row_int, col_int;
            line2parse >> row_coord;
            if (line2parse) {  // checks if x coord can be read
                line2parse >> col_coord;
                if (line2parse) {  // checks if y coord can be read
                    line2parse >> should_not_read;
                    if (!line2parse) {  // Should not read because of invalid input after nums
                        if (PairIsInts(row_coord, col_coord)) {  // Convert to ints after verifying they can be converted
                            row_int = std::stoi(row_coord);
                            col_int = std::stoi(col_coord);
                            if (boardObj.areCoordsInBounds(row_int, col_int)) {  // out of bounds ints
                                coord attack_coord = std::make_pair(row_int, col_int);
                                if (not boardObj.CoordWasAttacked(
                                        attack_coord)) {  // previously attempted attack at this coord
                                    return attack_coord;
                                } else {
                                    PrintFiringBoard(1);
                                    PrintFullBoard(1);
                                }
                            } else {
                                PrintFiringBoard(1);
                                PrintFullBoard(1);
                            }
                        }
                    }
                }
            }
        }
    }


    // This function always looks at the first ship inside of ship_details
    // Once all the information for a ship is gathered, create ship and remove it from ship_details
    void human::GetOrientAndCoords(char &orientation, coord &player_coords) {
        bool is_orientation_valid;
        bool are_coords_valid;
        bool is_format_valid;

        PrintFullBoard(0);
        do {
            do {
                orientation = GetVertOrHor(is_orientation_valid);
            } while (!is_orientation_valid);
            do {
                player_coords = AskPlayerCoords(are_coords_valid, orientation, is_format_valid);
            } while (!is_format_valid);
        } while (!are_coords_valid);
    }


    // Uses input validation on input the user enters for deciding where ships should be placed
    coord human::AskPlayerCoords(bool &are_coords_valid, char &orientation, bool &is_format_valid) {
        // Ask for name in another function
        std::cout << name << ", enter the row and column you want to place "
                  << boardObj.GetShipDetails().at(0).first << ", which is "
                  << boardObj.GetShipDetails().at(0).second <<
                  " long, at with a space in between row and col: ";

        return GetPlayerCoords(are_coords_valid, orientation, is_format_valid);
    }


    // Gets player coords for ship placement on board
    coord human::GetPlayerCoords(bool &are_coords_valid, char &orientation, bool &is_format_valid)  {
        std::string player_coord_string;
        int coord1_int = 0;
        int coord2_int = 0;
        getline(std::cin, player_coord_string);
        std::stringstream line2parse(player_coord_string);
        std::string row_coord, col_coord, should_not_read;
        line2parse >> row_coord;
        if (line2parse) {
            line2parse >> col_coord;
            if (line2parse) {
                line2parse >> should_not_read;
                if (!line2parse) {  // should not pass because of invalid input after nums
                    are_coords_valid = CoordValidation(row_coord, col_coord, coord1_int, coord2_int,
                                                       orientation, is_format_valid); //make coord validator
                    if (are_coords_valid) {
                        coord1_int = stoi(row_coord);  //converts strings to coords
                        coord2_int = stoi(col_coord);  //converts strings to coords
                        player_coord_string.clear();
                    }
                }
            } else {
                are_coords_valid = false;
                is_format_valid = false;
            }
        } else {
            are_coords_valid = false;
        }
        return std::make_pair(coord1_int, coord2_int);
    }


    // Validation check for coordinates, makes sure ships aren't placed out of bounds or on other ships
    bool human::CoordValidation(const std::string& row_coord, const std::string& col_coord,
                         int& coord1_int, int& coord2_int, char& orientation, bool &is_format_valid) {
        for (char const &c : row_coord) {  // If x is not an int, coords are invalid
            if (std::isdigit(c) == 0) return false;
        }
        for (char const &c : col_coord) {  // If y is not an int, coords are invalid
            if (std::isdigit(c) == 0) return false;
        }
        is_format_valid = true;  // If x and y are both ints and no more lines can be read, format is valid

        coord1_int = stoi(row_coord);  // transforms coords from strings to usable ints
        coord2_int = stoi(col_coord);

        if (!CheckOutOfBounds(coord1_int, coord2_int, orientation)) {
            return false;
        }
        if (!CheckShipOverlap(coord1_int, coord2_int, orientation)) {
            return false;
        }
        return true;
    }


    // Checks if ship at selected coordinate are out of bounds
    bool human::CheckOutOfBounds(int& coord1_int, int& coord2_int, char& orientation) {
        // checks if x is out of bounds on the board
        if (coord1_int < 0 || coord1_int >= boardObj.GetNumRows()) {
            return false;
        }
        // checks if y is out of bounds on the board
        if (coord2_int < 0 || coord2_int >= boardObj.GetNumCols()) {
            return false;
        }

        if (orientation == 'v') {  // checks if ship will go off board vertically at end coord
            if ((boardObj.GetShipDetails().front().second - 1) + coord1_int >= boardObj.GetNumRows()) {
                return false;
            }
        }

        if (orientation == 'h') {  // checks if ship will go off board horizontally at end coord
            if ((boardObj.GetShipDetails().front().second - 1) + coord2_int >= boardObj.GetNumCols()) {
                return false;
            }
        }
        return true;
    }


    // Uses input validation on input the user enters for deciding orientation of their ships
    char human::GetVertOrHor(bool &is_orientation_valid) {
        std::string orientation_line;
        std::string orientation;
        std::cout << name << ", do you want to place " <<
                  boardObj.GetShipDetails().front().first << " horizontally or vertically?" << std::endl;
        std::cout << "Enter h for horizontal or v for vertical" << std::endl;
        std::cout << "Your choice: ";

        getline(std::cin, orientation_line);

        std::stringstream line2parse(orientation_line);
        std::string should_not_read;
        line2parse >> orientation;
        if (line2parse) {
            line2parse >> should_not_read;
            if (!line2parse) {  // Read should fail if the input is valid
                is_orientation_valid = OrientationValidation(orientation);
                if (is_orientation_valid) {
                    orientation = std::tolower(orientation.at(0));
                    orientation_line.clear();
                    return orientation.at(0);
                }
            } else {
                is_orientation_valid = false;
            }
        }

        orientation_line.clear();
        return '?'; // invalid character
    }

    // Validation check for orientation input
    bool human::OrientationValidation(std::string& orientation) {
        if (orientation == "v" || orientation == "V" ||
            orientation == "h" || orientation == "H") {

            return true;
        } else {
            return false;
        }
    }

    const std::string human::GetName() const {
        return name;
    }

}