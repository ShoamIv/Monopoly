
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
    VisitorAction(player);
}

void Street::VisitorAction(Player &player) {
 if(this->Hotel){
     int curr_rent= this->BaseRent * 6;
 }
 int curr_rent= this->BaseRent * (int)pow(2,this->Houses);
 this->owner->CollectRent(player,curr_rent);
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


