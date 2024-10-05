
#ifndef MONOPOLY_GAMEFLOW_HPP
#define MONOPOLY_GAMEFLOW_HPP
#include <unordered_map>
#include <unordered_set>
#include "Board.hpp"
#include "Dice.hpp"
#include "Button.hpp"
#include "ChanceCard.hpp"
#include "Infrastructure.hpp"
#include "SpecialSquare.hpp"

/**
 * @class GameFlow
 * @brief Manages the overall flow of the Monopoly game, including player turns, game state,
 *        and interactions with the game board.
 */
class GameFlow {
    Board * board;              // Board instance (singleton)
    Dice dice;              // Dice for rolling
    sf::RenderWindow& window;   // Reference to the SFML render window
    sf::Font font;                      // Font used for displaying text.
    std::vector<Player> players;        // Vector to store all players
    int currentPlayerIndex;                 // Tracks the current player's turn
    std::unordered_map<int, int> playerLocations;       // track player Location across the board.
    std::unordered_set<PlayerColor> selectedColors;     //track players colors to make sure no color repeating.
    void handleSquare(Player& player);                  // Handles landing.
    void movePlayer(Player& player,int steps);             // Handles the player's dice roll and movement
    /**
  * @brief Checks if a player has gone bankrupt.
  * @return true if a player is bankrupt, false otherwise.
  */
    bool checkBankruptcy() ;                  // Checks if a player has gone bankrupt
    /**
     * @brief Displays a message on the GUI.
     * Notice do not update the board, dislplay the message on blank board.
     * @param message The message to display.
     */
    void displayMessage(const std::string &message) ;

    /**
     * @brief Updates the displayed message on the GUI.
     * @param message The new message to display.
     */
    void updateMessage(const std::string &message);
    /**
     * @brief Initializes buttons for the game interface.
     */
    void ButtonInit();
    /**
    * @brief Retrieves the player color based on user input.
    * @param colorInput The color input string from the user.
    * @return The corresponding PlayerColor enum value.
    */
    PlayerColor getPlayerColorFromInput(const std::string& colorInput);

    /**
     * Once Player has Bankrupt, Remove player from the game.
     * @param playerID
     */
    void removePlayer(int playerID);
    /**
     * Display all Estates once the button is clicked.
     */
    void displayEstates();
    /**
     * @brief Prompts the user for the number of players to start the game.
     * @return The number of players entered by the user.
     */
    int promptForPlayerCount();
    /**
    * @brief Prompts the user for details about each player.
    * @param numPlayers The number of players to gather details for.
    */
    void promptForPlayerDetails(int numPlayers);

    /**
     * @brief Gets user input from the console.
     * @return The input string from the user.
     */
    std::string getUserInput();

    PlayerColor getFirstAvailableColor();

public:
    explicit GameFlow(sf::RenderWindow& window);         // Constructor: Initializes the game with a given number of players
    void startGame();              // Starts the game and handles the main game loop
    /**
        * @brief Handles a single player's turn, including dice rolling and movement.
        * @param player Reference to the player object whose turn is being played.
     */
    void playTurn(Player& player);
    /**
     * @brief Retrieves the index of the current player's turn.
     * @return The index of the current player.
     */
    int getTurn() const;
    /**
     * @brief Updates the GUI elements based on the current game state.
     */
    void updateGUI() ;
    std::vector<Player> & getPlayers();
    // Checks if the game has ended
    /**
    * @brief Checks if the game has ended based on game rules.
    * @return true if the game is over, false otherwise.
    */
    bool isGameOver() ;
    ~GameFlow();
    /**
     * Game Buttons.
     */
    Button throwDiceButton;
    Button yesButton;
    Button noButton;
    Button viewEstatesButton;

};


#endif //MONOPOLY_GAMEFLOW_HPP
