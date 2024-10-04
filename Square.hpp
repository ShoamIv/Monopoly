
#ifndef MONOPOLY_SQUARE_HPP
#define MONOPOLY_SQUARE_HPP
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
/**
 * @class Square
 * @brief The abstract base class representing a square on the Monopoly board.
 *
 * The `Square` class defines the common interface and properties for any type of square in the Monopoly game,
 * such as Streets, Chance squares, or other special board spaces. It contains common attributes such as
 * the square's name and position on the board, and mandates the implementation of the `action` method for
 * all derived classes, which will define the specific behavior when a player lands on that square.
 */

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
