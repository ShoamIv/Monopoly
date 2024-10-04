

#ifndef MONOPOLY_SPECIALSQUARE_HPP
#define MONOPOLY_SPECIALSQUARE_HPP
#include "Player.hpp"
#include "ChanceCard.hpp"
/**
 * Special squares header
 *
 * This header defines the SpecialSquare class, which represents special types of squares
 * on the Monopoly board, such as Jail, GoToJail, Chance, Tax, and FreeParking.
 * Each square has a specific action when a player lands on it.
 */

class SpecialSquare: public Square{
     void GotoJail(Player & player,sf::RenderWindow &window);
     void Jail(Player & player,sf::RenderWindow &window);
     void Chance(Player & player,sf::RenderWindow &window);
     void Tax(Player & player,sf::RenderWindow &window);
     void FreeParking(Player & player,sf::RenderWindow &window);
public:
    enum class SquareType {
        Jail,
        GoToJail,
        Chance,
        Tax,
        FreeParking,
        Unknown
    };

    explicit SpecialSquare(const std::string &name);
    /**
     * Action performed on player, based on SquareType.
     * @param player
     * @param window
     */
    void action(Player & player, sf::RenderWindow &window) override;
    ~SpecialSquare() override;
    [[nodiscard]] SquareType getSquareType() const;
};

#endif //MONOPOLY_SPECIALSQUARE_HPP
