#include <utility>
#include <iostream> // Include this for std::cerr
#include "Square.hpp"

// Constructor
Square::Square(const std::string &name) :name((name)) {}

// Other methods remain the same
void Square::setName(std::string _name) {
    this->name = std::move(_name);
}

std::string Square::getName() {
    return this->name;
}

Square::~Square() = default;

void Square::updateMessage(const std::string &message, sf::RenderWindow &window) {
    // Create a font object
    sf::Font font;
    // Load the font from a file
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
        std::cerr << "Error: Could not load font Lato-BlackItalic.ttf!" << std::endl;
        return;
    }

    // Create message text
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(16);
    messageText.setFillColor(sf::Color::Black);
    messageText.setString(message);

    // Center the text
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(800 / 2, 800 - 200); // Position at the bottom center of the window

    // Draw the message
    window.clear(); // Clear the window before drawing
    window.draw(messageText);
    window.display();

    sf::sleep(sf::seconds(3));
}
