//
// Created by Shoham on 13/09/2024.
//

#include <utility>

#include "Square.h++"


Square::Square(std::string name) : name(std::move(name)){}


void Square::setName(std::string _name) {
    this->name=std::move(_name);
}

std::string Square::getName() {
    return this->name;
}

Square::~Square() = default;


