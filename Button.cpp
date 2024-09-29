#include <iostream>
#include <utility>
#include "Button.hpp"

// Default constructor
Button::Button() = default;

// Parameterized constructor to initialize the button
Button::Button(float width, float height, const std::string &label, sf::Font &font, const sf::Color &color, std::function<void()> click)
        : Click(std::move(click)) // Initialize the click callback
{
    shape.setSize(sf::Vector2f(width, height)); // Set button size
    shape.setFillColor(color); // Set button color

    text.setFont(font); // Set button text font
    text.setString(label); // Set button label
    text.setCharacterSize(24); // Set text size
    text.setFillColor(sf::Color::Black); // Set text color

    // Center text within the button
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

// Render the button on the window
void Button::render(sf::RenderWindow &window)
{
    window.draw(shape); // Draw button shape
    window.draw(text);  // Draw button text
}

// Set the position of the button and center the text
void Button::setPosition(float x, float y)
{
    shape.setPosition(x, y); // Set button position
    text.setPosition(x + shape.getSize().x / 2, y + shape.getSize().y / 2); // Center text
}

// Check if the mouse is hovering over the button
bool Button::isHovered(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Get mouse position
    sf::FloatRect bounds = shape.getGlobalBounds(); // Get button bounds
    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); // Check for hover
}

// Handle mouse click events
bool Button::handleClick(sf::RenderWindow &window)
{
    if (isHovered(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Check if button is hovered and clicked
        if (Click) {
            Click(); // Call the associated function
        }
        return true; // Indicate the button was clicked
    }
    return false; // Indicate the button was not clicked
}

// Return the global bounds of the button's shape
sf::FloatRect Button::getGlobalBounds() const {
    return shape.getGlobalBounds();
}
