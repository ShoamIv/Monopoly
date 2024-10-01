
#include "GameFlow.hpp"
#include "Street.hpp"
//   for(int i=0; i<numPlayers; i++){
// std::string name;
// std::cout<< "Please enter your name. \n";
// std::getline(std::cin, name); // Use getline to read names with spaces
//playerLocations[i] = 0;

GameFlow::GameFlow(int numPlayers, sf::RenderWindow& window)
        : board(Board::getBoard()), window(window), currentPlayerIndex(0),
          throwDiceButton(200, 50, "Throw Dice", font, sf::Color::Green, [this]() {
              std::cout << "Dice rolled!" << std::endl;
          }) {
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return; // Early exit if font loading fails
    }
        std::string name1="Jon";
        std::string name2="Ron";
       players.emplace_back(name1,PlayerColor::Blue,0,window);
       players.emplace_back(name2,PlayerColor::Green,1,window);
    // Initialize the buttons
    ButtonInit();
    gameMessageText.setFont(font);
    gameMessageText.setCharacterSize(24);
    gameMessageText.setFillColor(sf::Color::Black);
    gameMessageText.setPosition(100, 100); // Set its position on the screen
    board->Draw(window);     // Draw the board
    // Start the game (assuming this handles additional game setup)
    startGame();
   // }
}

void GameFlow::startGame() {
    for(Player &player : players){
        player.setCash(1500);
    }
}

void GameFlow::playTurn(Player &player) {
    bool turnActive = true;  // Track if the turn is still active
    int doubleRolls = 0;     // Track the number of doubles rolled in the turn

    while (turnActive) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window closing
            if (event.type == sf::Event::Closed) {
                window.close();
                turnActive = false;
                return;
            }

            // Handle mouse click event
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Check if the "Throw Dice" button is clicked
                if (throwDiceButton.isHovered(window)) {
                    auto [roll1, roll2] = dice.roll(); // Roll the dice
                    std::string moveMessage = player.getName() + " rolled the dice: " + std::to_string(roll1) + ", " + std::to_string(roll2) + ".";
                    std::cout << moveMessage << std::endl;
                    updateMessage(moveMessage);
                    window.display();
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    // If the player rolled a double
                    if (roll1 == roll2) {
                        doubleRolls++;
                        if (doubleRolls == 3) {
                            // Player goes to jail after 3 consecutive doubles
                            player.resetRepeatDouble();
                            displayMessage(player.getName() + " has rolled 3 doubles in a row. Time to go to jail!");
                            player.MoveTo("Jail", window);
                            playerLocations.at(player.getID()) = 10;
                            handleSquare(player);  // Handle landing on jail
                            turnActive = false;    // End the player's turn
                        } else {
                            // Move player and let them roll again
                            movePlayer(player, roll1 + roll2);
                            handleSquare(player);
                            updateMessage(player.getName() + " gets an extra turn for rolling a double!");
                        }
                    } else {
                        // Normal turn, move player and end the turn
                        doubleRolls = 0;  // Reset double rolls count
                        movePlayer(player, roll1 + roll2);
                        handleSquare(player);
                        turnActive = false;  // End the turn
                    }
                }
                // Check if the "View Estates" button is clicked
                if (viewEstatesButton.isHovered(window)) {
                    std::cout << "View Estates button clicked!" << std::endl;
                    displayEstates(); // Call function to display player estates
                }
            }
        }

        // Clear the window and render the GUI and buttons
        window.clear(sf::Color::White);  // Clear the window
        updateGUI();                     // Update and render the game GUI
        // Render the "Throw Dice" and "View Estates" buttons
        throwDiceButton.render(window);
        viewEstatesButton.render(window);
        // Ensure the window is updated and displayed
        window.display();
    }
    // Move to the next player after the turn ends
    checkBankruptcy();
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void GameFlow::movePlayer(Player &player, int steps) {
    int currentPosition = playerLocations[player.getID()]; // Get current position
    int newPosition = (currentPosition + steps) % 40;      // Monopoly board size is 40
    playerLocations[player.getID()] = newPosition;         // Update position
    player.Move(steps, window);                            // Move the player visually
    window.display();
}

