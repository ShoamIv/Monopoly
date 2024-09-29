#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button
{
private:
    sf::RectangleShape shape;    // Shape of the button
    sf::Text text;               // Text displayed on the button
    // Function to be called on button click

public:
    Button();
    Button(float width, float height, const std::string &label, sf::Font &font, const sf::Color &color, std::function<void()> onClickAction);
    void render(sf::RenderWindow &window);
    void setPosition(float x, float y);
    bool isHovered(sf::RenderWindow &window);
    bool handleClick(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds() const; // Added method to get button bounds
    std::function<void()> Click;
};

#endif // BUTTON_HPP
