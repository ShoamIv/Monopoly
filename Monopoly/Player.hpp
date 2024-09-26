
#ifndef MONOPOLY_PLAYER_HPP
#define MONOPOLY_PLAYER_HPP
#include <string>
#include <vector>
#include "Estate.hpp"
#include "Dice.hpp"

class Player {
    std::string name;
    std::string color;
    Square*  curr_position;                //current position in the game.
    int cash;                         // holds for the money the player has.
    int jail_time=0;
    int dice{};                        //recent diceRoll.
    int NumOfRailRoad=0;
    std::vector<Estate*> Estates;       //Player Estates
    /*
     * list of cities the player own
     * a Player that Owns entire city-> able to require houses.
     */
    std::vector<std::string> CityOwner;
public:
    explicit Player(std::string &name,std::string &color);
    //setters
    void setCash(int amount);
    void setJail(int time);
    void setRecentDice(int dice_);
    void IncreaseNumRailRoad();
    void AddCity(const std::string& city);
    void AddEstate(Estate * estate);
 // void setPosition(int dice);

 //getters
    std::string getName();
    [[nodiscard]] std::string getColor() const;
    [[nodiscard]] int getCash() const;
    [[nodiscard]] int getJail() const;
    [[nodiscard]] int getRecentDice() const;
    [[nodiscard]] int getRailRoad() const;
    //Square* getPosition();

    //
    void CollectRent(Player &p,int rent);
    bool OwnCity(const std::string& City);

};


#endif //MONOPOLY_PLAYER_HPP
