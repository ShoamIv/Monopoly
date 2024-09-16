

#ifndef MONOPOLY_GAMEFLOW_H
#define MONOPOLY_GAMEFLOW_H

#include <unordered_map>
#include "Player.h++"
#include "Board.h++"
#include "Dice.h++"
#include "ChanceCard.h++"
#include "Infrastructure.h++"
#include "SpecialSquare.h++"

class GameFlow {

    // Board instance (singleton)
    Board * board;

    // Dice for rolling
    Dice dice;

    // Vector to store all players
    std::vector<Player> players;

    // Tracks the current player's turn
    int currentPlayerIndex;

    std::unordered_map<int, int> playerLocations; // Player ID to current position

    // Handles landing on a tile
    void handleSquare(Player& player);

    // Handles the player's dice roll and movement
    void movePlayer(Player& player,int repeat);

    // Checks if a player has gone bankrupt
    static bool checkBankruptcy(Player& player) ;

public:

    // Constructor: Initializes the game with a given number of players
    GameFlow(int numPlayers);

    // Starts the game and handles the main game loop
    void startGame();

    // Handles a single player's turn
    void playTurn(Player& player);

    // Checks if the game has ended
    bool isGameOver() const;

    // Ends the game
    void endGame();

    // Resets the game for a new session
    void resetGame();

};


#endif //MONOPOLY_GAMEFLOW_H
