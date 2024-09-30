
#ifndef MONOPOLY_STREET_HPP
#define MONOPOLY_STREET_HPP
#include "Estate.hpp"

class Street : public Estate {
    std::string city;
    int BaseRent;
    bool upgradable=false;              //return if this street upgradable.
    int HouseCount=0;                      //Number of Houses at the street.
    bool Hotel=false;
    int HouseCost=cost*2;
    int HotelCost= 4*HouseCost+100;
    void OwnerAction(Player &player, sf::RenderWindow &window);
    void VisitorAction(Player &player,sf::RenderWindow &window);

public:
    Street(const std::string& name,std::string  city,int color,int cost,int BaseRent);
    void action(Player &player, sf::RenderWindow &window) override;
    void isUpgradable(const std::vector<std::unique_ptr<Square>>& squares);
    std::string getCity() const;
    void drawHousesAndHotel(sf::RenderWindow &window) override;
};




#endif //MONOPOLY_STREET_HPP
