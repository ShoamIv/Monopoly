
#include "player.hpp"
#include <utility>
#include "Street.hpp"

Street::Street(const std::string& name,std::string  city,int color, int cost, int BaseRent) :
        Estate(name,cost),BaseRent(BaseRent),city(std::move(city)),color(color) {}

void Street::action(Player &player) {
    if(this->owner== nullptr){
        Acquisition(player);
    }
    else if(player.getName()==this->owner->getName()){
        OwnerAction();
    }
    else if(player.getName()!=this->owner->getName())
    VisitorAction(player);
}

void Street::VisitorAction(Player &player) {
 if(this->Hotel){
     ////////hotel rent logic
     return;
 }
 int curr_rent= this->BaseRent * (int)pow(2,this->Houses);
 this->owner->CollectRent(player,curr_rent);
}

void Street::OwnerAction() {
    if(this->owner->OwnCity(this->city)){
        std::cout<<"Welcome sir\n"<<"Would you like to";
    }
}

int Street::getBaseRent() const {
    return this->BaseRent;
}

