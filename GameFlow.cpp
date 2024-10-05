#include "GameFlow.hpp"
#include "Street.hpp"
/**
 * @class GameFlow
 * @brief Manages the overall flow of the Monopoly game, including player turns, dice rolls,
 *        player movement, handling square actions, and managing game state.
 *
 * This class is responsible for controlling the main aspects of the Monopoly game. It maintains
 * the state of the game board, the players, and their positions. The GameFlow class handles
 * player interactions such as rolling dice, moving to squares, upgrading properties, and checking
 * for game-over conditions like bankruptcy. It also manages the graphical user interface (GUI)
 * elements like buttons and messages displayed to the players.
 *
 * @details
 * Key responsibilities of GameFlow include:
 * - Managing turns and player actions.
 * - Updating and rendering the game board and player movements.
 * - Handling special actions such as rolling doubles and sending players to jail.
 * - Checking for game-ending conditions like bankruptcy or a player reaching a target amount of cash.
 * - Displaying player estates and other in-game messages to the screen.
 *
 */

GameFlow::GameFlow(sf::RenderWindow& window)
        : board(Board::getBoard()), window(window), currentPlayerIndex(0),
          throwDiceButton(200, 50, "Throw Dice", font, sf::Color::Green, []() {
              std::cout << "Dice rolled!" << std::endl;
          }) {

    // Load font
    if (!font.loadFromFile("Lato-BlackItalic.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return; // Early exit if font loading fails
    }
    // Initialize the buttons
    ButtonInit();
    // Draw the board
    board->Draw(window);
    // Ask for the valid number of players through the GUI
    int numPlayers = promptForPlayerCount();
    // Input for player names and colors
    promptForPlayerDetails(numPlayers);
    // Start the game
    startGame();
}

void GameFlow::startGame() {
    for(Player &player : players){
        player.setCash(1500);
    }
}

void GameFlow::playTurn(Player &player) {
    bool turnActive = true;  // Track if the turn is still active
    int doubleRolls = 0;     // Track the number of doubles rolled in the turn

    // Check if the player is in jail at the start of the turn
    if (player.getJail() > 0) {
        handleSquare(player);  // Handle jail-related logic
        return;  // End the turn after handling jail
    }

    while (turnActive) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Handle window closing
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            // Handle mouse click event
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Check if the "Throw Dice" button is clicked
                if (throwDiceButton.isHovered(window)) {
                    auto [roll1, roll2] = dice.roll(); // Roll the dice
                    // For testing, let's set a fixed roll
                    std::string moveMessage = player.getName() + " rolled the dice: " + std::to_string(roll1) + ", " +
                                              std::to_string(roll2) + ".";
                    std::cout << moveMessage << std::endl;
                    updateMessage(moveMessage);
                    window.display();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    // If the player rolled a double
                    if (roll1 == roll2) {
                        doubleRolls++;
                        if (doubleRolls == 3) {
                            // Player goes to jail after 3 consecutive doubles
                            doubleRolls = 0; // Reset double rolls
                            displayMessage(player.getName() + " has rolled 3 doubles in a row. Time to go to jail!");
                            player.MoveTo("Jail", window);
                            playerLocations.at(player.getID()) = 10;
                            handleSquare(player);  // Handle landing on jail
                            return; // End the player's turn
                        }
                        else {
                            // Move player and let them roll again
                            movePlayer(player, roll1 + roll2);
                            updateMessage(player.getName() + " gets an extra turn for rolling a double!");
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                            handleSquare(player);
                            // Check if the player is in jail after moving
                            if (player.getJail() > 0 || playerLocations.at(currentPlayerIndex) == 20) {
                                turnActive = false; // End the turn if the player ends up in jail
                                break; // Exit the loop
                            }
                        }
                    } else {
                        // Normal turn, move player and end the turn
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
        updateGUI();                     // Update and render the game GUI
        window.display();                // Ensure the window is updated and displayed
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
    // Render the "Throw Dice" and "View Estates" buttons
    viewEstatesButton.render(window);
    throwDiceButton.render(window);
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
    std::string winMessage;
    for (const Player &p: players) {
        if (p.getCash() >= 4000) {
            winMessage = p.getName() + " Has just Won the Game, Good Game!";
            displayMessage(winMessage);
            std::this_thread::sleep_for(std::chrono::seconds(4));
            return true;
        }
        if (players.size() == 1) {
            winMessage = players.at(0).getName() + " Has just Won the Game, Good Game!";
            displayMessage(winMessage);
            std::this_thread::sleep_for(std::chrono::seconds(4));
            return true;
        }
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
        if(player.getJailCard()>0){
            estates+= "posses " + std::to_string(player.getJailCard()) + " Get out of Jail Card\n";
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

// Function to convert user input to PlayerColor
PlayerColor GameFlow::getPlayerColorFromInput(const std::string& colorInput) {
    PlayerColor color;

    // Match input to PlayerColor
    if (colorInput == "red") color = PlayerColor::Red;
    else if (colorInput == "blue") color = PlayerColor::Blue;
    else if (colorInput == "green") color = PlayerColor::Green;
    else if (colorInput == "yellow") color = PlayerColor::Yellow;
    else if (colorInput == "orange") color = PlayerColor::Orange;
    else if (colorInput == "purple") color = PlayerColor::Purple;
    else if (colorInput == "brown") color = PlayerColor::Brown;
    else if (colorInput == "magenta") color = PlayerColor::Magenta;
    else {
        std::cerr << "Invalid color! Defaulting to Red." << std::endl;
        color = PlayerColor::Red;
    }

    // Check if the color has already been selected
    if (selectedColors.find(color) != selectedColors.end()) {
        std::cerr << "Color already selected! Assigning a new available color." << std::endl;
        // Automatically assign the first available color
        color = getFirstAvailableColor();
    }

    // Mark the color as selected
    selectedColors.insert(color);
    return color;
}

PlayerColor GameFlow::getFirstAvailableColor() {
    if (selectedColors.find(PlayerColor::Red) == selectedColors.end()) return PlayerColor::Red;
    if (selectedColors.find(PlayerColor::Blue) == selectedColors.end()) return PlayerColor::Blue;
    if (selectedColors.find(PlayerColor::Green) == selectedColors.end()) return PlayerColor::Green;
    if (selectedColors.find(PlayerColor::Yellow) == selectedColors.end()) return PlayerColor::Yellow;
    if (selectedColors.find(PlayerColor::Orange) == selectedColors.end()) return PlayerColor::Orange;
    if (selectedColors.find(PlayerColor::Purple) == selectedColors.end()) return PlayerColor::Purple;
    if (selectedColors.find(PlayerColor::Brown) == selectedColors.end()) return PlayerColor::Brown;
    if (selectedColors.find(PlayerColor::Magenta) == selectedColors.end()) return PlayerColor::Magenta;

    std::cerr << "No available colors!" << std::endl;
    return PlayerColor::Red; // Default color in case all are chosen (shouldn't happen if limited by number of players)
}

int GameFlow::promptForPlayerCount() {
    int numPlayers = 0;

    while (numPlayers < 2 || numPlayers > 8) {
        // Display the prompt in the GUI
        displayMessage("Please insert the number of players (between 2-8): ");

        // Capture user input through the GUI (the user types the number)
        std::string input = getUserInput();

        try {
            // Try to convert the input to an integer
            numPlayers = std::stoi(input);
        } catch (...) {
            // If input is invalid, show an error message
            updateMessage("Invalid input. Please enter a valid number between 2 and 8.");
        }
    }
    return numPlayers;
}

void GameFlow::promptForPlayerDetails(int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        // Prompt for player's name
        displayMessage("Player " + std::to_string(i + 1) + ", enter your name:");
        std::string playerName = getUserInput();

        // Prompt for player's color
        displayMessage(  playerName + ", choose a color (red, blue, green, yellow, \norange, Purple, brown, magenta):");
        std::string colorInput = getUserInput();
        // Convert the color input to the PlayerColor enum
        PlayerColor playerColor = getPlayerColorFromInput(colorInput);
        // Create the player
        players.emplace_back(playerName, playerColor, i, window);
        playerLocations[i] = 0;
    }
}

std::string GameFlow::getUserInput() {
    std::string userInput;
    sf::Event event{};

    while (window.waitEvent(event)) {  // Wait for events in a blocking loop
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !userInput.empty()) {
                // Handle backspace (removing last character)
                userInput.pop_back();
            } else if (event.text.unicode == '\r') {
                // Handle enter (submit input)
                break;
            } else if (event.text.unicode < 128) {
                // Only handle standard characters
                userInput += static_cast<char>(event.text.unicode);
            }

            // Update message in real-time (shows the typed input)
            updateMessage(userInput);
        }
    }

    return userInput;
}

GameFlow::~GameFlow() {
    // This destructor is called when GameFlow goes out of scope
    players.clear(); // Clear the players
}
