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
                                     ""+this->owner->getName()+"Took all your possession!";
        updateMessage(message, window);
        window.display();

    }else
    this->owner->CollectRent(player, curr_rent);

}

void Infrastructure::drawHousesAndHotel(sf::RenderWindow &window) {
    if(owner==nullptr)return;
    sf::Text estateText;
    estateText.setFont(font); // Ensure you have loaded the font
    estateText.setString(owner ? owner->getName() + " Infrastructure " : ""); // Check if there is an owner
    estateText.setCharacterSize(12); // Set the size of the text    estateMarker.setFillColor(owner->getColor()); // Set the color based on the owner's color
    estateText.setFillColor(owner->getColor());

    int curr_position = this->owner->getPositionIndex(this->getName());
    // Positioning the estate marker based on the current position on the board
    if (curr_position < 11) { // Bottom row (0 to 10)
        estateText.setPosition(BOARD_WIDTH + 10 - (curr_position + 1) * SQUARE_SIZE + 3, BOARD_HEIGHT - SQUARE_SIZE + 5 * (owner->getID() + 1)-20);
    }
    else if (curr_position < 20) { // Left side (11 to 19)
        estateText.setPosition(80, BOARD_HEIGHT - (curr_position - 10) * SQUARE_SIZE + 5 * (owner->getID() + 1)-50);
    }
    else if (curr_position < 31) { // Top row (20 to 30)
        estateText.setPosition((curr_position - 20) * SQUARE_SIZE + 10, 5 * (owner->getID() + 1)+70);
    }
    else { // Right side (31 to 39)
        estateText.setPosition(BOARD_WIDTH - SQUARE_SIZE - 60, (curr_position - 30) * SQUARE_SIZE + 5 * (owner->getID() + 1));
    }
    window.draw(estateText);

}


