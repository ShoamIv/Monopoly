#include <sstream>
#include "doctest.h"
#include "Street.hpp"
#include "Board.hpp"
#include "Infrastructure.hpp"
#include "SpecialSquare.hpp"

std::string Player1="Amatiza";
std::string Player2="Karako";
std::string Player3="Avi";
std::string Player4="Shuali";
std::string Color1="RED";
std::string Color2="BLUE";

/*
 * Player Tests.
 */
TEST_CASE("Creation of Player") {
    std::string Check_string="Amatiza";
    Player player(Player1, Color1);
    CHECK(player.getName() == Check_string);  // Check the name
    CHECK((player.getCash()==0));          // Initial cash should be 0
    CHECK((player.getJail() == 0));    // Initial jail time should be 0
}

TEST_CASE("Cash Management in Player") {
    Player player(Player1,Color1);

    player.setCash((150));  // Set cash to 150
    CHECK((player.getCash() == 150));  // Check cash

    player.setCash((-50));  // Deduct cash
    CHECK((player.getCash() == 100));  // Cash should now be 100

    player.setCash((-100));  // Deduct cash more than current amount
    CHECK((player.getCash() == 0));  // Cash should not go below 0
}

TEST_CASE("Jail Time Management in Player") {
    Player player(Player1, Color1);

    // Check initial jail time
    CHECK((player.getJail() == 0));

    // Set jail time
    player.setJail(2);  // Add 2 turns in jail
    CHECK((player.getJail() == 2));

    // Reduce jail time
    player.setJail(-1);  // Remove 1 turn
    CHECK((player.getJail() == 1));  // Should now be 1

    // Set to negative jail time (if your logic allows)
    player.setJail(-1);
    CHECK((player.getJail() == 0));  // Should be 0 now
}
/*
TEST_CASE("Position Management in Player") {
    Player player(Player1, 1);
    // Check initial position
    CHECK(player.get_curr_position() == 0);

    player.set_pos(5);  // Move 5 spaces
    CHECK(player.get_curr_position() == 5);

    player.set_pos(38);  // Move from 38 to 0 (circular board)
    CHECK(player.get_curr_position() == 3);  // Should be at 3 (40 % 40 = 0)
}
*/

/*
 * Board Tests:
 */
TEST_CASE("Creation of the Board") {
    Board * board = Board::getBoard();
    CHECK((board != nullptr));  // Ensure the board singleton is created
}

TEST_CASE("Check if Board is Singleton") {
    Board * board1 = Board::getBoard();
    Board * board2 = Board::getBoard();
    CHECK((board1 == board2));  // Check both instances are the same (singleton)
}

TEST_CASE("Board Initialization with Squares") {
    Board * board = Board::getBoard();
    const auto& squares = board->getSquares();

    // Check if the board was initialized with the correct number of squares
    CHECK((!squares.empty()));  // Ensure squares are initialized

    // Verify some squares (change the indices if needed, based on your actual board setup)
    CHECK(squares[0]->getName() == "Go");  // First square is "Go"
    CHECK(squares[1]->getName() == "Neve-Ofer");  // Second square is a street
    CHECK(squares[2]->getName() == "Chance");  // Third square is a "Chance"
}

TEST_CASE("Check Specific Squares in Board") {
    Board * board = Board::getBoard();
    const auto& squares = board->getSquares();
    // Check specific squares for their type
    CHECK((dynamic_cast<SpecialSquare*>(squares[0].get()) != nullptr));  // "Go" is a SpecialSquare
    CHECK((dynamic_cast<Street*>(squares[1].get()) != nullptr));  // "Neve-Ofer" is a Street
    CHECK((dynamic_cast<SpecialSquare*>(squares[2].get()) != nullptr));  // "Chance" is a SpecialSquare
    CHECK((dynamic_cast<Infrastructure*>(squares[5].get()) != nullptr));  // "Railroad" is an Infrastructure
}

/*
 * SpecialSquare Tests:
 */

TEST_CASE("Creation of SpecialSquare") {
    SpecialSquare square("GoToJail");
    CHECK((square.getSquareType() == SpecialSquare::SquareType::GoToJail));  // Ensure the square type is correct
}

