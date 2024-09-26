
#include <utility>
#include <unordered_map>
#include "SpecialSquare.hpp"

SpecialSquare::SpecialSquare(std::string name) : Square(std::move(name)) {}

// Map string names to SquareType enumeration values
SpecialSquare::SquareType SpecialSquare::getSquareType() const {
    static const std::unordered_map<std::string, SquareType> nameToType = {
            {"GoToJail",    SquareType::GoToJail},
            {"Chance",      SquareType::Chance},
            {"Tax",         SquareType::Tax},
            {"FreeParking", SquareType::FreeParking}
    };
    auto it = nameToType.find(name);
    if (it != nameToType.end()) {
        return it->second;
    }
    return SquareType::Unknown;
}

void SpecialSquare::action(Player & player) {
    switch (getSquareType()) {
        case SquareType::GoToJail:
            GotoJail(player);
            break;
        case SquareType::Chance:
            Chance(player);
            break;
        case SquareType::Tax:
            Tax(player);
            break;
        case SquareType::FreeParking:
            FreeParking(player);
            break;
        default:
            std::cout << "Unknown special square type!" << std::endl;
            break;
    }
}

void SpecialSquare::GotoJail(Player & player) {
    Dice dice;
    std::cout << "You've landed on the Jail!" << std::endl;
    // Option 1: Send player to jail
    std::cout << "You are now in jail. You need to pay 50 to get out or roll doubles." << std::endl;
    std::cout << "if you wish to pay 50 please insert P, to choose Roll dices Please insert R, if you prefer to wait this turn insert any other character.\n";
    char i;
    std::cin >> i;
    if(i=='P') {
        int bailAmount = 50; // Example bail amount
        player.setCash(-50);
        // Inform the player about their current balance after paying bail
        std::cout << "You have paid " << bailAmount << " for bail." << std::endl;
        std::cout << "Your current balance is " << player.getCash() << "." << std::endl;
        player.setJail(-(player.getJail()));
        return;
    }
    else if(i=='R'){
        auto [roll1, roll2] = dice.roll();  // Roll the dice
        if(roll1==roll2){
            std::cout << "Congratulations, you free! \n";
            player.setJail(-(player.getJail()));
        }
    }
    if(player.getJail()>0) {        //for catch exceptions:
        player.setJail(-1);
        std::cout << "You have left " << player.getJail() << " for bail." << std::endl;
    }
}

void SpecialSquare::Tax(Player & player) {
    std::cout << "You have landed on a Tax Debt!" << std::endl;
    player.setCash(-100);
    // Display message after tax is deducted
    std::cout << "Tax of "<< 100 << " has been deducted from your account." << std::endl;
    std::cout << "Your current balance is " << player.getCash() << "." << std::endl;
}

void SpecialSquare::FreeParking(Player & player) {
    std::cout << player.getName() <<" landed on a Free Parking spot!" << std::endl;
    std::cout <<   "enjoy your break mate!\n";
}

void SpecialSquare::Chance(Player & player) {
    std::cout << player.getName() << " landed on the Chance spot!" << std::endl;
}

SpecialSquare::~SpecialSquare() = default;