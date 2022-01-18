#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H


#include "../GameFiles/board.h"

#include <memory>
#include <vector>

namespace BattleShip {
    class player {
    public:
        using player_ptr = std::unique_ptr<BattleShip::player>;

        using coord = std::pair<int, int>;

        explicit player(board &boardObj);

        virtual ~player() = default;

        const board &GetBoard() const;

        board &SetBoard();

        virtual void PrintFullBoard(int during_game = 0) const = 0;

        virtual void PrintFiringBoard(int during_game = 0) const = 0;

        virtual void SetupPlayer(int player_num = 0) = 0;

        virtual const std::string GetName() const = 0;

        virtual coord AskAttackCoord() = 0;

        virtual bool AttackShip(player_ptr &other_player, coord &attack_coord, int &index_of_ship);


    protected:
        board &boardObj;

        bool CheckShipOverlap(const int &coord1_int, const int &coord2_int, const char &orientation) const;
    };
}

#endif