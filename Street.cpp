
#include "player.hpp"
#include <utility>
#include "Street.hpp"

Street::Street(const std::string& name,std::string  city,int color, int cost, int BaseRent) :
        Estate(name,cost),BaseRent(BaseRent),city(std::move(city)) {}

void Street::action(Player &player, sf::RenderWindow &window) {
    if(this->owner== nullptr){
        this->owner= &player;
        player.setCash(-(this->cost));

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
        curr_rent = this->BaseRent * (int)pow(2, this->Houses); // Rent based on houses
    }

    // Collect rent from the player
    this->owner->CollectRent(player, curr_rent);

    // Create a message to display
    std::string message = player.getName() + " pay up!  $" + std::to_string(curr_rent) + " to: " + this->get_owner()->getName();
    updateMessage(message, window);
}


void Street::OwnerAction() {
    if(this->owner->OwnCity(this->city)){
    }
}

int Street::getBaseRent() const {
    return this->BaseRent;
}

std::string Street::getCity() const {
    return this->city;
}


