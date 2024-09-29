#include "ChanceCard.hpp"
#include <iostream>
#include <random> // Include for random number generation

ChanceCard::ChanceCard(Effect effect)
        : effect(effect) {}

void ChanceCard::ApplyEffect(Player &player, std::vector<Player> &Players, sf::RenderWindow &window) {
    std::string message; // Message to display

    switch (effect) {
        case Effect::AdvanceToGo:
            player.MoveTo("Go", window); // Move to Go and handle collecting money
            player.setCash(200);
            message = player.getName() + " collects $200 for advancing to Go.";
            break;

        case Effect::BankPaysYouDividend:
            player.setCash(50);
            message = player.getName() + " receives a dividend of $50.";
            break;

        case Effect::GoBack3Spaces:
            player.Move(-3, window);
            message = player.getName() + " goes back 3 spaces.";
            break;

        case Effect::GoDirectlyToJail:
            player.MoveTo("Jail", window);
            player.setJail(1);
            message = player.getName() + " goes directly to Jail. For 1 turn.";
            break;

        case Effect::PayPoorTax:
            player.setCash(-15);
            message = player.getName() + " pays poor tax of $15.";
            break;

        case Effect::ElectedChairman:
            for (Player &other : Players) {
                if (&other != &player) {
                    other.setCash(-50);
                    player.setCash(50);
                    message = other.getName() + " pays $50 to " + player.getName() + ".";
                }
            }
            break;

        case Effect::BuildingLoanMatures:
            player.setCash(150);
            message = player.getName() + " collects $150 from matured building loan.";
            break;

        case Effect::GetOutOfJailFree:
            player.IncreaseJailCard();
            message = player.getName() + " receives a Get Out of Jail Free card.";
            break;

        case Effect::StreetRepairs: {
            int houses = 0; // player.getNumHouses();  // Implement this method
            int hotels = 0; // player.getNumHotels();  // Implement this method
            int repairCost = (houses * 40) + (hotels * 115);
            player.setCash(-repairCost);
            message = player.getName() + " pays $" + std::to_string(repairCost) + " for street repairs.";
            break;
        }
        default:
            message = "No effect for this card.";
            break;
    }

    // Display the message in the GUI
    Square::updateMessage(message, window);
}

ChanceCard ChanceCard::DrawCard(Player &player, std::vector<Player> &Players, sf::RenderWindow &window) {
    // For simplicity, using a random number generator to pick a card effect
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 15); // 16 effects in total

    int cardIndex = distribution(generator);
    auto drawnEffect = static_cast<Effect>(cardIndex);

    ChanceCard drawnCard(drawnEffect); // The amount can be 0 for effects that do not require it

    // Apply the drawn effect to the player
    drawnCard.ApplyEffect(player,Players,window);

    return drawnCard;
}
