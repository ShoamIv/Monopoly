
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
            {"FreeParking", SquareType::FreeParking}
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
    jailMessage.setString("You are in jail. Pay 50 to get out or roll the dice.");
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

    // Pay button
    Button payButton(100, 50, "Pay", font, sf::Color::Green, [&]() {
        message = handlePay(player); // Update message after payment
        messageBox.setString(message); // Update GUI text box
    });
    payButton.setPosition(BOARD_WIDTH / 2 - 120, BOARD_HEIGHT / 2);

    // Roll button
    Button rollButton(100, 50, "Roll", font, sf::Color::Red, [&]() {
        message = handleRoll(player); // Update message after dice roll
        messageBox.setString(message); // Update GUI text box
    });
    rollButton.setPosition(BOARD_WIDTH / 2 + 20, BOARD_HEIGHT / 2);

    // Render the jail message, buttons, and message box
    window.clear();
    window.draw(jailMessage);
    window.draw(messageBox);
    payButton.render(window);
    rollButton.render(window);
    window.display();

    // Event loop for buttons
    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (payButton.handleClick(window)) {
            // Player chooses to pay, update display
            window.clear();
            window.draw(jailMessage);
            window.draw(messageBox); // Update message box text
            payButton.render(window);
            rollButton.render(window);
            window.display();
        }

        if (rollButton.handleClick(window)) {
            // Player chooses to roll, update display
            window.clear();
            window.draw(jailMessage);
            window.draw(messageBox); // Update message box text
            payButton.render(window);
            rollButton.render(window);
            window.display();
        }
    }
}

std::string SpecialSquare::handlePay(Player &player) {
    int bailAmount = 50;
    player.setCash(-bailAmount);
    player.setJail(-(player.getJail())); // Free the player from jail
    // Return GUI-friendly message string
    return "You paid " + std::to_string(bailAmount) + " for bail.\nCurrent balance: " + std::to_string(player.getCash()) + ".";
}

std::string SpecialSquare::handleRoll(Player &player) {
    Dice dice;
    auto [roll1, roll2] = dice.roll();
    if (roll1 == roll2) {
        player.setJail(-(player.getJail())); // Free the player from jail
        return "Congratulations, you rolled doubles and are free!";
    } else {
        return "You rolled: " + std::to_string(roll1) + " and " + std::to_string(roll2) + ".";
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
    message.setString(player.getName() + " landed on a Free Parking spot!\nEnjoy your break mate!");
    // Center the text
    sf::FloatRect textRect = message.getLocalBounds(); // Get the bounds of the text
    message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Set origin to the center
    message.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 - 50); // Position the title at the center-top of the
    // Create a button to close the message
    Button closeButton(100, 50, "OK", font, sf::Color::Green, [&]() { /* Close message */ });
    // Center the button below the message
    closeButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2-100); // Position below the text
    // Main loop to display the GUI
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                closeButton.handleClick(window);
            }
        }

        window.clear(sf::Color::White);
        window.draw(message); // Draw the message
        closeButton.render(window); // Render the close button
        window.display();
    }
}
