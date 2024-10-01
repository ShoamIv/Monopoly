#include "Board.hpp"
#include "Street.hpp"
#include "Infrastructure.hpp"

Board* Board::ptr = nullptr;

Board::Board() {
    initializeBoard();
}

Board::~Board() {
   board.clear();
}

Board* Board::getBoard() {
    if (ptr == nullptr) {
        ptr = new Board();
        ptr->initializeBoard(); // Call setupBoard to initialize the board
    }
    return ptr;
}

void Board::addSquare(std::unique_ptr<Square> square) {
    board.push_back(std::move(square));  // Move unique_ptr into the vector
}

void Board::initializeBoard() { // Renamed initializeBoard to setupBoard
    // Top Row
    addSquare(std::make_unique<SpecialSquare>("Go"));
    addSquare(std::make_unique<Street>("Neve-Ofer", "Beer-Sheva", 1, 50, 4));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("Ramot", "Beer-Sheva", 1, 70, 6));

    // Utilities
    addSquare(std::make_unique<SpecialSquare>("Tax"));
    addSquare(std::make_unique<Infrastructure>("Railroad", 200));

    // Kiryat Ata
    addSquare(std::make_unique<Street>("HaYarden", "Kiryat Ata", 2, 100, 8));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("HaShomer", "Kiryat Ata", 2, 120, 10));
    addSquare(std::make_unique<Street>("Givat-Tal", "Kiryat Ata", 2, 140, 12));

    // Jail
    addSquare(std::make_unique<SpecialSquare>("Jail"));

    // Ariel
    addSquare(std::make_unique<Street>("Moriya", "Ariel", 3, 160, 14));
    addSquare(std::make_unique<Infrastructure>("Electric Company", 150));
    addSquare(std::make_unique<Street>("Ramat Hagolan", "Ariel", 3, 180, 16));
    addSquare(std::make_unique<Street>("Neve Shannan", "Ariel", 3, 200, 18));

    addSquare(std::make_unique<Infrastructure>("Railroad", 200));

    // Orange Properties - Netanya
    addSquare(std::make_unique<Street>("Herzl", "Netanya", 4, 200, 18));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("Gordon", "Netanya", 4, 220, 20));
    addSquare(std::make_unique<Street>("Keren Hayesod", "Netanya", 4, 240, 22));

    // Free parking
    addSquare(std::make_unique<SpecialSquare>("Free Parking"));

    // Red Properties - Haifa
    addSquare(std::make_unique<Street>("HaNevi'im", "Haifa", 5, 260, 24));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("HaZohar ", "Haifa", 5, 280, 26));
    addSquare(std::make_unique<Street>("HaPalmach ", "Haifa", 5, 300, 28));

    // Railroad
    addSquare(std::make_unique<Infrastructure>("Railroad", 200));

    // Yellow Properties - Jerusalem
    addSquare(std::make_unique<Street>("Ben Yehuda", "Jerusalem", 6, 320, 30));
    addSquare(std::make_unique<Street>("Jaffa Street", "Jerusalem", 6, 340, 32));
    addSquare(std::make_unique<Infrastructure>("Water Company", 150));
    addSquare(std::make_unique<Street>("King George", "Jerusalem", 6, 360, 34));

    // Jail
    addSquare(std::make_unique<SpecialSquare>("GotoJail"));

    // Green Properties - Tel Aviv
    addSquare(std::make_unique<Street>("Dizengoff ", "Tel Aviv", 7, 400, 36));
    addSquare(std::make_unique<Street>("Rothschild", "Tel Aviv", 7, 420, 38));
    addSquare(std::make_unique<SpecialSquare>("Chance"));
    addSquare(std::make_unique<Street>("Hayarkon ", "Tel Aviv", 7, 440, 40));

    // Railroad & Chance
    addSquare(std::make_unique<Infrastructure>("Railroad", 200));
    addSquare(std::make_unique<SpecialSquare>("Chance"));

    // Blue Properties - Savion
    addSquare(std::make_unique<Street>("Havazelet ", "Savion", 8, 500, 50));
    addSquare(std::make_unique<SpecialSquare>("Tax"));
    addSquare(std::make_unique<Street>("Ariel Sharon ", "Savion", 8, 600, 60));

}

std::vector<std::unique_ptr<Square>>& Board::getSquares() {
    return board;
}

void Board::Draw(sf::RenderWindow &window) {
    // Draw the title
    drawTitle(window);
    // Define section names and their positions based on your cities
    std::vector<std::pair<std::string, sf::Vector2f>> sections = {
            {"Beer-Sheva", {630, 700}},   // Above Beer-Sheva properties
            {"Kiryat Ata", {220, 700}},  // Above Kiryat Ata properties
            {"Ariel", {130, 600}},        // Above Ariel properties
            {"Netanya", {130, 200}},      // Above Netanya properties
            {"Haifa", {220, 100}},       // Above Haifa properties
            {"Jerusalem", {600, 100}},   // Above Jerusalem properties
            {"Tel Aviv", {680, 200}},    // Above Tel Aviv properties
            {"Savion", {680, 600}}        // Above Savion properties
    };

    // Draw section names
    for (const auto& section : sections) {
        drawSectionName(section.first, section.second.x, section.second.y, window);
    }
    // Iterate over the squares and create graphical representation
    for (int i = 0; i < board.size(); ++i) {
        std::string name = board[i]->getName(); // Assuming you have a method to get the name
        sf::Color color = getSquareColor(board[i]);
        DrawSquare(i, name, color, window);
        board.at(i)->setPosition(graphicalSquares.at(i).first.getPosition());
    }
}

