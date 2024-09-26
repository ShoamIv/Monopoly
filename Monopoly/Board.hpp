#ifndef MONOPOLY_BOARD_HPP
#define MONOPOLY_BOARD_HPP
#include <vector>
#include <memory>
#include "Estate.hpp"
#include "SpecialSquare.hpp"

class Board {
    Board();
    static Board * ptr;
    std::vector<std::unique_ptr<Square>> board;  // Use unique_ptr for polymorphism
    void initializeBoard();
    void addSquare(std::unique_ptr<Square> square);  // Accept unique_ptr for derived classes

public:
    static Board * getBoard();
    std::vector<std::unique_ptr<Square>>& getSquares();

    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif // MONOPOLY_BOARD_HPP
