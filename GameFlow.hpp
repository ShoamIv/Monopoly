

#ifndef MONOPOLY_GAMEFLOW_HPP
#define MONOPOLY_GAMEFLOW_HPP

#include <unordered_map>
#include "Board.hpp"
#include "Dice.hpp"
#include "Button.hpp"
#include "ChanceCard.hpp"
#include "Infrastructure.hpp"
#include "SpecialSquare.hpp"

class GameFlow {
    Board * board;              // Board instance (singleton)
    Dice dice;              // Dice for rolling
    sf::RenderWindow& window;
    sf::Font font;
    std::vector<Player> players;        // Vector to store all players
    int currentPlayerIndex;                 // Tracks the current player's turn
    std::unordered_map<int, int> playerLocations;
    void handleSquare(Player& player);                  // Handles landing.
    void movePlayer(Player& player);             // Handles the player's dice roll and movement
    static bool checkBankruptcy(Player& player) ;                  // Checks if a player has gone bankrupt
    void handleEstate(Estate &estate, Player &player);
    void displayMessage(const std::string &message) ;

public:

    // Constructor: Initializes the game with a given number of players
    GameFlow(int numPlayers,sf::RenderWindow& window);

    // Starts the game and handles the main game loop
    void startGame();

    // Handles a single player's turn
    void playTurn(Player& player);

    int getTurn() const;

    void updateGUI() ;

    std::vector<Player> & getPlayers();

    sf::RenderWindow& getWindow();


    // Checks if the game has ended
     bool isGameOver() ;
    // Ends the game
   // void endGame();

    // Resets the game for a new session
  // void resetGame();


    Button throwDiceButton;
    Button yesButton;
    Button noButton;
    sf::Text gameMessageText;
};


#endif //MONOPOLY_GAMEFLOW_HPP
