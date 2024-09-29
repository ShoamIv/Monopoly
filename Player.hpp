
#ifndef MONOPOLY_PLAYER_HPP
#define MONOPOLY_PLAYER_HPP
#include <string>
#include <vector>
#include "Estate.hpp"
#include "Dice.hpp"
class Board;
const float BOARD_WIDTH = 800;
const float BOARD_HEIGHT = 800;
const float SQUARE_SIZE = 73;
const float R = 10.0f;
enum class PlayerColor {
    Red,
    Blue,
    Green,
    Yellow,
    Orange,
    Purple,
    Brown,
    Magenta
};

class Player {
    std::string name;
    PlayerColor  color;
    int id;
    int curr_position=0;                //current position in the game.
    int cash=0;                         // holds for the money the player has.
    int jail_time=0;
    int dice{};                        //recent diceRoll.
    int NumOfRailRoad=0;
    int getOutFromJail=0;
    int repeatDouble=0;
    bool DrawChance=false;                    //indicate if to draw a chance

    std::vector<Estate*> Estates;       //Player Estates

    /*
     * list of cities the player own
     * a Player that Owns entire city-> able to require houses.
     */
    std::vector<std::string> CityOwner;
    //GUI
    sf::Text text;
    sf::Font font;
    void InitializePlayer(sf::RenderWindow &window);
    sf::CircleShape PlayerInfoCircle;

public:
    explicit Player(std::string &name,PlayerColor color,int id,sf::RenderWindow& window);
    //setters
    void setCash(int amount);
    void setJail(int time);
    void setRecentDice(int dice_);
    void IncreaseNumRailRoad();
    void AddCity(const std::string& city);
    void AddEstate(Estate * estate);
    void setChanceDraw(bool flag);
    void IncreaseJailCard();
 // void setPosition(int dice);

 //getters
    std::string getName();
    [[nodiscard]] std::string getColor() const;
    [[nodiscard]] int getCash() const;
    [[nodiscard]] int getJail() const;
    [[nodiscard]] int getRecentDice() const;
    [[nodiscard]] int getRailRoad() const;
    int getRepeatDouble() const;

    bool getChanceDraw() const;
    int getID() const;
    int getJailCard() const;
    sf::CircleShape & getCircle();

    //Square* getPosition();

    //
    void CollectRent(Player &p,int rent);
    bool OwnCity(const std::string& City);
    void Move(int steps,sf::RenderWindow &window);
    void DrawInfo(sf::RenderWindow &window);
    void MoveTo(const std::string& location,sf::RenderWindow &window);
    void increaseRepeatDouble();
    void resetRepeatDouble();
};


#endif //MONOPOLY_PLAYER_HPP
