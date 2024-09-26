
#include <memory>
#include "GameFlow.hpp"
#include "Street.hpp"

GameFlow::GameFlow(int numPlayers) : board(Board::getBoard()), currentPlayerIndex(0){
    for(int i=0; i<numPlayers; i++){
        std::string name;
        std::string color;
        std::cout<< "Please enter your name and your desired color.";
        std::cin>>name>>color;
        players.emplace_back(name,color);
    }
    startGame();
}

void GameFlow::startGame() {
    for(Player player : players){
        player.setCash(1500);
    }
}

void GameFlow::playTurn(Player &player) {
    Player& currentPlayer = players[currentPlayerIndex];
    movePlayer(currentPlayer,0);
    handleSquare(currentPlayer);
    // Move to the next player
    currentPlayerIndex = (int)((currentPlayerIndex + 1) % players.size());
}

void GameFlow::movePlayer(Player &player,int repeat)
{
    if(repeat==3){
        // go to jail.
        //playerLocations[player.get_id()-1]=20;
    }
    else {
        auto [roll1, roll2] = dice.roll();  // Roll the dice
        int steps = roll1 + roll2;          // Sum of the dice rolls
      //  int currentPosition = playerLocations[player.get_id() - 1];
      //  int newPosition = (currentPosition + steps) % 40; // Monopoly board size is 40.
       // playerLocations[player.get_id() - 1] = newPosition;
        if (roll1 == roll2){
            handleSquare(player);
            movePlayer(player,++repeat);
        }
    }
}

void GameFlow::handleSquare(Player &player) {
   // board->getSquares().at(playerLocations.at(currentPlayerIndex))->action(player);
}
bool GameFlow::checkBankruptcy(Player &player) {

    return false;
}
