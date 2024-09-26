
#include <utility>

#include "Square.hpp"


Square::Square(std::string name) : name(std::move(name)){}


void Square::setName(std::string _name) {
    this->name=std::move(_name);
}

std::string Square::getName() {
    return this->name;
}

Square::~Square() = default;


