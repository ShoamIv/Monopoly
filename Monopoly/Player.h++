
#ifndef MONOPOLY_PLAYER_H
#define MONOPOLY_PLAYER_H
#include <string>
#include <vector>
#include "Estate.h++"
#include "Dice.h++"
class Player {
    std::string name;
    int id;
    int curr_position;                //current position in the game.
    int cash;                         // holds for the money the player has.
    int jail_time=0;

public:
    explicit Player(std::string &name,int id);
    //setters
    void setCash(int amount);
    void set_jail(int time);
    void set_pos(int dice);
    //getters

    std::string get_name();
    int get_id();
    int getCash();
    int get_jail_time();


};


#endif //MONOPOLY_PLAYER_H
