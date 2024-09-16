//
// Created by Shoham on 13/09/2024.
//

#include <utility>

#include "Estate.h++"

Estate::Estate(const std::string &name , int cost, int rent)
    :Square(name),cost(cost),rent(rent){}



void Estate::set_cost(int _cost) {
    this->cost=_cost;
}
void Estate::set_rent(int _rent) {
    this->rent=_rent;
}
void Estate::set_owner(std::string _owner) {
    this->owner=std::move(_owner);
}




int Estate::get_cost() const {
    return this->cost;
}

int Estate::get_rent() const {
    return this->rent;
}

std::string Estate::get_owner() {
    return this->owner;
}
