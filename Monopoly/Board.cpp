#include "Board.h++"
#include "Street.h++"
#include "Infrastructure.h++"

Board * Board::ptr = nullptr;

Board::Board() {
    initializeBoard();
}

Board * Board::getBoard() {
    if (ptr == nullptr) {
        ptr = new Board();
    }
    return ptr;
}

void Board::addSquare(std::unique_ptr<Square> square) {
    board.push_back(std::move(square));  // Move unique_ptr into the vector
}

void Board::initializeBoard() {
    addSquare(std::make_unique<SpecialSquare>("Go"));
    addSquare(std::make_unique<Street>("Neve-Ofer", "Beer-Sheva", 1, 60, 4));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("Ramot", "Beer-Sheva", 1, 400, 50));
    addSquare(std::make_unique<SpecialSquare>("Tax"));
    addSquare(std::make_unique<Infrastructure>("Railroad", 200, 50));

    // Add other squares similarly...
}

std::vector<std::unique_ptr<Square>>& Board::getSquares() {
    return board;
}
