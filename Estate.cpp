#include "Player.hpp"
#include "Estate.hpp"

Estate::Estate(const std::string &name, int cost) : Square(name), cost(cost) {}

void Estate::set_cost(int _cost) {
    this->cost=_cost;
}

void Estate::set_owner(Player *_owner) {
    this->owner=_owner;
}

int Estate::get_cost() const {
    return this->cost;
}

Player * Estate::get_owner() {
    return this->owner;
}

void Estate::BuyEstate(Player &player, sf::RenderWindow &window) {

    // Initialize buttons
    yesButton = Button(60, 40, "Yes", font, sf::Color::Green, [&]() {
        std::cout << "Yes button clicked!" << std::endl;
    });
    noButton = Button(60, 40, "No", font, sf::Color::Red, [&]() {
        std::cout << "No button clicked!" << std::endl;
    });

    // Set button positions
    yesButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 + 100);
    noButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 100);

    // Create the purchase message
    std::string message = "Would you like to buy " + name + " Estate for $" + std::to_string(cost) + "?";
    yesButton.render(window); // Render Yes button
    noButton.render(window);  // Render No butto
    updateMessage(message, window); // Display the initial message
    bool actionComplete = false;

    // Main loop for the BuyEstate interaction
    while (window.isOpen() && !actionComplete) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; // Exit if the window is closed
            }

            // Handle button clicks
            if (yesButton.handleClick(window)) {
                // Handle purchase
                if (player.getCash() >= cost) {
                    this->owner = &player;
                    player.setCash(-cost); // Deduct cost
                    message = player.getName() + " bought: " + name;
                    if(this->getName()=="Railroad"){
                        player.IncreaseNumRailRoad();
                    }
                    player.AddEstate(*this);
                    updateMessage(message, window);
                } else {
                    message = "Not enough money to buy: " + name;
                    updateMessage(message, window);
                }
                actionComplete = true; // Complete the action
            }

            if (noButton.handleClick(window)) {
                // Player chose not to buy the property
                message = player.getName() + " decided not to buy: " + name;
                updateMessage(message, window);
                actionComplete = true; // Complete the action
            }
        }
    }
}










