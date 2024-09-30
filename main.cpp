#include <SFML/Graphics.hpp>
#include "GameFlow.hpp"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Monopoly Game");
    window.clear(sf::Color::White);  // Clear with a white background
    // Specify the number of players
    int numPlayers = 2;
    bool over=false;
    // Create the game flow
    GameFlow gameFlow(numPlayers, window);
    while(!over) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            // Update the game state
            gameFlow.updateGUI();
            window.draw(gameFlow.gameMessageText);  // Draw the game message
            // Play a turn
            gameFlow.playTurn(gameFlow.getPlayers()[gameFlow.getTurn()]);
            // Display the window contents
            window.display();
            over=gameFlow.isGameOver();
        }
    }
    return 0;
}