void Board::drawTitle(sf::RenderWindow &window) {

        sf::Font font;
        // Load the font for the title text
        if (!font.loadFromFile("Lato-BlackItalic.ttf")) { // Make sure the font file exists in your working directory
            throw std::runtime_error("Failed to load font");
        }

        sf::Text title; // Create a text object for the title
        title.setFont(font); // Set the font
        title.setString("Monopoly"); // Set the title text
        title.setCharacterSize(50); // Set a large text size
        title.setFillColor(sf::Color::Black); // Set the text color
        title.setStyle(sf::Text::Bold); // Make the text bold

        // Center the text on the board
        sf::FloatRect textRect = title.getLocalBounds(); // Get the bounds of the text
        title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Set origin to the center
        title.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 - 50); // Position the title at the center-top of the board
        // Draw the title text on the window
        window.draw(title);

    }

void Board::DrawSquare(int i, const std::string &name, sf::Color color, sf::RenderWindow &window) {

    // Create a rectangle shape for the square
    sf::RectangleShape squareShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    squareShape.setFillColor(color); // Set the color of the square
    // Load font for the square text
    sf::Font font;
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) { // Make sure the font file exists in your working directory
        throw std::runtime_error("Failed to load font");
    }
    // Create a text object for the square name
    sf::Text squareText;
    squareText.setFont(font);
    squareText.setString(name);
    squareText.setCharacterSize(11); // Set the character size for the text
    squareText.setFillColor(sf::Color::Black); // Set the text color to black

    // Position the square based on its index (i)
    if (i < 11) { // Top row
        squareShape.setPosition(BOARD_WIDTH - (i + 1) * SQUARE_SIZE + 3, BOARD_HEIGHT - SQUARE_SIZE);
    } else if (i < 20) { // Right column
        squareShape.setPosition(0, BOARD_HEIGHT - (i - 9) * SQUARE_SIZE);
    } else if (i < 31) { // Bottom row
        squareShape.setPosition((i - 20) * SQUARE_SIZE, 0);
    } else { // Left column
        squareShape.setPosition(BOARD_WIDTH - SQUARE_SIZE + 3, (i - 30) * SQUARE_SIZE - 2);
    }

    // Position the text at the center of the square
    sf::FloatRect textRect = squareText.getLocalBounds();
    squareText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    squareText.setPosition(squareShape.getPosition().x + SQUARE_SIZE / 2, squareShape.getPosition().y + SQUARE_SIZE / 2);
    // Draw the square and the text on the window
    window.draw(squareShape);  // Draw the rectangle shape
    window.draw(squareText); // Draw the text on the square
    // Optional: Store the square and its text for later use (if needed)
    graphicalSquares.emplace_back(squareShape, squareText);
}

sf::Color Board::getSquareColor(const std::unique_ptr<Square>& square) const {
    const auto* street = dynamic_cast<const Street*>(square.get());

    if (street) {
        // Check by city name
        const std::string& city = street->getCity();
        if (city == "Beer-Sheva") return {255, 200, 200};
        if (city == "Kiryat Ata") return {255, 165, 0}; // Orange
        if (city == "Ariel") return {255, 0, 0}; // Red
        if (city == "Netanya") return {255, 255, 0}; // Yellow
        if (city == "Haifa") return {0, 255, 0}; // Green
        if (city == "Jerusalem") return {0, 0, 255}; // Blue
        if (city == "Tel Aviv") return {75, 0, 130}; // Indigo
        if (city == "Savion") return {238, 130, 238}; // Violet
    }

    // Check for special squares
    const std::string& name = square->getName();
    if (name == "Go") return {255, 223, 186}; // Light Orange for "Go"
    if (name == "Chance") return {173, 216, 230}; // Light Blue for "Chance"
    if (name == "Tax") return {189, 183, 107}; // Khaki for "Tax"
    if (name == "Jail") return {128, 128, 128}; // Gray for "Jail"
    if (name == "Free Parking") return {255, 255, 255}; // White for "Free Parking"
    if (name == "Go to Jail") return {255, 105, 97}; // Salmon for "Go to Jail"
    if (name == "Railroad") return {169, 169, 169}; // Dark Gray for "Railroad"
    if (name == "Electric Company") return {255, 255, 0}; // Yellow for Electric Company
    if (name == "Water Company") return {0, 191, 255}; // Deep Sky Blue for Water Company

    return sf::Color::White; // Default color if not found
}

void Board::drawSectionName(const std::string &name, float x, float y, sf::RenderWindow &window) {
    sf::Font font;
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text sectionText;
    sectionText.setFont(font);
    sectionText.setString(name);
    sectionText.setCharacterSize(20); // Set a larger character size for section names
    sectionText.setFillColor(sf::Color::Black); // Set text color
    sectionText.setStyle(sf::Text::Bold); // Make text bold

    // Center the text above the squares
    sf::FloatRect textRect = sectionText.getLocalBounds();
    sectionText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    sectionText.setPosition(x, y); // Position the text

    // Draw the section name on the window
    window.draw(sectionText);
}

Button Board::getButton() {
    return this->button;
}
int Board::getSquareIndex(const std::string &location) const {
    for (size_t i = 0; i < board.size(); ++i) {
        if (board[i]->getName() == location) { // Assuming Square has a method getName()
            return static_cast<int>(i); // Return the index of the matching square
        }
    }
    return -1; // Return -1 if the location is not found
}