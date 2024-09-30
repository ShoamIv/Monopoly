#include "Player.hpp"
#include "Infrastructure.hpp"

Infrastructure::Infrastructure(const std::string& name, int cost) : Estate(name, cost) {}

void Infrastructure::action(Player &player, sf::RenderWindow &window) {
    if (this->owner == nullptr) {
        BuyEstate(player,window);
        return;
    }
    if (player.getName() == this->get_owner()->getName()) {
        std::string message= "Welcome sir to Your Estate, Good Luck";
        updateMessage(message,window);
        window.display();
        return; // Player already owns this property
    }

    std::string companyName = this->getName();
    std::string message= player.getName() + " stepped on " + companyName + " owned by " + this->owner->getName() + ".";
    updateMessage(message,window);
    window.display();

    if (companyName == "Electric Company") {
        CompanyAction(player,window);
    } else if (companyName == "Water Company") {
        CompanyAction(player,window);
    } else if (companyName == "Railroad") {
        RailroadAction(player,window);
    }
}

void Infrastructure::CompanyAction(Player &player, sf::RenderWindow &window) {
    std::string message;
    int diceRoll = player.getRecentDice();
    int curr_rent = 10 * diceRoll;
    if(player.getCash()<curr_rent){
        player.setBankruptcy();
        message = player.getName() + "Has Just Bankruptcy, wish him better Luck next time.."
                                     ""+this->owner->getName()+"Took all your possession!";
        updateMessage(message, window);
        window.display();
    }else
    this->owner->CollectRent(player, curr_rent);
}

void Infrastructure::RailroadAction(Player &player, sf::RenderWindow &window) {
    std::string message;
    this->owner->IncreaseNumRailRoad();
    int curr_rent = 50 * this->owner->getRailRoad();
    if(player.getCash()<curr_rent){
        player.setBankruptcy();
        this->owner->CollectBankruptcy(player);
        message = player.getName() + "Has Just Bankruptcy, wish him better Luck next time.."
                                     ""+this->owner->getName()+"Took all your possession!";
        updateMessage(message, window);
        window.display();

    }else
    this->owner->CollectRent(player, curr_rent);

}

void Infrastructure::drawHousesAndHotel(sf::RenderWindow &window) {
    if (owner!= nullptr) { // If there is a house
        sf::CircleShape houseShape(10); // Circle representing the house
        houseShape.setFillColor(sf::Color::Green); // House color
        // Set the position relative to the square position
        houseShape.setPosition(50 + 1 * 30, 50);  // Adjust the position for each house
        window.draw(houseShape); // Draw the house
        }
    }


