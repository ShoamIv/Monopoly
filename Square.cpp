#include <utility>
#include <iostream> // Include this for std::cerr
#include "Square.hpp"

// Constructor
Square::Square(const std::string &name) :name((name)) {}

// Other methods remain the same
void Square::setName(std::string _name) {
    this->name = std::move(_name);
}

std::string Square::getName() {
    return this->name;
}

Square::~Square() = default;


