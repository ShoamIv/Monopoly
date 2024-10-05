
#include "player.hpp"
#include <utility>
#include "Street.hpp"

Street::Street(const std::string& name,std::string  city,int color, int cost, int BaseRent) :
        Estate(name,cost),BaseRent(BaseRent),city(std::move(city)) {}

void Street::action(Player &player, sf::RenderWindow &window) {
    if(this->owner== nullptr){
        this->BuyEstate(player,window);
    }

    else if(player.getName()==this->owner->getName()){
        OwnerAction(player,window);
    }
    else if(player.getName()!=this->owner->getName())
    VisitorAction(player,window);
}

void Street::VisitorAction(Player &player, sf::RenderWindow &window) {

    int curr_rent = 0;
    // Calculate rent based on the presence of a hotel
    if (this->Hotel) {
        curr_rent = this->BaseRent * 6; // Hotel rent calculation
    }
    else {
        curr_rent = this->BaseRent * (int)pow(2, this->HouseCount); // Rent based on houses
    }
    std::string message;
    if(player.getCash()<curr_rent){
        player.setBankruptcy();
        this->owner->CollectBankruptcy(player);
        message = player.getName() + "Has Just Bankruptcy, wish him better Luck next time.."
                                     " "+this->owner->getName()+"Took all your possession!";
        updateMessage(message, window);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    else {
        // Collect rent from the player
        this->owner->CollectRent(player, curr_rent);
        // Create a message to display
        message = player.getName() + " pay up!  $" + std::to_string(curr_rent) + " to: " + this->get_owner()->getName();
        updateMessage(message, window);
        std::this_thread::sleep_for(std::chrono::seconds(3));

      }
    }

void Street::OwnerAction(Player &player, sf::RenderWindow &window) {
    // Check if the street is upgradable
    if (upgradable) {
        std::string message;

        // Check if the maximum number of houses (4) is reached
        if (HouseCount == 4) {
            message = "You can build a hotel on " + name + ". Would you like to proceed?";
        } else {
            message = "You can build a house on " + name + ". Would you like to proceed?";
        }

        // Create "Build" button
        Button buildButton(80, 40, "Build", font, sf::Color::Green, []() {
            std::cout << "Build button clicked!" << std::endl;
        });

        // Create "Decline" button
        Button declineButton(80, 40, "Decline", font, sf::Color::Red, []() {
            std::cout << "Decline button clicked!" << std::endl;
        });

        // Set positions for the "Build" and "Decline" buttons
        buildButton.setPosition(BOARD_WIDTH / 2 - 100, BOARD_HEIGHT / 2 + 100);  // Adjust positioning
        declineButton.setPosition(BOARD_WIDTH / 2 + 100, BOARD_HEIGHT / 2 + 100);  // Adjust positioning

        // Wait for user input
        bool decisionMade = false;
        bool buildSelected = false;

        while (!decisionMade) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (buildButton.isHovered(window)) {
                        decisionMade = true;
                        buildSelected = true;  // Build option selected
                    }
                    if (declineButton.isHovered(window)) {
                        decisionMade = true;
                        buildSelected = false;  // Decline option selected
                    }
                }
            }

            // Display the message and render both buttons
            buildButton.render(window);
            declineButton.render(window);
            updateMessage(message, window);

            // Display everything
        }

        // Handle player's decision
        if (buildSelected) {
            // If the player clicked the "Build" button
            if (HouseCount == 4) {
                if (player.getCash() >= HotelCost) {
                    player.setCash(-HotelCost);
                    Hotel = true;  // Build the hotel
                } else {
                    updateMessage("Not enough money to build a hotel.", window);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            } else {
                if (player.getCash() >= HouseCost) {
                    player.setCash(-HouseCost);
                    HouseCount++;  // Build the house
                } else {
                    updateMessage("Not enough money to build a house.", window);
                }
            }
        } else {
            // If the player clicked the "Decline" button
            updateMessage("You have declined to build on " + name + ".", window);
        }
    }
}


std::string Street::getCity() const {
    return this->city;
}

void Street::drawHousesAndHotel(sf::RenderWindow &window)  {
    if(owner==nullptr) return;           //safety
// Display Street Name
    sf::Text streetText;
    streetText.setFont(font); // Ensure the font is loaded
    streetText.setCharacterSize(12); // Text size
    streetText.setFillColor(owner->getColor()); // Default text color
    // Display Street Name
    int curr_position = this->owner->getPositionIndex(this->getName());
    streetText.setString(owner->getName() +" Street");
    sf::Vector2f streetPosition = this->position;

    // Positioning the estate marker based on the current position on the board
    if (curr_position < 11) { // Bottom row (0 to 10)
        streetText.setPosition(streetPosition.x +10, streetPosition.y - 20);
    }
    else if (curr_position < 20) { // Left side (11 to 19)
        streetText.setPosition(streetPosition.x+80, streetPosition.y + 30 );
    }
    else if (curr_position < 31) { // Top row (20 to 30)
        streetText.setPosition(streetPosition.x+10, streetPosition.y + 75);
    }
    else { // Right side (31 to 39)
        streetText.setPosition(streetPosition.x-70, streetPosition.y+35);
    }
    window.draw(streetText);
    // Draw houses if exists:
        for (int i = 0; i < this->HouseCount; i++) {
            sf::RectangleShape house(sf::Vector2f(5, 5)); // Size of each house
            house.setFillColor(sf::Color::Green); // Color for houses
            house.setPosition(position.x + 5 + (i * 12), position.y + 5); // Positioning houses
            window.draw(house);
        }

        // Draw hotel if it exists
        if (Hotel) {
            sf::RectangleShape hotel(sf::Vector2f(7, 7)); // Size of the hotel
            hotel.setFillColor(sf::Color::Red); // Color for the hotel
            hotel.setPosition(position.x + 5, position.y - 15); // Position hotel above the estate
            window.draw(hotel);
        }
    }

void Street::isUpgradable(const std::vector<std::unique_ptr<Square>>& squares) {
    if (owner == nullptr) {
        return; // Can't upgrade if the street isn't owned
    }
    // Count the number of houses for this street
    int currentHouses = this->HouseCount;
    for (const auto& square : squares) {
        // Use dynamic_cast to check if the square is a Street
        if (auto* street = dynamic_cast<Street*>(square.get())) {
            if (street->getCity() == city && street->HouseCount!= currentHouses) {
                return; // If any other property in the group has a different number of houses, can't upgrade
            }
            if (street->getCity() == city && (street->owner==nullptr || street->owner!=this->owner)) {
                return;
            }
        }
    }
    // Ensure the current street has less than 4 houses (or your upgrade limit)
    if (Hotel) {
        return ; // Can't upgrade if there are already 4 houses
    }
    upgradable= true; // The street is upgradable
}

