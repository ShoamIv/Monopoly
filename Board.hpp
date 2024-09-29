#ifndef MONOPOLY_BOARD_HPP
#define MONOPOLY_BOARD_HPP
#include "Button.hpp"
#include <vector>
#include <memory>
#include "Estate.hpp"
#include "Button.hpp"
#include "SpecialSquare.hpp"

class Board {
    Board();
    static Board * ptr;
    std::vector<std::unique_ptr<Square>> board;
    void initializeBoard();
    void addSquare(std::unique_ptr<Square> square);  // Accept unique_ptr for derived classes
    [[nodiscard]] sf::Color getSquareColor(const std::unique_ptr<Square>& square) const;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> graphicalSquares;  // Stores the graphical representation of squares
    void drawSectionName(const std::string &name, float x, float y, sf::RenderWindow &window);
    Button button;

public:
    void Draw(sf::RenderWindow &window);
    void drawTitle(sf::RenderWindow &window) ;
    void createGraphicalSquare(int i, const std::string &name, sf::Color color, sf::RenderWindow &window);
    static Board * getBoard();
    Button getButton();
    int getSquareIndex(const std::string &location) const;
        std::vector<std::unique_ptr<Square>>& getSquares();
    ~Board();
    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};

#endif // MONOPOLY_BOARD_HPP
