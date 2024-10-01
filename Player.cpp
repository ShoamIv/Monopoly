#include <utility>
#include "Player.hpp"
#include "Board.hpp"
#include "Street.hpp"

static int playerCount=0;
std::map<PlayerColor, sf::Color> PlayersColor = {
        {PlayerColor::Red, sf::Color(139, 0, 0)},        // Dark Red (different from Ariel's Red)
        {PlayerColor::Blue, sf::Color(0, 191, 255)},     // Deep Sky Blue (different from Jerusalem's Blue)
        {PlayerColor::Green, sf::Color(34, 139, 34)},    // Forest Green (different from Haifa's Green)
        {PlayerColor::Yellow, sf::Color(255, 215, 0)},   // Gold (different from Netanya's Yellow)
        {PlayerColor::Orange, sf::Color(255, 140, 0)},   // Dark Orange (different from Kiryat Ata's Orange)
        {PlayerColor::Purple, sf::Color(128, 0, 128)},   // Purple (distinct from any city color)
        {PlayerColor::Brown, sf::Color(139, 69, 19)},    // Saddle Brown
        {PlayerColor::Magenta, sf::Color(255, 0, 255)}   // Magenta (distinct)

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

void Player::CollectRent(Player &p,int rent) {
 this->cash+=rent;
 p.cash-=rent;
}

int Player::getRailRoad() const {
    return this->NumOfRailRoad;
}

void Player::IncreaseNumRailRoad() {
    this->NumOfRailRoad++;
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
    // Draw the player's info circle
    window.draw(PlayerInfoCircle);
    // Set up the text for displaying player info (name and cash)
    text.setFont(font); // Set the font
    text.setCharacterSize(16); // Text size
    text.setFillColor(PlayerInfoCircle.getFillColor()); // Text color same as token
    text.setString(name + ": $" + std::to_string(cash)); // Set the initial string

    // Update the player info (name and money) position
    float x = BOARD_WIDTH / 2 + 200; // X position
    float y = BOARD_HEIGHT / 2 + 20 * (id + 1); // Y position
    text.setPosition(x, y);
    window.draw(text); // Draw player info
    // Now draw the player's estates
    for (const auto& estate : Estates) {
            // Check if the estate is a Street and draw street text, houses/hotel if it is
                estate->drawHousesAndHotel(window); // Draw houses and hotel for the street
    }
}

    void Player::Move(int steps, sf::RenderWindow &window) {
    int old_pos=curr_position;
    curr_position = (curr_position+steps)%40;
    // Set the token's position based on its index (i)
    if (curr_position < 11) {
        PlayerInfoCircle.setPosition(BOARD_WIDTH +10-(curr_position + 1) * SQUARE_SIZE+3, BOARD_HEIGHT +10- SQUARE_SIZE+5*(id+1));
    }
    else if (curr_position < 20) {
        PlayerInfoCircle.setPosition(20, BOARD_HEIGHT - (curr_position - 9) * SQUARE_SIZE+5*(id+1));
    }
    else if (curr_position < 31) {
        PlayerInfoCircle.setPosition((curr_position - 20) * SQUARE_SIZE+10, 5*(id+1));
    }
    else {
        PlayerInfoCircle.setPosition(BOARD_WIDTH - SQUARE_SIZE+3, (curr_position- 30) * SQUARE_SIZE+5*(id+1));;
    }
    if(old_pos>curr_position){
        this->cash+=200;
    }
    window.draw(PlayerInfoCircle);
    window.display();
}

void Player::MoveTo(const std::string& location, sf::RenderWindow &window) {

    int newPosition = getPositionIndex(location);
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


void Player::setBankruptcy() {
    this->Bankruptcy=true;
}

bool Player::getBankruptcy() const {
    return this->Bankruptcy;
}

void Player::CollectBankruptcy(Player & BrokePlayer) {
    this->setCash(BrokePlayer.getCash());
      for(Estate * estate : BrokePlayer.getEstates()){
          estate->set_owner(this);
      }
      NumOfRailRoad+=BrokePlayer.getRailRoad();
    getOutFromJail+=BrokePlayer.getOutFromJail;
}

std::vector<Estate *> Player::getEstates() {
    return this->Estates;
}

void Player::setJailCard(int num) {
    this->getOutFromJail+=num;
}

int Player::getPosition() const {
    return this->curr_position;
}

void Player::setChanceDraw(bool flag) {
    this->ChanceDraw=flag;
}

bool Player::getChanceDraw() const {
    return this->ChanceDraw;
}

void Player::resetRepeatDouble() {
    DoubleCount=0;
}

void Player::AddEstate(Estate &estate) {
    this->Estates.emplace_back(&estate);
}

const sf::Color& Player::getColor() {
    // Attempt to find the player color in the map
    auto it = PlayersColor.find(this->color); // 'color' should be of type PlayerColor
    if (it != PlayersColor.end()) {
        return it->second; // Return the corresponding sf::Color
    } else {
        // Handle error: color not found (this shouldn't normally happen)
        std::cerr << "Invalid player color: " << static_cast<int>(this->color) << std::endl;
        static sf::Color defaultColor = sf::Color::Black; // Return a static default color
        return defaultColor;
    }
}

int Player::getPositionIndex(const std::string& location) {
    Board * board=Board::getBoard();
    int newPosition = board->getSquareIndex(location);
    return newPosition;
}


