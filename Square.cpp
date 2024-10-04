#include <utility>
#include <iostream> // Include this for std::cerr
#include "Square.hpp"
sf::Text Square::messageText;
sf::Font Square::font;
// Constructor
Square::Square(const std::string &name) :name((name)) {}

void Square:: setPosition(const sf::Vector2f pos) {
    this->position=pos;
}

std::string Square::getName() {
    return this->name;
}

Square::~Square() = default;

void Square::updateMessage(const std::string &message, sf::RenderWindow &window) {
    // Create a font object
    // Load the font from a file
    LoadFont();
    // Create message text
    messageText.setFont(font);
    messageText.setCharacterSize(16);
    messageText.setFillColor(sf::Color::Black);
    messageText.setString(message);
    // Center the text
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(800 / 2, 800 - 150); // Position at the bottom center of the window
    // Draw the message
    window.draw(messageText);
    window.display();
}

void Square:: LoadFont()
{
    // Load the font from a file
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
        std::cerr << "Error: Could not load font Lato-BlackItalic.ttf!" << std::endl;
        return;
    }

}
