cmake_minimum_required(VERSION 3.15)
project(Battleship)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip GameFiles/main.cpp GameFiles/board.cpp GameFiles/board.h GameFiles/ship.cpp GameFiles/ship.h Players/player.cpp Players/player.h GameFiles/setup.cpp GameFiles/setup.h GameFiles/game.cpp GameFiles/game.h Players/human.cpp Players/human.h Players/AIPlayers/random.cpp Players/AIPlayers/random.h Players/AIPlayers/cheater.cpp Players/AIPlayers/cheater.h Players/AIPlayers/search_destroy.cpp Players/AIPlayers/search_destroy.h Players/ai_player.cpp Players/ai_player.h GameFiles/game_type.cpp GameFiles/game_type.h)