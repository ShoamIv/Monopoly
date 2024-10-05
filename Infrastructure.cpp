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
    int curr_rent = 50 * this->owner->getRailRoad();
    if(player.getCash()<curr_rent){
        player.setBankruptcy();
        this->owner->CollectBankruptcy(player);
        message = player.getName() + "Has Just Bankruptcy, wish him better Luck next time.."
                                     " "+this->owner->getName()+"Took all your possession!";
        updateMessage(message, window);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(3));

    }else
    this->owner->CollectRent(player, curr_rent);

}

void Infrastructure::drawHousesAndHotel(sf::RenderWindow &window) {
    if(owner==nullptr) return;           //safety
// Display Street Name
    sf::Text InfrastructureText;
    InfrastructureText.setFont(font); // Ensure the font is loaded
    InfrastructureText.setCharacterSize(12); // Text size
    InfrastructureText.setFillColor(owner->getColor()); // Default text color
    // Display Street Name
    int curr_position = this->owner->getPositionIndex(this->getName());
    InfrastructureText.setString(owner->getName() +" Estate");
    sf::Vector2f streetPosition = this->position;

    // Positioning the estate marker based on the current position on the board
    if (curr_position < 11) { // Bottom row (0 to 10)
        InfrastructureText.setPosition(streetPosition.x +10, streetPosition.y - 20);
    }
    else if (curr_position < 20) { // Left side (11 to 19)
        InfrastructureText.setPosition(streetPosition.x+80, streetPosition.y + 30 );
    }
    else if (curr_position < 31) { // Top row (20 to 30)
        InfrastructureText.setPosition(streetPosition.x+10, streetPosition.y + 75);
    }
    else { // Right side (31 to 39)
        InfrastructureText.setPosition(streetPosition.x-70, streetPosition.y+35);
    }
    window.draw(InfrastructureText);
}


