//
// Created by Shoham on 13/09/2024.
//

#include <utility>

#include "Player.h++"

Player::Player(std::string &name,int id) : name(std::move(name)), id(id),curr_position(0),cash(1500){}

void Player::setCash(int amount) {
    this->cash=cash+amount;
}

std::string Player::get_name() {
    return this->name;
}

int Player::getCash() {
    return this->cash;
}

void Player::set_jail(int time) {
this->jail_time+=time;
}

int Player::get_jail_time() {
    return this->jail_time;
}

void Player::set_pos(int dice) {
    this->curr_position=(this->curr_position+dice)%40;
}

int Player::get_id() {
    return id;
}

