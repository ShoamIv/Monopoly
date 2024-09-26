#include "Board.hpp"
#include "Street.hpp"
#include "Infrastructure.hpp"

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
    addSquare(std::make_unique<Street>("Neve-Ofer", "Beer-Sheva", 1, 50, 4));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("Ramot", "Beer-Sheva", 1, 70, 6));

    //Utilities
    addSquare(std::make_unique<SpecialSquare>("Tax"));
    addSquare(std::make_unique<Infrastructure>("Railroad", 200));

    //Kiryat Ata
    addSquare(std::make_unique<Street>("HaYarden ", "Kiryat Ata", 2, 100, 8)); // HaYarden Street
    addSquare(std::make_unique<SpecialSquare>("Chance"));              // Chance Tile
    addSquare(std::make_unique<Street>("HaShomer ", "Kiryat Ata", 2, 120, 10)); // HaShomer Street
    addSquare(std::make_unique<Street>("Givat-Tal ", "Kiryat Ata", 2, 140, 12)); // HaGefen Street

    //jail
    addSquare(std::make_unique<SpecialSquare>("Go to Jail"));          // Go to Jail Tile

    //Ariel
    addSquare(std::make_unique<Street>("Moriya", "Ariel", 3, 160, 14));       // Moriya Street
    addSquare(std::make_unique<Infrastructure>("Electric Company", 150));
    addSquare(std::make_unique<Street>("Ramat Hagolan", "Ariel", 3, 180, 16)); // Ramat Hagolan Street
    addSquare(std::make_unique<Street>("Neve Shannan", "Ariel", 3, 200, 18));  // Neve Shannan Street

    addSquare(std::make_unique<Infrastructure>("Railroad", 200));

    // Orange Properties - Netanya
    addSquare(std::make_unique<Street>("Herzl", "Netanya", 4, 200, 18)); // Herzl Street
    addSquare(std::make_unique<SpecialSquare>("Chance"));              // Chance Tile
    addSquare(std::make_unique<Street>("Gordon", "Netanya", 4, 220, 20)); // Gordon Street
    addSquare(std::make_unique<Street>("Keren Hayesod", "Netanya", 4, 240, 22)); // Keren Hayesod Street

    //free parking
    addSquare(std::make_unique<SpecialSquare>("Free Parking"));         // Free Parking Tile

    // Red Properties - Haifa
    addSquare(std::make_unique<Street>("HaNevi'im Street", "Haifa", 5, 260, 24)); // HaNevi'im Street
    addSquare(std::make_unique<SpecialSquare>("Chance"));              // Chance Tile
    addSquare(std::make_unique<Street>("HaZohar Street", "Haifa", 5, 280, 26)); // HaZohar Street
    addSquare(std::make_unique<Street>("HaPalmach Street", "Haifa", 5, 300, 28)); // HaPalmach Street

    // railroad
    addSquare(std::make_unique<Infrastructure>("Railroad", 200));

// Yellow Properties - Jerusalem
    addSquare(std::make_unique<Street>("Ben Yehuda Street", "Jerusalem", 6, 320, 30)); // Ben Yehuda Street
    addSquare(std::make_unique<Street>("Jaffa Street", "Jerusalem", 6, 340, 32)); // Jaffa Street
    addSquare(std::make_unique<Infrastructure>("Water Company", 150));
    addSquare(std::make_unique<Street>("King George Street", "Jerusalem", 6, 360, 34)); // King George Street

    //jail
    addSquare(std::make_unique<SpecialSquare>("Go to Jail"));          // Go to Jail Tile

// Green Properties - Tel Aviv
    addSquare(std::make_unique<Street>("Dizengoff Street", "Tel Aviv", 7, 400, 36)); // Dizengoff Street
    addSquare(std::make_unique<Street>("Rothschild Boulevard", "Tel Aviv", 7, 420, 38)); // Rothschild Boulevard
    addSquare(std::make_unique<SpecialSquare>("Chance"));              // Chance Tile
    addSquare(std::make_unique<Street>("Hayarkon Street", "Tel Aviv", 7, 440, 40)); // Hayarkon Street

    //railroad &chance
    addSquare(std::make_unique<Infrastructure>("Railroad", 200));
    addSquare(std::make_unique<SpecialSquare>("Chance"));              // Chance Tile

// Blue Properties - Savion
    addSquare(std::make_unique<Street>("Havazelet Street", "Savion", 8, 500, 50)); // Havazelet Street
    addSquare(std::make_unique<SpecialSquare>("Tax"));
    addSquare(std::make_unique<Street>("Ariel Sharon Street", "Savion", 8, 600, 60)); // Ariel Sharon Street
}

std::vector<std::unique_ptr<Square>>& Board::getSquares() {
    return board;
}
