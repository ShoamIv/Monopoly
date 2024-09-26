#include "Player.hpp"
#include "Estate.hpp"

Estate::Estate(const std::string &name, int cost):Square(name),cost(cost),owner(nullptr){}

void Estate::set_cost(int _cost) {
    this->cost=_cost;
}


void Estate::set_owner(Player *_owner) {
    this->owner=_owner;
}

int Estate::get_cost() const {
    return this->cost;
}

Player * Estate::get_owner() {
    return this->owner;
}

void Estate::Acquisition(Player &player) {

    if (player.getCash() < this->get_cost()) {
        std::cout << "Hello Amigo!\n" << "You do not have enough Cash to make this purchase!\n Good Luck\n";
    }
    std::cout << "Hello Amigo!\n this estate: " << this->getName() << " has no owner!\n" <<
              "Would you like to Acquire this profit Asset?\n" << "Its in Sale only for: " << this->get_cost();
    int num;
    std::cin >> num;
    if (num == 1) {
        this->owner = &player;
        this->owner->AddEstate(this);
        this->owner->setCash(-(this->get_cost()));
        std::cout << this->owner->getName() << " is the New owner of: " << this->getName() << " Congrats!\n";
    } else {
        std::cout << player.getName() << "Hmmm, Your Lost Sir!\n";
    }
}



