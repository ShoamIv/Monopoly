
#ifndef MONOPOLY_SQUARE_HPP
#define MONOPOLY_SQUARE_HPP
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Player;
class Square {

protected:
    std::string name;
public:
    explicit Square(const std::string &name);
    //setters
    void setName(std::string _type);
    //getters
    std::string getName();
    //abstract function, all classes must implement this function:
    virtual void action(Player & player, sf::RenderWindow &window)=0;
    virtual  ~Square();

};


#endif //MONOPOLY_SQUARE_HPP
