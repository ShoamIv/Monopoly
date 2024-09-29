#include "ChanceCard.hpp"
#include <iostream>
#include <random> // Include for random number generation

ChanceCard::ChanceCard(Effect effect)
        : effect(effect) {}

void ChanceCard::ApplyEffect(Player &player, std::vector<Player> &Players, sf::RenderWindow &window) {
    switch (effect) {
        case Effect::AdvanceToGo:
            player.MoveTo("Go",window); // Move to Go and handle collecting money
            player.setCash(200);
            std::cout << player.getName() << " collects $200 for advancing to Go." << std::endl;
            break;

        case Effect::BankPaysYouDividend:
            player.setCash(50);
            std::cout << player.getName() << " receives a dividend of $50." << std::endl;
            break;

        case Effect::GoBack3Spaces:
            player.Move(-3, window);
            std::cout << player.getName() << " goes back 3 spaces." << std::endl;
            break;

        case Effect::GoDirectlyToJail:
            player.MoveTo("Jail",window);
            player.setJail(1);
            std::cout << player.getName() << " goes directly to Jail. For 1 turn." << std::endl;
            break;

        case Effect::PayPoorTax:
            player.setCash(-15);
            std::cout << player.getName() << " pays poor tax of $15." << std::endl;
            break;

        case Effect::ElectedChairman:
            for (Player &other : Players) {
                if (&other != &player) {
                    other.setCash(-50);
                    player.setCash(50);
                    std::cout << other.getName() << " pays $50 to " << player.getName() << "." << std::endl;
                }
            }
            break;

        case Effect::BuildingLoanMatures:
            player.setCash(150);
            std::cout << player.getName() << " collects $150 from matured building loan." << std::endl;
            break;

        case Effect::GetOutOfJailFree:
            player.IncreaseJailCard();
            std::cout << player.getName() << " receives a Get Out of Jail Free card." << std::endl;
            break;

        case Effect::StreetRepairs: {
            int houses =0;// player.getNumHouses();  // You need to implement this
            int hotels =0;// player.getNumHotels();  // You need to implement this
            int repairCost = (houses * 40) + (hotels * 115);
            player.setCash(-repairCost);
            std::cout << player.getName() << " pays $" << repairCost << " for street repairs." << std::endl;
            break;
        }
        default:
            std::cout << "No effect for this card." << std::endl;
            break;
    }
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