void GameFlow::handleSquare(Player &player) {
    // Retrieve the vector of squares from the board
    const std::vector<std::unique_ptr<Square>>& squares = board->getSquares();
    // Get the player's current location
    int playerLocation = playerLocations.at(player.getID());
    // Retrieve the current square the player is on
    Square* currentSquare = squares.at(playerLocation).get();
    if(auto* streetSquare = dynamic_cast<Street*>(currentSquare)){
        streetSquare->isUpgradable(squares);
    }
    // Perform the action for the square
    currentSquare->action(player, window);
    if (player.getChanceDraw()) {
        // Draw a chance card and handle its effect
        ChanceCard::DrawCard(player, this->players, this->window);
        player.setChanceDraw(false);
        // Update the player's location after drawing the chance card (if applicable)
        playerLocations[player.getID()] = player.getPosition();
    }
}

bool GameFlow::checkBankruptcy() {
    for(const Player&  player : this->players){
            if(player.getBankruptcy()){
                removePlayer(player.getID());
            }
    }
    return false;
}

void GameFlow::updateGUI() {
    window.clear(sf::Color::White);  // Clear the window
    // Draw the board and all players
    board->Draw(window);
    viewEstatesButton.render(window);
    // Draw each player based on their updated locations
      for(Player player : players){
        player.DrawInfo(window); // Draw the player's token at the correct position
   }
}

std::vector<Player> &GameFlow::getPlayers() {
    return this->players;
}

int GameFlow::getTurn() const {
    return this->currentPlayerIndex;
}

bool GameFlow:: isGameOver() {
    for(const Player& p : players){
        if(p.getCash()>=4000)
        players.clear();
            return true;
    }
    if(players.size()==1){
            players.clear();
        return true;
    }
    return false;
}

void GameFlow::displayMessage(const std::string &message) {

    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
        std::cerr << "Error: Could not load font Lato-BlackItalic.ttf!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(24);  // Text size
    text.setFillColor(sf::Color::Black);  // Text color

    // Center the text on the screen
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    // Clear the window before displaying the message
    window.clear(sf::Color::White);
    window.draw(text);
    window.display();
}

void GameFlow::updateMessage(const std::string &message) {
    // Create message text
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(16);
    messageText.setFillColor(sf::Color::Black);
    messageText.setString(message);
    // Center the text
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT - 200); // Position at the bottom center of the window
    // Draw the message
    window.draw(messageText);

}

void GameFlow::removePlayer(int playerID) {
    // Remove player from the list of active players
    players.erase(std::remove_if(players.begin(), players.end(),
                                 [playerID](const Player& player) {
                                     return player.getID() == playerID;
                                 }), players.end());
    // Remove player's location
    playerLocations.erase(playerID);
    updateMessage("Player " + std::to_string(playerID) + " is bankrupt and has been removed from the game.");
}

void GameFlow::ButtonInit() {
    throwDiceButton = Button(120, 40, "Roll Dice", font, sf::Color::Yellow, []() {
        std::cout << "Throw Dice button clicked!" << std::endl;
    });
    yesButton = Button(60, 40, "Yes", font, sf::Color::Green, []() {
        std::cout << "Yes button clicked!" << std::endl;
    });
    noButton = Button(60, 40, "No", font, sf::Color::Red, []() {
        std::cout << "No button clicked!" << std::endl;
    });
    viewEstatesButton = Button(140, 40, "View Estates", font, sf::Color::Cyan, [this]() {
        std::cout << "View Estates button clicked!" << std::endl;
    });
    throwDiceButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 10);
    yesButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2+100);
    noButton.setPosition(BOARD_WIDTH / 2-50, BOARD_HEIGHT / 2 +100);
    viewEstatesButton.setPosition(BOARD_WIDTH / 2-50, BOARD_HEIGHT / 2 -200);
}

void GameFlow::displayEstates() {
    for (Player player : players) {
        std::string estates = player.getName() + "'s Estates:\n";
        // loop through player's owned properties and append to the estates string
        for (const auto &property: player.getEstates()) {
            estates += property->getName() + "\n";
        }
        // If player has no estates, display a message indicating that
        if (player.getEstates().empty()) {
            estates = player.getName() + " owns no properties.";
        }
        // Use the displayMessage method to show the list of estates
        displayMessage(estates);
        // Pause to allow viewing each player's estates
        sf::sleep(sf::seconds(3));
    }
}
