#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

/**
 * @class Button
 * @brief Represents a clickable button in the GUI, with visual representation and interaction handling.
 */
class Button
{
private:
    sf::RectangleShape shape;    ///< Shape of the button, defined by a rectangle.
    sf::Text text;               ///< Text displayed on the button.

    /**
     * @brief Function to be called when the button is clicked.
     */
    std::function<void()> Click; ///< Callback function for the button click action.

public:
    /**
     * @brief Default constructor for the Button class.
     */
    Button();

    /**
     * @brief Parameterized constructor for creating a button with specific properties.
     * @param width Width of the button.
     * @param height Height of the button.
     * @param label The text label displayed on the button.
     * @param font Reference to the font used for the button text.
     * @param color The color of the button shape.
     * @param onClickAction The function to be called when the button is clicked.
     */
    Button(float width, float height, const std::string &label, sf::Font &font, const sf::Color &color, std::function<void()> onClickAction);

    /**
     * @brief Renders the button on the specified window.
     * @param window The SFML render window where the button will be drawn.
     */
    void render(sf::RenderWindow &window);

    /**
     * @brief Sets the position of the button.
     * @param x The x-coordinate of the button's position.
     * @param y The y-coordinate of the button's position.
     */
    void setPosition(float x, float y);

    /**
     * @brief Checks if the mouse is hovering over the button.
     * @param window The SFML render window to check the mouse position against.
     * @return true if the mouse is over the button, false otherwise.
     */
    bool isHovered(sf::RenderWindow &window);

    /**
     * @brief Handles click events for the button.
     * @param window The SFML render window to check for mouse clicks.
     * @return true if the button was clicked, false otherwise.
     */
    bool handleClick(sf::RenderWindow &window);

    /**
     * @brief Gets the global bounds of the button for collision detection.
     * @return A FloatRect representing the bounds of the button.
     */
    sf::FloatRect getGlobalBounds() const; // Added method to get button bounds
};

#endif // BUTTON_HPP
