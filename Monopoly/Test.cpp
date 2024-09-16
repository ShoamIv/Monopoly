#include <sstream>
#include "doctest.h"
#include "GameFlow.h++"
#include "Street.h++"
#include "Board.h++"
#include "Infrastructure.h++"

TEST_CASE("Creation of the Board") {
    Board * board = Board::getBoard();
    CHECK((board != nullptr));  // Ensure the board singleton is created
}

TEST_CASE("Check if Board is Singleton") {
    Board * board1 = Board::getBoard();
    Board * board2 = Board::getBoard();
    CHECK((board1 == board2));  // Check both instances are the same (singleton)
}

TEST_CASE("Board Initialization with Squares") {
    Board * board = Board::getBoard();
    const auto& squares = board->getSquares();

    // Check if the board was initialized with the correct number of squares
    CHECK((!squares.empty()));  // Ensure squares are initialized

    // Verify some squares (change the indices if needed, based on your actual board setup)
    CHECK(squares[0]->getName() == "Go");  // First square is "Go"
    CHECK(squares[1]->getName() == "Neve-Ofer");  // Second square is a street
    CHECK(squares[2]->getName() == "Chance");  // Third square is a "Chance"
}

TEST_CASE("Check Specific Squares in Board") {
    Board * board = Board::getBoard();
    const auto& squares = board->getSquares();

    // Check specific squares for their type
    CHECK((dynamic_cast<SpecialSquare*>(squares[0].get()) != nullptr));  // "Go" is a SpecialSquare
    CHECK((dynamic_cast<Street*>(squares[1].get()) != nullptr));  // "Neve-Ofer" is a Street
    CHECK((dynamic_cast<SpecialSquare*>(squares[2].get()) != nullptr));  // "Chance" is a SpecialSquare
    CHECK((dynamic_cast<Infrastructure*>(squares[5].get()) != nullptr));  // "Railroad" is an Infrastructure
}



