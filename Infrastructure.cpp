#include "Player.hpp"
#include "Infrastructure.hpp"


Infrastructure::Infrastructure(const std::string& name, int cost) : Estate(name,cost){}

void Infrastructure::action(Player &player, sf::RenderWindow &window) {
    if (this->owner == nullptr) {
        this->owner=&player;
        player.setCash(-(200));
    }
    if (player.getName() == this->get_owner()->getName()) {
        return;
    }
    if (this->getName() == "Electric Company") {
        std::cout << player.getName() << "Stepped at Electric Company Own by:" << this->owner->getName() << std::endl;
        CompanyAction(player);
    }
    if (this->getName() == "Water Company") {
        std::cout << player.getName() << "Stepped at Water Company Own by:" << this->owner->getName() << std::endl;
        CompanyAction(player);
    }
    if (this->getName() == "Railroad") {
        std::cout << player.getName() << "Stepped at Railroad Own by:" << this->owner->getName() << std::endl;
        RailroadAction(player);
    }
}

void Infrastructure::CompanyAction(Player &player) {
    int diceRoll = player.getRecentDice();
    int curr_rent = 10 * diceRoll;
    this->owner->CollectRent(player,curr_rent);
}

void Infrastructure::RailroadAction(Player &player) {
  int curr_rent=50*this->owner->getRailRoad();
  this->owner->CollectRent(player,curr_rent);
}
