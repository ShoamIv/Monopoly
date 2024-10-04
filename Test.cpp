#include <sstream>
#include "doctest.h"
#include "Street.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include "Infrastructure.hpp"
#include "SpecialSquare.hpp"
#include "ChanceCard.hpp"

sf::RenderWindow window(sf::VideoMode(800, 800), "Monopoly Game");
std::string Player1 = "Amatiza";
std::string Player2 = "Karako";
std::string Player3 = "Avi";
std::string Player4 = "Shuali";

TEST_CASE("Creation of Player") {

    Player player(Player1, PlayerColor::Red, 1, window);
    CHECK(player.getName() == Player1);  // Check the name
    CHECK((player.getCash() == 0));        // Initial cash should be 0
    CHECK((player.getJail() == 0));        // Initial jail time should be 0
}

TEST_CASE("Cash Management in Player") {
    Player player(Player1, PlayerColor::Red, 1,window);

    player.setCash(150);  // Set cash to 150
    CHECK((player.getCash() == 150));  // Check cash

    player.setCash(-50);  // Deduct cash
    CHECK((player.getCash() == 100));  // Cash should now be 100

    player.setCash(-100);  // Deduct cash more than current amount
    CHECK((player.getCash() == 0));    // Cash should not go below 0
}

TEST_CASE("Jail Time Management in Player") {
    Player player(Player1, PlayerColor::Red, 1,window);

    CHECK((player.getJail() == 0)); // Check initial jail time

    player.setJail(2);  // Add 2 turns in jail
    CHECK((player.getJail() == 2));

    player.setJail(-1);  // Remove 1 turn
    CHECK((player.getJail() == 1));  // Should now be 1

    player.setJail(-1);  // Set to negative jail time
    CHECK((player.getJail() == 0));  // Should be 0 now
}

TEST_CASE("Creation of the Board") {
    Board* board = Board::getBoard();
    CHECK((board != nullptr));  // Ensure the board singleton is created
}

TEST_CASE("Check if Board is Singleton") {
    Board* board1 = Board::getBoard();
    Board* board2 = Board::getBoard();
    CHECK((board1 == board2));  // Check both instances are the same (singleton)
}

TEST_CASE("Board Initialization with Squares") {
    Board* board = Board::getBoard();
    const auto& squares = board->getSquares();

    CHECK((!squares.empty()));  // Ensure squares are initialized
    CHECK(squares[0]->getName() == "Go");  // First square is "Go"
    CHECK(squares[1]->getName() == "Neve-Ofer");  // Second square is a street
    CHECK(squares[2]->getName() == "Chance");  // Third square is a "Chance"
}

TEST_CASE("Check Specific Squares in Board") {
    Board* board = Board::getBoard();
    const auto& squares = board->getSquares();

    CHECK((dynamic_cast<SpecialSquare*>(squares[0].get()) != nullptr));  // "Go" is a SpecialSquare
    CHECK((dynamic_cast<Street*>(squares[1].get()) != nullptr));        // "Neve-Ofer" is a Street
    CHECK((dynamic_cast<SpecialSquare*>(squares[2].get()) != nullptr));  // "Chance" is a SpecialSquare
    CHECK((dynamic_cast<Infrastructure*>(squares[5].get()) != nullptr));  // "Railroad" is an Infrastructure
}

TEST_CASE("Creation of SpecialSquare") {
    SpecialSquare square("GoToJail");
    CHECK((square.getSquareType() == SpecialSquare::SquareType::GoToJail));  // Ensure the square type is correct
}

TEST_CASE("Check Square Type Mapping") {
    SpecialSquare chanceSquare("Chance");
    SpecialSquare taxSquare("Tax");
    SpecialSquare freeParkingSquare("Free Parking");

    CHECK((chanceSquare.getSquareType() == SpecialSquare::SquareType::Chance));
    CHECK((taxSquare.getSquareType() == SpecialSquare::SquareType::Tax));
    CHECK((freeParkingSquare.getSquareType() == SpecialSquare::SquareType::FreeParking));
    CHECK((SpecialSquare("Unknown").getSquareType() == SpecialSquare::SquareType::Unknown)); // Unknown type
}

