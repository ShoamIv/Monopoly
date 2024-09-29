#include "Player.hpp"
#include "Estate.hpp"

Estate::Estate(const std::string &name, int cost) : Square(name), cost(cost) {}

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






