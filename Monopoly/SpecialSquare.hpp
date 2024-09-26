/*
 * Special squares header ////
 * ///
 * ///
 * ///
 * //
 * add document.
 */

#ifndef MONOPOLY_SPECIALSQUARE_HPP
#define MONOPOLY_SPECIALSQUARE_HPP
#include "Player.hpp"

class SpecialSquare: public Square{
    static void GotoJail(Player & player);
    static void Chance(Player & player);
    static void Tax(Player & player);
    static void FreeParking(Player & player);

public:

    enum class SquareType {
        GoToJail,
        Chance,
        Tax,
        FreeParking,
        Unknown
    };
    explicit SpecialSquare(std::string name);
    void action(Player & player) override;
    ~SpecialSquare() override;
    [[nodiscard]] SquareType getSquareType() const;
};

#endif //MONOPOLY_SPECIALSQUARE_HPP
