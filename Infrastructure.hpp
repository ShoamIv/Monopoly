
#ifndef MONOPOLY_INFRASTRUCTURE_HPP
#define MONOPOLY_INFRASTRUCTURE_HPP
#include "Estate.hpp"

/**
 * @class Infrastructure
 * @brief Represents a utility (Water/Electric) or a Railroad in the Monopoly game.
 * The Infrastructure class extends the Estate class, adding specific actions
 * and behaviors for utility and railroad properties. It allows for interaction
 * with players who land on these properties, performing actions such as charging rent.
 */

class Infrastructure : public Estate {
 std::string name;              //Utilities(Water/Electric or RailRoad).
void CompanyAction(Player &player, sf::RenderWindow &window);
void RailroadAction(Player &player, sf::RenderWindow &window);

public:
    Infrastructure(const std::string& name,int cost);
    /**
     * Action performed by player(visitor/owner).
     * @param player
     * @param window
     */
    void action(Player &player, sf::RenderWindow &window) override;
    /**
     * Draw to mark ownership.
     * @param window
     */
    void drawHousesAndHotel(sf::RenderWindow &window) override;

};


#endif //MONOPOLY_INFRASTRUCTURE_HPP
