
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
    } else {
        curr_rent = this->BaseRent * (int)pow(2, this->HouseCount); // Rent based on houses
    }
    std::string message;
    if(player.getCash()<curr_rent){
        player.setBankruptcy();
        this->owner->CollectBankruptcy(player);
        message = player.getName() + "Has Just Bankruptcy, wish him better Luck next time.."
                                     ""+this->owner->getName()+"Took all your possession!";
        updateMessage(message, window);
    }
    else {
        // Collect rent from the player
        this->owner->CollectRent(player, curr_rent);
        // Create a message to display
        message = player.getName() + " pay up!  $" + std::to_string(curr_rent) + " to: " + this->get_owner()->getName();
        updateMessage(message, window);

     }
    }

void Street::OwnerAction(Player &player, sf::RenderWindow &window) {
    // Check if the street is upgradable
    if (upgradable) {
        // Check if the maximum number of houses (4) is reached
        if (HouseCount == 4) {
            std::string message = "You can build a hotel on " + name + ". Would you like to proceed? ";
            updateMessage(message, window);
            // Create hotel option button (you may implement a Button class)
            Button buildHotelButton(60, 40, "Build Hotel",font, sf::Color::Green, [&]() {
                if (player.getCash() >= HotelCost) { // Assume hotelCost is defined
                    player.setCash(-HotelCost);
                    Hotel = true;            // Indicate hotel is built
                    // Update the GUI and display success message
                    updateMessage("Hotel built on " + name + "!", window);
                } else {
                    updateMessage("Not enough money to build a hotel.", window);
                }
            });
            // Render hotel button
            buildHotelButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 + 100);
            buildHotelButton.render(window);
            window.display();
        } else {
            // Show house offer in GUI
            std::string message = "You can build a house on " + name + ". Would you like to proceed?";
            updateMessage(message, window);

            // Create house option button (you may implement a Button class)
            Button buildHouseButton(60, 40, "Build House", font, sf::Color::Green, [&]() {
                if (player.getCash() >= HouseCount) { // Assume houseCost is defined
                    player.setCash(-HouseCost);
                    HouseCount++;
                    // Update the GUI and display success message
                    updateMessage("House built on " + name + "!", window);
                } else {
                    updateMessage("Not enough money to build a house.", window);
                }
            });

            // Render house button
            buildHouseButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 + 100);
            buildHouseButton.render(window);
            window.display();
        }
    } else {
       // updateMessage("You cannot build at the moment on this property.", window);
    }
}

std::string Street::getCity() const {
    return this->city;
}
void Street::drawHousesAndHotel(sf::RenderWindow &window)  {
    // Drawing houses as circles
    float houseRadius = 10.0f;  // Size of the house (circle)
    sf::CircleShape house(houseRadius);
    house.setFillColor(sf::Color::Green);
    for (int i = 0; i < this->HouseCount; i++) {
        house.setPosition(50 + i * 30, 50);  // Adjust the position for each house
        window.draw(house);
    }

    // Drawing a hotel as a triangle
    if (this->Hotel) {
        sf::ConvexShape hotel;
        hotel.setPointCount(3);  // Triangle shape
        hotel.setPoint(0, sf::Vector2f(100, 30));  // Top
        hotel.setPoint(1, sf::Vector2f(120, 70));  // Bottom right
        hotel.setPoint(2, sf::Vector2f(80, 70));   // Bottom left
        hotel.setFillColor(sf::Color::Red);
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