TEST_CASE("Check Square Type Mapping") {
    SpecialSquare chanceSquare("Chance");
    SpecialSquare taxSquare("Tax");
    SpecialSquare freeParkingSquare("FreeParking");

    CHECK((chanceSquare.getSquareType() == SpecialSquare::SquareType::Chance));
    CHECK((taxSquare.getSquareType() == SpecialSquare::SquareType::Tax));
    CHECK((freeParkingSquare.getSquareType() == SpecialSquare::SquareType::FreeParking));
    CHECK((SpecialSquare("Unknown").getSquareType() == SpecialSquare::SquareType::Unknown)); // Unknown type
}

TEST_CASE("Action on GoToJail Square") {
    Player player(Player1,Color1);
    player.setCash(100);  // Starting cash
    SpecialSquare goToJail("GoToJail");

    // Mock input for paying bail (you might need to refactor to allow input simulation)
    std::streambuf* originalCin = std::cin.rdbuf(); // Store original stream buffer
    std::istringstream input("P");  // Simulate user input to pay bail
    std::cin.rdbuf(input.rdbuf());  // Redirect cin to the string stream

    goToJail.action(player);
    CHECK((player.getCash() == 50));  // Cash after paying bail
    CHECK((player.getJail() == 0));  // Ensure player is not in jail anymore
    std::cin.rdbuf(originalCin); // Restore original stream buffer
}

TEST_CASE("Tax Deduction Action") {
    Player player(Player1,Color1);
    player.setCash(100);  // Starting cash
    SpecialSquare tax("Tax");
    tax.action(player);
    CHECK((player.getCash() == 0));  // Cash after tax deduction
}

TEST_CASE("Free Parking Action") {
    Player player(Player1,Color1);
    player.setCash(300);  // Starting cash
    SpecialSquare freeParking("FreeParking");
    freeParking.action(player);
    // Ensure player cash remains the same
    CHECK((player.getCash() == 300));  // Cash should still be 300
}

/*
TEST_CASE("Chance Action") {
    Player player(Player1,1);
    SpecialSquare chance("Chance");

    // Test the action method
    // Currently, Chance does not affect player state, just outputs a message
    // You may add more functionality for Chance in the future to test
    CHECK_NOTHROW(chance.action(player));  // Ensure action does not throw exceptions
}
*/

/*
 * Infrastructure Tests:
 */
/*
TEST_CASE("Acquisition of Infrastructure") {
    Player player(Player1, Color1);  // Initialize Player 1
    player.setCash(1500);
    Infrastructure electricCompany("Electric Company", 150);

    //electricCompany.Acquisition(player);
    CHECK(electricCompany.get_owner()->getName() == "Amatiza");  // Verify ownership

    // Ensure the player's cash is reduced by the cost of the company
    CHECK((player.getCash() == 1350));
}
*/
TEST_CASE("Electric & Water Company Rent Calculation") {
    Player player1(Player1,Color1);
    Player player2(Player2, Color2);
    player1.setCash(1500);
    player2.setCash(1500);

    Infrastructure electricCompany("Electric Company", 150);
    // Simulate player 1 acquiring the Electric Company
    electricCompany.set_owner(&player1);
    // Set the dice roll for player 2
    player2.setRecentDice(6);  // Simulating a dice roll of 6
    // Player 2 steps on Electric Company owned by Player 1
    electricCompany.action(player2);

    // Rent should be 10 * dice roll (10 * 6 = 60)
    CHECK((player1.getCash() == 1500 + 60));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1500 - 60));  // Player 2's cash decreases by rent

    Infrastructure waterCompany("Water Company", 150);
    electricCompany.set_owner(&player1);
    waterCompany.action(player2);
    CHECK((player1.getCash() == 1560 + 40));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1440 - 40));  // Player 2's cash decreases by rent
}



TEST_CASE("Railroad Rent Calculation") {
    Player player1(Player1,Color1);
    Player player2(Player2, Color2);
    player1.setCash(1500);
    player2.setCash(1500);
    Infrastructure railroad("Railroad", 200);

    // Simulate player 1 acquiring the Railroad
    railroad.set_owner(&player1);
    player1.IncreaseNumRailRoad();
    // Player 2 steps on Railroad owned by Player 1
    railroad.action(player2);

    CHECK((player1.getCash() == 1500 + 50));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1500 - 50));  // Player 2's cash decreases by rent

    // Simulate that player 1 owns 2 railroads
    player1.IncreaseNumRailRoad();
    railroad.action(player2);
    CHECK((player1.getCash() == 1500 + 100));  // Player 1's cash increases by rent
    CHECK((player2.getCash() == 1500 - 100));  // Player 2's cash decreases by rent
}
