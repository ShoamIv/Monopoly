#ifndef MONOPOLY_BOARD_H
#define MONOPOLY_BOARD_H
#include <vector>
#include <memory>  // Include for std::unique_ptr
#include "Estate.h++"
#include "SpecialSquare.h++"

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

#endif // MONOPOLY_BOARD_H
