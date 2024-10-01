
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
    sf::Vector2f position;
    static sf::Text messageText;
    static sf::Font font;

public:
    explicit Square(const std::string &name);
    //setters
    void setName(std::string _type);
    void setPosition(sf::Vector2f pos);
    //getters
    std::string getName();
    //abstract function, all classes must implement this function:
    virtual void action(Player & player, sf::RenderWindow &window)=0;
    static void updateMessage(const std::string &message, sf::RenderWindow &window) ;
        virtual  ~Square();

    static void LoadFont();
};


#endif //MONOPOLY_SQUARE_HPP
