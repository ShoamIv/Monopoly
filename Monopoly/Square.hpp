
#ifndef MONOPOLY_SQUARE_HPP
#define MONOPOLY_SQUARE_HPP
#include <string>
#include <iostream>

class Player;
class Square {

protected:
    std::string name;
public:
    explicit Square(std::string name);
    //setters
    void setName(std::string _type);
    //getters
    std::string getName();
    //abstract function, all classes must implement this function:
    virtual void action(Player & player)=0;
    virtual  ~Square();
};


#endif //MONOPOLY_SQUARE_HPP
