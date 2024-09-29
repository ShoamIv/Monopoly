
#ifndef MONOPOLY_INFRASTRUCTURE_HPP
#define MONOPOLY_INFRASTRUCTURE_HPP
#include "Estate.hpp"


class Infrastructure : public Estate {
 std::string name;              //Utilities(Water/Electric or RailRoad).
void CompanyAction(Player &player);
void RailroadAction(Player &player);

public:
    Infrastructure(const std::string& name,int cost);
    void action(Player &player, sf::RenderWindow &window) override;
};


#endif //MONOPOLY_INFRASTRUCTURE_HPP
