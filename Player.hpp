#ifndef MONOPOLY_PLAYER_HPP
#define MONOPOLY_PLAYER_HPP

#include <string>
#include <vector>
#include "Estate.hpp"
#include "Dice.hpp"

/**
 * @class Player
 * @brief Represents a player in the Monopoly game.
 *
 * The Player class manages all player-specific details such as their name, color,
 * current position on the board, cash, jail status, owned estates, and dice rolls.
 * It also handles player interactions like moving, paying rent, and collecting
 * money from bankrupt players.
 *
 * Additionally, the class handles GUI-related functionality to display player info
 * in the game window.
 */

class Board; // Forward declaration of Board class

// Constants for board and player visuals
const float BOARD_WIDTH = 800;       ///< Width of the game board.
const float BOARD_HEIGHT = 800;      ///< Height of the game board.
const float SQUARE_SIZE = 73;        ///< Size of each square on the board.
const float R = 10.0f;               ///< Radius for the player's token.

/**
 * @enum PlayerColor
 * @brief Enum representing the available colors for player tokens.
 */
enum class PlayerColor {
    Red,        ///< Red player token.
    Blue,       ///< Blue player token.
    Green,      ///< Green player token.
    Yellow,     ///< Yellow player token.
    Orange,     ///< Orange player token.
    Purple,     ///< Purple player token.
    Brown,      ///< Brown player token.
    Magenta     ///< Magenta player token.
};

class Player {
private:
    std::string name;                  ///< Player's name.
    PlayerColor color;                 ///< Player's token color.
    int id;                            ///< Unique player ID.
    int curr_position = 0;             ///< Current position of the player on the board.
    int cash = 0;                      ///< Player's current cash balance.
    int jail_time = 0;                 ///< Time player spends in jail.
    int dice = 0;                      ///< Result of the player's most recent dice roll.
    int NumOfRailRoad = 0;             ///< Number of Railroads owned by the player.
    int getOutFromJail = 0;            ///< Number of Get Out of Jail Free cards owned.
    int DoubleCount = 0;               ///< Counts the number of consecutive double dice rolls.
    bool ChanceDraw = false;           ///< Flag to check if player drew a Chance card.
    bool Bankruptcy = false;           ///< Flag to check if player is bankrupt.
    std::vector<Estate*> Estates;      ///< List of estates owned by the player.

    // GUI-related fields
    sf::Text text;                     ///< Text to display player's name and details.
    sf::Font font;                     ///< Font used for displaying player's text.
    sf::CircleShape PlayerInfoCircle;  ///< Circle representing the player in the GUI.

    /**
     * @brief Initializes the player's GUI elements, such as name and token.
     * @param window The game window where the player's info will be displayed.
     */
    void InitializePlayer(sf::RenderWindow &window);

public:
    /**
     * @brief Constructor to initialize a Player object with name, color, and ID.
     * @param name Player's name.
     * @param color Player's token color.
     * @param id Player's unique ID.
     * @param window The game window for rendering the player.
     */
    explicit Player(std::string &name, PlayerColor color, int id, sf::RenderWindow &window);

    // Setters:
    /**
     * @brief Updates the player's cash balance.
     * @param amount The amount to add or subtract from the player's cash.
     */
    void setCash(int amount);

    /**
     * @brief Sets the player's jail time.
     * @param time The time the player will stay in jail.
     */
    void setJail(int time);

    /**
     * @brief Increases the number of Railroads owned by the player.
     */
    void IncreaseNumRailRoad();

    /**
     * @brief Sets the flag for drawing a Chance card.
     * @param flag True if a Chance card was drawn, false otherwise.
     */
    void setChanceDraw(bool flag);

    /**
     * @brief Increases the number of Get Out of Jail Free cards.
     */
    void IncreaseJailCard();

    /**
     * @brief Marks the player as bankrupt.
     */
    void setBankruptcy();

    /**
     * @brief Sets the number of Get Out of Jail Free cards the player owns.
     * @param num Number of cards.
     */
    void setJailCard(int num);

    /**
     * @brief Adds an estate to the player's list of owned estates.
     * @param estate The estate to add.
     */
    void AddEstate(Estate &estate);

    /**
     * @brief Updates the player's most recent dice roll.
     * @param diceroll The result of the dice roll.
     */
    void setRecentDice(int diceroll);

    // Getters:
    /**
     * @brief Returns the player's name.
     * @return Player's name.
     */
    [[nodiscard]] std::string getName() const;

    /**
     * @brief Returns the player's current cash balance.
     * @return Player's cash.
     */
    [[nodiscard]] int getCash() const;

    /**
     * @brief Returns the player's jail time.
     * @return Time the player is in jail.
     */
    [[nodiscard]] int getJail() const;

    /**
     * @brief Returns the player's most recent dice roll.
     * @return The result of the most recent dice roll.
     */
    [[nodiscard]] int getRecentDice() const;

    /**
     * @brief Returns the number of Railroads owned by the player.
     * @return Number of Railroads.
     */
    [[nodiscard]] int getRailRoad() const;

    /**
     * @brief Returns the player's current position on the board.
     * @return Player's board position.
     */
    int getPosition() const;

    /**
     * @brief Returns the player's unique ID.
     * @return Player ID.
     */
    int getID() const;

    /**
     * @brief Returns the number of Get Out of Jail Free cards the player owns.
     * @return Number of Get Out of Jail Free cards.
     */
    int getJailCard() const;

    /**
     * @brief Returns whether the player has drawn a Chance card.
     * @return True if Chance card drawn, false otherwise.
     */
    bool getChanceDraw() const;

    /**
     * @brief Returns whether the player is bankrupt.
     * @return True if bankrupt, false otherwise.
     */
    bool getBankruptcy() const;

    /**
     * @brief Returns the player's position index based on the given location name.
     * @param location The name of the location on the board.
     * @return Position index of the location.
     */
    int getPositionIndex(const std::string& location);

    /**
     * @brief Returns the list of estates owned by the player.
     * @return Vector of pointers to Estate objects.
     */
    std::vector<Estate*> getEstates();

    // In-game methods:
    /**
     * @brief Collects rent from another player.
     * @param p The player paying the rent.
     * @param rent The rent amount to be collected.
     */
    void CollectRent(Player &p, int rent);

    /**
     * @brief Moves the player by a specified number of steps on the board.
     * @param steps Number of steps to move the player.
     * @param window The game window where the movement is displayed.
     */
    void Move(int steps, sf::RenderWindow &window);

    /**
     * @brief Moves the player directly to a specified location on the board.
     * @param location The name of the destination location.
     * @param window The game window where the movement is displayed.
     */
    void MoveTo(const std::string& location, sf::RenderWindow &window);

    /**
     * @brief Resets the count of consecutive double dice rolls for the player.
     */
    void resetRepeatDouble();

    /**
     * @brief Collects assets from a player who has gone bankrupt.
     * @param BrokePlayer The player who is bankrupt.
     */
    void CollectBankruptcy(Player & BrokePlayer);

    // GUI Update:
    /**
     * @brief Draws the player's information (name, token, etc.) on the game window.
     * @param window The game window where the player's info will be drawn.
     */
    void DrawInfo(sf::RenderWindow &window);

    /**
     * @brief Returns the SFML color corresponding to the player's token color.
     * @return Reference to the SFML Color object.
     */
    const sf::Color &getColor();
};

#endif // MONOPOLY_PLAYER_HPP
