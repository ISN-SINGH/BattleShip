# Course Project - *BattleShip*

Battleship is a text-based battleship game with multiple game modes. Play against another human or versus AI

## Setup
Upon startup the game first reads from a file the length and width of the game board and the number of ships per player. Following lines are made up of the letter a ship will be represented by and its length. "B 3" signifies a ship displayed with B's on the game board that is 3 units long.

Each human player in the game enters their name and is asked the orientation and coordinates of the ships they woud like to place. They first choose between horizontal or verticla placement, then specify a coordinate for the top left of the ship to be placed in format "row col". Input validation disallows ships to overlap or extend outside of the game board. Human players will keep being asked for this information until it is valid. AIs place their ships randomly.

### Placement Board
The placement board displays the location of all ships of a player. If a coordinate that a ship is on is attacked by the opponent, an X marker will be placed to indicate which part of the ship is destroyed. If a coordinate with no ship is attacked by the opponent, an O marker will be plaecd to indicate the miss. Each time a ship is placed on the board, the player's placement board is printed so they can see where exactly on the board the ship was placed.

### Firing Board
The firing board displays all coordinates a player has attacked. Each time a player attacks a new coordinate, their firing board is printed. X's are marked at coordinates that successfully hit the opponent's ship and O's indicate misses.

## Playthrough
### Gamemodes
The game begins by allowing the user to choose between 3 gamemodes.
1. Human vs Human - Two human players take turns firing at each other's ships.
2. Human vs AI - A human player can go against any AI type they choose.
3. AI vs AI - Two AIs face each other at blazing fast speeds within a few seconds.

## AI Types
Each AI in the game can be one of the following types.
1. RandomAI

2. CheatingAI

3. HuntDestroyAI

Three AI types:
Random - Attacks random coordinates in the board
Cheating - Knows the location of all enemy ships and never misses
Hunt-Destroy - Attacks at random until a ship is hit in which case the AI chooses random coordinates around the coordinate of the ship that was hit