TEST_CASE("Action on GoToJail Square") {
    Player player(Player1, PlayerColor::Red, 1,window);
    player.setCash(100);  // Starting cash
    SpecialSquare goToJail("GoToJail");
    goToJail.action(player, window);
    CHECK((player.getJail() == 0));    // Ensure player is not in jail anymore
}

TEST_CASE("Tax Deduction Action") {
    Player player(Player1, PlayerColor::Red, 1,window);
    player.setCash(100);  // Starting cash
    SpecialSquare tax("Tax");
    tax.action(player,window);
    CHECK((player.getCash() == 0));  // Cash after tax deduction
}

TEST_CASE("Free Parking Action") {
    Player player(Player1, PlayerColor::Red, 1,window);
    player.setCash(300);  // Starting cash
    SpecialSquare freeParking("Free Parking");
    freeParking.action(player, window);
    CHECK((player.getCash() == 300));  // Cash should still be 300
}

TEST_CASE("Electric & Water Company Rent Calculation") {
    Player player1(Player1, PlayerColor::Red, 1, window);
    Player player2(Player2, PlayerColor::Blue, 1, window);
    player1.setCash(1500);
    player2.setCash(1500);
    Dice dice;
    auto [roll1, roll2] = dice.roll()= dice.roll();
    int dice_roll=roll1+roll2;
    player2.setRecentDice(dice_roll);
    Infrastructure electricCompany("Electric Company", 150);
   electricCompany.set_owner(&player1);  // Simulate player 1 acquiring Electric Company
    // Player 2 steps on Electric Company owned by Player 1
    electricCompany.action(player2,window);
    CHECK((player1.getCash() == 1500+(10*dice_roll)));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1500-(10*dice_roll)));  // Player 2's cash decreases by rent

    Infrastructure waterCompany("Water Company", 150);
    waterCompany.set_owner(&player1);  // Simulate player 1 acquiring Water Company
    waterCompany.action(player2, window);
    CHECK((player1.getCash() == 1500+2*(10*dice_roll)));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1500-2*(10*dice_roll)));  // Player 2's cash decreases by rent
}

TEST_CASE("Railroad Rent Calculation") {
    Player player1(Player1, PlayerColor::Red, 1,window);
    Player player2(Player2, PlayerColor::Blue, 1,window);
    player1.setCash(1500);
    player2.setCash(1500);
    Infrastructure railroad("Railroad", 200);

    railroad.set_owner(&player1);  // Simulate player 1 acquiring the Railroad
    player1.IncreaseNumRailRoad();
    railroad.action(player2, window);
    CHECK((player1.getCash() == 1550));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1450));  // Player 2's cash decreases by rent

    player1.IncreaseNumRailRoad();  // Simulate that player 1 owns 2 railroads
   // railroad.action(player2, window);
   railroad.action(player2,window);
    CHECK((player1.getCash() == 1650));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1350));  // Player 2's cash decreases by rent
}

