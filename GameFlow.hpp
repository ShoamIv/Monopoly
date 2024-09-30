

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
    void movePlayer(Player& player,int steps);             // Handles the player's dice roll and movement
    bool checkBankruptcy() ;                  // Checks if a player has gone bankrupt
    void displayMessage(const std::string &message) ;
    void updateMessage(const std::string &message);
public:
    GameFlow(int numPlayers,sf::RenderWindow& window);         // Constructor: Initializes the game with a given number of players
    void startGame();              // Starts the game and handles the main game loop
    void playTurn(Player& player);         // Handles a single player's turn
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

    void removePlayer(int playerID);
};


#endif //MONOPOLY_GAMEFLOW_HPP
