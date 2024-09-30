
#ifndef MONOPOLY_SQUARE_HPP
#define MONOPOLY_SQUARE_HPP
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

class Player;
class Square {

protected:
    std::string name;
    static sf::Text messageText;
    static sf::Font font;

public:
    explicit Square(const std::string &name);
    //setters
    void setName(std::string _type);
    //getters
    std::string getName();
    //abstract function, all classes must implement this function:
    virtual void action(Player & player, sf::RenderWindow &window)=0;
    static void updateMessage(const std::string &message, sf::RenderWindow &window) ;
        virtual  ~Square();

    static void LoadFont(sf::Font &font);
};


#endif //MONOPOLY_SQUARE_HPP
