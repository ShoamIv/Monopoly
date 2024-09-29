
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
    throwDiceButton = Button(120, 40, "Roll Dice", font, sf::Color::Yellow, []() {
        std::cout << "Throw Dice button clicked!" << std::endl;
    });
    yesButton = Button(60, 40, "Yes", font, sf::Color::Green, []() {
        std::cout << "Yes button clicked!" << std::endl;
    });
    noButton = Button(60, 40, "No", font, sf::Color::Red, []() {
        std::cout << "No button clicked!" << std::endl;
    });
    gameMessageText.setFont(font);
    gameMessageText.setCharacterSize(24);
    gameMessageText.setFillColor(sf::Color::Black);
    gameMessageText.setPosition(100, 100); // Set its position on the screen
    throwDiceButton.setPosition(BOARD_WIDTH / 2 - 50, BOARD_HEIGHT / 2 + 10);
    yesButton.setPosition(BOARD_WIDTH / 2, BOARD_HEIGHT / 2+100);
    noButton.setPosition(BOARD_WIDTH / 2-50, BOARD_HEIGHT / 2 +100);
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
    // Event loop for the player's turn
    while (turnActive) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window closing
            if (event.type == sf::Event::Closed) {
                window.close();
                turnActive = false;
                break;
            }

            // Handle mouse click event
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Check if the "Throw Dice" button is clicked
                if (throwDiceButton.isHovered(window)) {
                    // Call the button's click action
                    throwDiceButton.handleClick(window);
                    movePlayer(player);  // Move player based on dice roll
                    handleSquare(player);   // Handle what happens after landing on the square
                    turnActive = false;     // End the turn after the move
                }
            }
        }
        // Render GUI and buttons
        window.clear(sf::Color::White);  // Clear the window
        updateGUI();                     // Update and render the game GUI
        throwDiceButton.render(window);  // Render the "Throw Dice" button
        window.display();                // Display the updated window
    }
    // Move to the next player after turn ends
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void GameFlow::movePlayer(Player &player) {
    if (player.getRepeatDouble() == 3) {
        player.resetRepeatDouble();
        displayMessage(player.getName() +" has Double 3 times in a row, Time to go to Jail!;");
        player.MoveTo("Jail", window);
        playerLocations.at(player.getID()) = 10;
        handleSquare(player);
    } else {
        auto [roll1, roll2] = dice.roll();  // Roll the dice
        int steps = roll1 + roll2;          // Sum of the dice rolls
        int currentPosition = playerLocations[player.getID()]; // Ensure player.getID() returns the correct index
        // Calculate the new position
        int newPosition = (currentPosition + steps) % 40;  // Monopoly board size is 40.
        // Update the player's position in the playerLocations array
        playerLocations[player.getID()] = newPosition;
        player.Move(steps,window);
        // Update the display message to show movement
        std::string moveMessage = player.getName() + " rolled the dice: " + std::to_string(roll1) + ", " + std::to_string(roll2) + ".";
        // Call to your update message function to display the move
        updateMessage(moveMessage);
        sf::sleep(sf::seconds(2));

// Update the player's position in the playerLocations array
        playerLocations[player.getID()] = newPosition;
        if (roll1 == roll2) {
            player.increaseRepeatDouble();
            handleSquare(player);
            playTurn(player);
        }
    }
}

void GameFlow::handleSquare(Player &player) {
    Square* currentSquare = board->getSquares().at(playerLocations.at(player.getID())).get();
    // Check if the square is an Estate
    auto* estate = dynamic_cast<Estate*>(currentSquare);
    if(estate){
        handleEstate(*estate,player);
    }else{
        currentSquare->action(player,window);
        if(player.getChanceDraw()){
            ChanceCard::DrawCard(player,this->players,this->window);
            player.setChanceDraw(false);
        }
    }
}

bool GameFlow::checkBankruptcy(Player &player) {

    return false;
}

void GameFlow::updateGUI() {
    window.clear(sf::Color::White);  // Clear the window
    // Draw the board and all players
    board->Draw(window);
    // Draw each player based on their updated locations
    for (const auto& [playerID, position] : playerLocations) {
        Player& player = players[playerID]; // Assuming you have a vector of Player objects
        player.DrawInfo(window); // Draw the player's token at the correct position
   }
}

std::vector<Player> &GameFlow::getPlayers() {
    return this->players;
}
;
sf::RenderWindow &GameFlow::getWindow() {
    return this->window;
}

int GameFlow::getTurn() const {
    return this->currentPlayerIndex;
}

bool GameFlow:: isGameOver() {
    for(const Player& p : players){
        if(p.getCash()>=4000)
            return true;
    }
    return false;
}


void GameFlow::handleEstate(Estate &estate, Player &player) {
    if (estate.get_owner() == nullptr) {
        // Display the purchase message
        yesButton.render(window);
        noButton.render(window);
        std::string mess="Would you like to buy " + estate.getName() + " Estate for $" + std::to_string(estate.get_cost()) + "?";
        updateMessage(mess);
        bool actionComplete = false;

        while (window.isOpen() && !actionComplete) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (yesButton.handleClick(window)) {
                    // Handle purchase
                    if (player.getCash() >= estate.get_cost()) {
                        estate.action(player,window);
                        //displayMessage(player.getName() + " bought " + estate.getName());
                    } else {
                       // displayMessage("Not enough money to buy." + estate.getName());
                    }
                    actionComplete = true;
                }

                if (noButton.handleClick(window)) {
                    // Player chose not to buy the property
                    displayMessage(player.getName() + " chose not to buy " + estate.getName());
                    actionComplete = true;
                }
            }
        }
    }
    else{
        estate.action(player,window);
    }
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
    // Wait a few seconds so the player has time to read the message
    sf::sleep(sf::seconds(3));
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
    window.display();

}
