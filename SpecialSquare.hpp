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
#include "ChanceCard.hpp"
#include "Button.hpp"


class SpecialSquare: public Square{
     void GotoJail(Player & player,sf::RenderWindow &window);
     void Chance(Player & player,sf::RenderWindow &window);
     void Tax(Player & player,sf::RenderWindow &window);
     void FreeParking(Player & player,sf::RenderWindow &window);
    sf::Font font;
    std::string handlePay(Player &player);
    std::string handleRoll(Player &player);
public:
    enum class SquareType {
        GoToJail,
        Chance,
        Tax,
        FreeParking,
        Unknown
    };

    explicit SpecialSquare(const std::string &name);
    void action(Player & player, sf::RenderWindow &window) override;
    ~SpecialSquare() override;
    [[nodiscard]] SquareType getSquareType() const;
};

#endif //MONOPOLY_SPECIALSQUARE_HPP
