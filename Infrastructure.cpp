#include "Player.hpp"
#include "Infrastructure.hpp"

Infrastructure::Infrastructure(const std::string& name, int cost) : Estate(name, cost) {}

void Infrastructure::action(Player &player, sf::RenderWindow &window) {
    if (this->owner == nullptr) {
        this->owner = &player;
        player.IncreaseNumRailRoad();
        player.setCash(-200);
        std::string message=player.getName() + " bought " + this->getName() + " for $200.";
        updateMessage(message,window);
        return;
    }

    if (player.getName() == this->get_owner()->getName()) {
        return; // Player already owns this property
    }

    std::string companyName = this->getName();
    std::string message= player.getName() + " stepped on " + companyName + " owned by " + this->owner->getName() + ".";
    updateMessage(message,window);

    if (companyName == "Electric Company") {
        CompanyAction(player);
    } else if (companyName == "Water Company") {
        CompanyAction(player);
    } else if (companyName == "Railroad") {
        RailroadAction(player);
    }
}

void Infrastructure::CompanyAction(Player &player) {
    int diceRoll = player.getRecentDice();
    int curr_rent = 10 * diceRoll;
    this->owner->CollectRent(player, curr_rent);
}

void Infrastructure::RailroadAction(Player &player) {
    int curr_rent = 50 * this->owner->getRailRoad();
    this->owner->CollectRent(player, curr_rent);
}

