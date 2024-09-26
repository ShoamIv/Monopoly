#include <utility>
#include "Player.hpp"

Player::Player(std::string &name,std::string &color) : name((name)),color(color),curr_position(nullptr),cash(0){}

void Player::setCash(int amount) {
    this->cash=cash+amount;
}

std::string Player::getName() {
    return this->name;
}

int Player::getCash() const {
    return this->cash;
}

std::string Player::getColor() const {
    return color;
}

void Player::setJail(int time) {
this->jail_time+=time;
}

int Player::getJail() const {
    return this->jail_time;
}

int Player::getRecentDice() const {
    return this->dice;
}

void Player::setRecentDice(int dice_) {
 this->dice=dice_;
}

void Player::CollectRent(Player &p,int rent) {
 this->cash+=rent;
 p.cash-=rent;
 std::cout<<p.getName()<< "Paid Rent at amount of:" << rent << "to: " <<this->getName()<<std::endl;
}

int Player::getRailRoad() const {
    return this->NumOfRailRoad;
}

void Player::IncreaseNumRailRoad() {
    this->NumOfRailRoad++;
}

void Player::AddCity(const std::string& city) {
 this->CityOwner.emplace_back(city);
}

bool Player::OwnCity(const std::string& City) {
    for(const std::string& city : CityOwner){
        if(City==city){
            return true;
        }
    }
    return false;
}

void Player::AddEstate(Estate *estate) {
    this->Estates.emplace_back(estate);
}


/*
void Player::setPosition(int dice) {}(Square& dice) {
    this->curr_position=(this->curr_position+dice)%40;
}

*/

