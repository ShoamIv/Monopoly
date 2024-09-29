
#include <utility>
#include <unordered_map>
#include "SpecialSquare.hpp"
#include "Button.hpp"
#include "Dice.hpp"
SpecialSquare::SpecialSquare(const std::string & name) : Square((name)) {
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {  // Ensure you have the correct path to your font file
        std::cerr << "Error: Could not load font Lato-BlackItalic.ttf!" << std::endl;
    }
}

// Map string names to SquareType enumeration values
SpecialSquare::SquareType SpecialSquare::getSquareType() const {
    static const std::unordered_map<std::string, SquareType> nameToType = {
            {"Jail", SquareType::GoToJail},
            {"GoToJail",    SquareType::GoToJail},
            {"Chance",      SquareType::Chance},
            {"Tax",         SquareType::Tax},
            {"Free Parking", SquareType::FreeParking}
    };
    auto it = nameToType.find(name);
    if (it != nameToType.end()) {
        return it->second;
    }
    return SquareType::Unknown;
}

void SpecialSquare::action(Player & player, sf::RenderWindow &window) {
    switch (getSquareType()) {
        case SquareType::GoToJail:
            GotoJail(player,window);
            break;
        case SquareType::Chance:
            Chance(player,window);
            break;
        case SquareType::Tax:
            Tax(player,window);
            break;
        case SquareType::FreeParking:
            FreeParking(player,window);
            break;
        default:
            std::cout << "Unknown special square type!" << std::endl;
            break;
    }
}
void SpecialSquare::GotoJail(Player &player, sf::RenderWindow &window) {
    // Jail message
    sf::Text jailMessage;
    jailMessage.setFont(font);
    jailMessage.setString("You are in jail. Pay $50 to get out or roll the dice.");
    jailMessage.setCharacterSize(24);
    jailMessage.setFillColor(sf::Color::Black);
    jailMessage.setPosition(BOARD_WIDTH / 2 - jailMessage.getGlobalBounds().width / 2, BOARD_HEIGHT / 2 - 100);

    // GUI text box for displaying messages
    sf::Text messageBox;
    messageBox.setFont(font);
    messageBox.setCharacterSize(20);
    messageBox.setFillColor(sf::Color::Black);
    messageBox.setPosition(BOARD_WIDTH / 2 - 150, BOARD_HEIGHT / 2 + 100); // Center the message box
    std::string message = "Welcome to jail!";
    messageBox.setString(message); // Initial message
    bool pressed=false;
    // Pay button
    Button payButton(100, 50, "Pay", font, sf::Color::Green, [&]() {
        if (player.getCash() >= 50) {
            player.setCash(-50); // Deduct $50 for paying bail
            message = "You paid $50 to get out of jail.";
            player.setJail(0); // Free the player from jail
        } else {
            message = "You don't have enough cash to pay!";
        }
        messageBox.setString(message); // Update GUI text box
    });
    payButton.setPosition(BOARD_WIDTH / 2 - 120, BOARD_HEIGHT / 2);

    // Roll button
    Button rollButton(100, 50, "Roll", font, sf::Color::Red, [&]() {
        Dice dice;
        auto [roll1, roll2] = dice.roll(); // Roll the dice
        message = "You rolled: " + std::to_string(roll1) + " and " + std::to_string(roll2) + ". "; // Show rolled values

        if (roll1 == roll2) {
            message += "Congratulations, you are free!";
            player.setJail(0); // Free the player from jail
        } else {
            message += "You remain in jail.";
        }
        messageBox.setString(message); // Update GUI text box
    });
    rollButton.setPosition(BOARD_WIDTH / 2 + 20, BOARD_HEIGHT / 2);

    // Main loop for displaying the jail screen
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle button clicks
            if (payButton.handleClick(window)) {
                pressed=true;
                payButton.Click(); // Execute the pay action
            }
            if (rollButton.handleClick(window)) {
                pressed=true;
                rollButton.Click(); // Execute the roll action
            }
        }
        if(pressed)break;
        // Render the updated UI
        window.clear(sf::Color::White);  // Clear the window
        window.draw(jailMessage);
        window.draw(messageBox);
        payButton.render(window);
        rollButton.render(window);
        window.display(); // Update the display with the new state
    }
}


void SpecialSquare::Tax(Player &player, sf::RenderWindow &window) {
    // Deduct tax from player
    player.setCash(-100);

    // Create message text
    sf::Text message;
    message.setFont(font); // Use the passed font
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::Black);
    message.setString("Tax of $100 has been deducted from your account.\n"
                      "Your current balance is $" + std::to_string(player.getCash()) + ".");

    // Center the text
    sf::FloatRect textRect = message.getLocalBounds(); // Get the bounds of the text
    message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Set origin to the center
    message.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 - 50); // Position the message at the center-top

    // Create a flag to handle closing the window
    bool closePressed = false;

    // Create a button to close the message
    Button closeButton(100, 50, "OK", font, sf::Color::Green, [&]() {
        closePressed = true; // Set the flag to true when clicked
    });

    // Center the button below the message
    closeButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 50); // Adjusted position to center the button

    // Main loop to display the GUI
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                closeButton.handleClick(window); // Process button click
            }
        }

        // Break the loop if the button was pressed
        if (closePressed) {
            break;
        }

        window.clear(sf::Color::White);
        window.draw(message);        // Draw the message
        closeButton.render(window);  // Render the close button
        window.display();
    }
}



SpecialSquare::~SpecialSquare() = default;



void SpecialSquare::Chance(Player &player, sf::RenderWindow &window) {
    player.setChanceDraw(true); // Mark that the player can draw a chance card

    // Create message text
    sf::Text message;
    message.setFont(font); // Use the passed font
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::Black);
    message.setString(player.getName() + " landed on the Chance spot!\nGood Luck...");

    // Center the text
    sf::FloatRect textRect = message.getLocalBounds(); // Get the bounds of the text
    message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Set origin to the center
    message.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 - 50); // Position the title at the center-top

    // Create a button to close the message
    bool closePressed = false; // This flag will determine when to close the message
    Button closeButton(100, 50, "OK", font, sf::Color::Green, [&]() {
        closePressed = true; // Set flag when button is clicked
    });

    // Center the button below the message
    closeButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 50); // Adjusted position to center button below text

    // Main loop to display the GUI
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                closeButton.handleClick(window); // Process button click
            }
        }

        // Exit the loop if the button was pressed
        if (closePressed) {
            break;
        }

        window.clear(sf::Color::White);
        window.draw(message);        // Draw the message
        closeButton.render(window);  // Render the close button
        window.display();
    }
}

void SpecialSquare::FreeParking(Player &player, sf::RenderWindow &window) {
    // Create message text
    sf::Text message;
    message.setFont(font); // Assume `font` is initialized globally or passed as a parameter
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::Black);
    message.setString(player.getName() + " landed on a Free Parking spot!\nEnjoy your break, mate!");

    // Center the text
    sf::FloatRect textRect = message.getLocalBounds(); // Get the bounds of the text
    message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Set origin to the center
    message.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 - 50); // Position the message at the center-top of the window

    // Create a button to close the message
    Button closeButton(100, 50, "OK", font, sf::Color::Green, [&]() { /* Close message */ });

    // Center the button below the message
    closeButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 + 10); // Position below the text

    // Main loop to display the GUI
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (closeButton.handleClick(window)) {
                    // Break the loop to close the message window when the button is clicked
                    return; // Exit the function
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(message); // Draw the message
        closeButton.render(window); // Render the close button
        window.display();
    }
}
