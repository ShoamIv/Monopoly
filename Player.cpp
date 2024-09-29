#include <utility>
#include "Player.hpp"
#include "Board.hpp"
static int playerCount=0;
std::map<PlayerColor, sf::Color> PlayersColor = {
        {PlayerColor::Red, sf::Color::Red},
        {PlayerColor::Blue, sf::Color::Blue},
        {PlayerColor::Green, sf::Color::Green},
        {PlayerColor::Yellow, sf::Color::Yellow},
        {PlayerColor::Orange, sf::Color(255, 165, 0)},  // Orange
        {PlayerColor::Purple, sf::Color(128, 0, 128)},  // Purple
        {PlayerColor::Brown, sf::Color(165, 42, 42)},    // Brown
        {PlayerColor::Magenta, sf::Color(255, 0, 255)}   // Magenta
};

Player::Player(std::string &name, PlayerColor color, int id, sf::RenderWindow& window)
        : name(name), color(color), id(id) {
    playerCount++;
    InitializePlayer(window);
}

void Player::setCash(int amount) {
    this->cash=cash+amount;
}

std::string Player::getName() {
    return this->name;
}

int Player::getCash() const {
    return this->cash;
}

void Player::setJail(int time) {
this->jail_time+=time;
}

int Player::getJail() const {
    return this->jail_time;
}

int Player::getRecentDice() const {
    return this->dice;
}

void Player::setRecentDice(int dice_) {
 this->dice=dice_;
}

void Player::CollectRent(Player &p,int rent) {
 this->cash+=rent;
 p.cash-=rent;
 std::cout<<p.getName()<< "Paid Rent at amount of:" << rent << "to: " <<this->getName()<<std::endl;
}

int Player::getRailRoad() const {
    return this->NumOfRailRoad;
}

void Player::IncreaseNumRailRoad() {
    this->NumOfRailRoad++;
}

void Player::AddCity(const std::string& city) {
 this->CityOwner.emplace_back(city);
}

bool Player::OwnCity(const std::string& City) {
    for(const std::string& city : CityOwner){
        if(City==city){
            return true;
        }
    }
    return false;
}

void Player::AddEstate(Estate *estate) {
    this->Estates.emplace_back(estate);
}

void Player::InitializePlayer(sf::RenderWindow &window) {

    PlayerInfoCircle.setRadius(R); // Set the radius for the player token
    // Set color from the PlayersColor map
    auto it = PlayersColor.find(color);
    if (it != PlayersColor.end()) {
        PlayerInfoCircle.setFillColor(it->second); // Set the color from the map
    } else {
        PlayerInfoCircle.setFillColor(sf::Color::Red); // Default to red if not found
        std::cerr << "Error: Player color not found, defaulting to red!" << std::endl;
    }
    // Set position for PlayerInfoCircle
    float x_ = BOARD_WIDTH - (SQUARE_SIZE / 1.5f);
    float y_ = BOARD_HEIGHT - (SQUARE_SIZE) + 12 * (id + 1) - 10;
    PlayerInfoCircle.setPosition(x_,y_);
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
            std::cerr << "Error: Could not load font Lato-BlackItalic.ttf!" << std::endl;
            return; // Return early if font loading fails
        }
    // Initialize the text for player name and money
    text.setFont(font); // Set the font
    text.setCharacterSize(16); // Text size
    text.setFillColor(PlayerInfoCircle.getFillColor()); // Text color same as token
    text.setString(name + ": $" + std::to_string(cash)); // Set the initial string
    // Update the player info (name and money) position
    float x=BOARD_WIDTH / 2 +50;
    float y= BOARD_HEIGHT / 2 +35 * (id + 1) ;
    text.setPosition(x,y);
    window.draw(PlayerInfoCircle);
    window.display();
}


int Player::getID() const {
    return this->id;
}
void Player::DrawInfo(sf::RenderWindow &window) {
    // Check if the PlayerInfoCircle is initialized correctly
    /*
    if (PlayerInfoCircle.getRadius() <= 0) {
        std::cerr << "Error: PlayerInfoCircle is not initialized!" << std::endl;
        return;
    }
    auto pos = PlayerInfoCircle.getPosition();
    if (pos.x < 0 || pos.y < 0) {
        std::cerr << "Error: PlayerInfoCircle position is invalid! Position: ("
                  << pos.x << ", " << pos.y << ")" << std::endl;
        return;
    }

// Check if color is set correctly
    auto fillColor = PlayerInfoCircle.getFillColor();
    if (fillColor.a == 0) { // Fully transparent
        std::cerr << "Error: PlayerInfoCircle color is not set properly!" << std::endl;
        return;
    }
     */
    window.draw(PlayerInfoCircle);
    text.setFont(font); // Set the font
    text.setCharacterSize(16); // Text size
    text.setFillColor(PlayerInfoCircle.getFillColor()); // Text color same as token
    text.setString(name + ": $" + std::to_string(cash)); // Set the initial string
    // Update the player info (name and money) position
    float x=BOARD_WIDTH / 2 +200;
    float y= BOARD_HEIGHT / 2 + 20 * (id + 1) ;
    text.setPosition(x,y);
    window.draw(text);
    // Optionally draw the ownership markers if applicable
  //  for (int i = 0; i < sizeMarkers; i++) {
 //       window.draw(ownershipMarkers[i]); // Draw the marker on the window
 //   }
}

    void Player::Move(int steps, sf::RenderWindow &window) {
    curr_position = (curr_position+steps)%40;
    // Set the token's position based on its index (i)
    if (curr_position < 10) {
        PlayerInfoCircle.setPosition(BOARD_WIDTH +10-(curr_position + 1) * SQUARE_SIZE+3, BOARD_HEIGHT +10- SQUARE_SIZE+5*(id+1));
    }
    else if (curr_position < 20) {
        PlayerInfoCircle.setPosition(20, BOARD_HEIGHT - (curr_position - 9) * SQUARE_SIZE+5*(id+1));
    }
    else if (curr_position < 30) {
        PlayerInfoCircle.setPosition((curr_position - 20) * SQUARE_SIZE+10, 5*(id+1));
    }
    else {
        PlayerInfoCircle.setPosition(BOARD_WIDTH - SQUARE_SIZE+3, (curr_position- 30) * SQUARE_SIZE+5*(id+1));;
    }
    window.draw(PlayerInfoCircle);
    window.display();
}


bool Player::getChanceDraw() const {
return DrawChance;
}

void Player::setChanceDraw(bool flag) {
this->DrawChance=flag;
}

void Player::MoveTo(const std::string& location, sf::RenderWindow &window) {
    Board * board=Board::getBoard();
    int newPosition = board->getSquareIndex(location); // Get the index of the target square
    if (newPosition != -1) { // Assuming -1 means the location was not found
        int steps = newPosition - curr_position; // Calculate steps to move
        // Handle wrapping around the board (if needed)
        if (steps < 0) {
            steps += 40; // Assuming there are 40 squares on the board
        }
        Move(steps,window); // Call the Move method with the calculated steps
        std::cout << getName() << " moves to " << location << "." << std::endl;
        curr_position=newPosition;
    } else {
        std::cout << "Invalid location: " << location << std::endl;
    }
}

void Player::IncreaseJailCard() {
    this->getOutFromJail++;
}

int Player::getJailCard() const {
    return this->getOutFromJail;
}

sf::CircleShape& Player::getCircle() {
    return this->PlayerInfoCircle;
}

int Player::getRepeatDouble() const {
     return repeatDouble;
}
void Player::increaseRepeatDouble() {
    repeatDouble++;
}
void Player::resetRepeatDouble() {
    repeatDouble=0;
}