TEST_CASE("Simulate 100 Chance Card Draws") {
    // Create players for testing
    Player player1(Player1, PlayerColor::Red, 1, window);
    player1.setCash(100);  // Starting cash
    Player player2(Player2, PlayerColor::Blue, 2, window);
    player2.setCash(100);  // Starting cash
    Player player3(Player3, PlayerColor::Green, 3, window);
    player3.setCash(100);  // Starting cash
    Player player4(Player4, PlayerColor::Yellow, 4, window);
    player4.setCash(100);  // Starting cash
    std::vector<Player> players = {player1, player2, player3, player4};

    for (int i = 0; i < 100; ++i) {
        int initialCash = player1.getCash();
        int initialPosition = player1.getPosition();
        ChanceCard card = ChanceCard::DrawCard(player1, players, window);
        // Store the initial cash and position before applying the card effect
            // Check for bankruptcy
        if (player1.getCash() < 0) {
            player1.setBankruptcy();
            CHECK((player1.getCash() >= 0)); // Ensure player cash is not negative
            break; // Exit loop if player goes bankrupt
        }

        // Nested subcases for different card effects
        if (card.getEffect() == Effect::AdvanceToGo) {
            SUBCASE("AdvanceToGo Effect") {
                CHECK((player1.getPosition() == 0));
            }
        }
        else if (card.getEffect() == Effect::BankPaysYouDividend) {
            SUBCASE("BankPaysYouDividend Effect") {
                CHECK((player1.getCash() == initialCash + 50));
            }
        }
        else if (card.getEffect() == Effect::GoBack3Spaces) {
            SUBCASE("GoBack3Spaces Effect") {
                int newPosition = player1.getPosition();
                CHECK((newPosition == (initialPosition - 3 + 40) % 40)); // Wrap around for board positions
            }
        }
        else if (card.getEffect() == Effect::GoDirectlyToJail) {
            SUBCASE("GoDirectlyToJail Effect") {
                int pos=player1.getPosition();
                CHECK((pos == 10)); // Jail is located at position 10
            }
        }
        else if (card.getEffect() == Effect::PayPoorTax) {
            SUBCASE("PayPoorTax Effect") {
                CHECK((player1.getCash() == initialCash - 15));
            }
        }
        else if (card.getEffect() == Effect::ElectedChairman) {
            SUBCASE("ElectedChairman Effect") {
                CHECK((player1.getCash() == initialCash + 150));
            }
        }
        else if (card.getEffect() == Effect::BuildingLoanMatures) {
            SUBCASE("BuildingLoanMatures Effect") {
                CHECK((player1.getCash() == initialCash + 150));
            }
        }
        else if (card.getEffect() == Effect::GetOutOfJailFree) {
            SUBCASE("GetOutOfJailFree Effect") {
                CHECK((player1.getJailCard() > 0));
            }
        }
        else if (card.getEffect() == Effect::StreetRepairs) {
            SUBCASE("StreetRepairs Effect") {
                int houses = 0;
                int hotels = 0;
                int expectedCash = initialCash - ((houses * 40) + (hotels * 115));
                CHECK((player1.getCash() == expectedCash));
            }
        }
    }
}

TEST_CASE("Estate Creation") {
    Street estate("Street","CityTest",1, 350,20);
    CHECK(estate.getName() == "Street");
    CHECK(estate.getCity()=="CityTest");
    CHECK((estate.get_owner() == nullptr)); // Initially no owner
}

TEST_CASE("Set and Get Owner") {
    Player player1(Player1, PlayerColor::Red, 1, window);
    Street estate("Street","CityTest",1, 350,20);
    estate.set_owner(&player1);
    CHECK((estate.get_owner() == &player1));
}

TEST_CASE("Buy Estate Successfully") {
    Player player(Player1, PlayerColor::Red, 1, window);
    player.setCash(400); // Set enough cash to buy the estate
    Street estate("Street","CityTest",1, 350,20);
    estate.BuyEstate(player, window); // Attempt to buy the estate
    CHECK((estate.get_owner() == &player)); // Check if player is now the owner
    CHECK((player.getCash() == 50)); // Check if cash is deducted correctly
    CHECK((player.getEstates().at(0)==&estate));
}

TEST_CASE("Buy Estate Not Enough Cash") {
    Player player(Player1, PlayerColor::Red, 1, window);
    player.setCash(200); // Set not enough cash to buy the estate
    Street estate("Street","CityTest",1, 350,20);
    estate.BuyEstate(player, window); // Attempt to buy the estate
    CHECK((estate.get_owner() == nullptr)); // Check that the estate is still not owned
    CHECK((player.getCash() == 200)); // Cash should remain the same
}

TEST_CASE("Buy Estate Player Declines") {
    Player player(Player1, PlayerColor::Red, 1, window);
    player.setCash(400); // Set enough cash
    Street estate("Street","CityTest",1, 350,20);
    estate.BuyEstate(player, window); // Attempt to buy the estate but decline

    CHECK((estate.get_owner() == nullptr)); // Estate should not be owned
    CHECK((player.getCash() == 400)); // Cash should remain the same
}