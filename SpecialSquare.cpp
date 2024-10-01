
#include <utility>
#include <unordered_map>
#include "SpecialSquare.hpp"
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
        case SquareType::Jail:
            Jail(player,window);
            break;
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
    player.MoveTo("Jail",window);
    Jail(player,window);
}

void SpecialSquare::Tax(Player &player, sf::RenderWindow &window) {
    std::string messageStr;
    if(player.getCash()<100){
        messageStr= player.getName()+" Bankrupt, better Luck next time!";
        player.setBankruptcy();
        updateMessage(messageStr,window);
    }
    else {
        player.setCash(-100);            // Deduct tax from the player's account
        messageStr = "Tax of $100 has been deducted from your account.\n"
                     "Your current balance is $" + std::to_string(player.getCash()) + ".";
        updateMessage(messageStr, window);
        }
    }

void SpecialSquare::Chance(Player &player, sf::RenderWindow &window) {
    player.setChanceDraw(true);
}

void SpecialSquare::FreeParking(Player &player, sf::RenderWindow &window) {
    std::string messageStr = " landed on a Free Parking spot!\nEnjoy your break, mate!";
    updateMessage(messageStr, window);
}

void SpecialSquare::Jail(Player &player, sf::RenderWindow &window) {
    if(player.getJail()==0) {
        player.setJail(3);
        if (player.getJailCard() > 0) {
            player.setJailCard(-1);
            updateMessage("Tricky way to avoid jail, next time...\n jail card has used", window);
            player.setJail(-(player.getJail()));
            return;
        }
    }
    Button payButton(30, 30, "Pay $50", font, sf::Color::Green, [&]() {
        if (player.getCash() >= 50) {
            player.setCash( -50); // Deduct $50 for paying bail
            updateMessage("You paid $50 to get out of jail.", window);
            player.setJail(-(player.getJail()));   // Free the player from jail
        } else {
            player.setJail(-1);
            updateMessage("You don't have enough cash to pay! stay for another"
                          " "+std::to_string(player.getJail()) +" turns",window);
        }
    });

    Button rollButton(30, 30, "Roll Dice", font, sf::Color::Blue, [&]() {
        Dice dice;
        auto [roll1, roll2] = dice.roll(); // Roll the dice
        std::string message = "You rolled: " + std::to_string(roll1) + " and " + std::to_string(roll2) + ". ";
        if (roll1 == roll2) {
            message += "Congratulations, you are free!";
            player.setJail(-(player.getJail()));          // Free the player from jail
        } else {
            player.setJail(-1);
            message += "You remain in jail "+std::to_string(player.getJail()) + " turns";
        }
        updateMessage(message, window);
    });

    // Set button positions
    payButton.setPosition(BOARD_WIDTH / 2 - 70, BOARD_HEIGHT / 2 + 120);
    rollButton.setPosition(BOARD_WIDTH / 2 + 10, BOARD_HEIGHT / 2 + 120);
    // Display the initial jail message
    bool actionTaken = false;
    payButton.render(window); // Render Pay button
    rollButton.render(window); // Render Roll button
    updateMessage("You are in jail. Pay $50 to get out or roll the dice.", window);

    // Main loop for handling jail actions
    while (!actionTaken) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check button clicks
            if (payButton.handleClick(window)) {
                actionTaken = true; // End the loop after an action
            }

            if (rollButton.handleClick(window)) {
                actionTaken = true; // End the loop after an action
            }
        }
    }
}


SpecialSquare::~SpecialSquare() = default;
