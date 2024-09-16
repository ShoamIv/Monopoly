/*
 * Special squares header ////
 * ///
 * ///
 * ///
 * //
 * add document.
 */

#ifndef MONOPOLY_SPECIALSQUARE_H
#define MONOPOLY_SPECIALSQUARE_H
#include "Player.h++"


class SpecialSquare: public Square{

    enum class SquareType {
        GoToJail,
        Chance,
        Tax,
        FreeParking,
        Unknown
    };

    [[nodiscard]] SquareType getSquareType() const;
    void GotoJail(Player & player);
    void Chance(Player & player);
    void Tax(Player & player);
    void FreeParking(Player & player);


public:
    explicit SpecialSquare(std::string name);
    void action(Player & player) override;
    ~SpecialSquare() override;
};

#endif //MONOPOLY_SPECIALSQUARE_H
