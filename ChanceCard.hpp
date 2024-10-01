
#ifndef MONOPOLY_CHANCECARD_HPP
#define MONOPOLY_CHANCECARD_HPP
#include <vector>
#include <string>
#include "Player.hpp"
/**
 * This header defines common header for Chance Effects that may be apply on a player.
 * each effect has detailed explanation.
 */
class ChanceCard {
    enum class Effect {
        AdvanceToGo,                   // 1. Advance to Go (Collect $200)
        BankPaysYouDividend,           // 2. Bank pays you dividend of $50
        GoBack3Spaces,                 // 3. Go back 3 spaces
        GoDirectlyToJail,              // 4. Go directly to Jail – do not pass Go, do not collect $200
        PayPoorTax,                    // 6. Pay poor tax of $15
        ElectedChairman,               // 9. Pay each player $50
        BuildingLoanMatures,           // 10. Collect $150
        GetOutOfJailFree,              // 11. Get out of Jail Free
        StreetRepairs,                 // 14. Street repairs – $40 per house, $115 per hotel

    };
    Effect effect;
    int amount=0;
    void ApplyEffect(Player &player, std::vector<Player> &Players, sf::RenderWindow &window);
    explicit ChanceCard(Effect effect); // Constructor
public:
     static ChanceCard DrawCard(Player &player, std::vector<Player> &Players, sf::RenderWindow &window);

};


#endif //MONOPOLY_CHANCECARD_HPP
