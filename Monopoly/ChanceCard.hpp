
#ifndef MONOPOLY_CHANCECARD_HPP
#define MONOPOLY_CHANCECARD_HPP
#include <vector>
#include <string>
#include "Player.hpp"
class ChanceCard {
    enum class Effect {
        AdvanceToGo,                   // 1. Advance to Go (Collect $200)
        BankPaysYouDividend,           // 2. Bank pays you dividend of $50
        GoBack3Spaces,                 // 3. Go back 3 spaces
        GoDirectlyToJail,              // 4. Go directly to Jail – do not pass Go, do not collect $200
        GeneralRepairs,                // 5. Make general repairs on all your property
        PayPoorTax,                    // 6. Pay poor tax of $15
        TripToReadingRailroad,         // 7. Take a trip to Reading Railroad
        WalkOnBoardwalk,               // 8. Advance token to Boardwalk
        ElectedChairman,               // 9. Pay each player $50
        BuildingLoanMatures,           // 10. Collect $150
        GetOutOfJailFree,              // 11. Get out of Jail Free
        AdvanceToIllinoisAve,          // 12. Advance to Illinois Ave.
        AdvanceToStCharlesPlace,       // 13. Advance to St. Charles Place
        StreetRepairs,                 // 14. Street repairs – $40 per house, $115 per hotel
        AdvanceToNearestUtility,       // 15. Advance to nearest Utility
        AdvanceToNearestRailroad       // 16. Advance to nearest Railroad
    };
    Effect effect;
    int amount=0;
public:
    ChanceCard(Effect effect,int amount); // Constructor
    static ChanceCard DrawCard(Player &player);
};


#endif //MONOPOLY_CHANCECARD_HPP
