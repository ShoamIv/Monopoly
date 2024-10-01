#include <SFML/Graphics.hpp>
#include "GameFlow.hpp"

int main() {
    // Create a window
sf::RenderWindow window(sf::VideoMode(880, 800), "Monopoly Game");
sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 800.f));
window.setView(view);

    window.clear(sf::Color::White);  // Clear with a white background
  std::cout << "Window size: " << window.getSize().x << "x" << window.getSize().y << std::endl;
sf::View currentView = window.getView();
std::cout << "View size: " << currentView.getSize().x << "x" << currentView.getSize().y << std::endl;

    // Specify the number of players
    int numPlayers = 2;
    bool over=false;
    // Create the game flow
    GameFlow gameFlow(numPlayers, window);
  
        while (window.isOpen() && !over) {
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
            window.display()	;
            over=gameFlow.isGameOver();
    }
    return 0;
}
