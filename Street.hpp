
#ifndef MONOPOLY_STREET_HPP
#define MONOPOLY_STREET_HPP
#include "Estate.hpp"
/**
 * @class Street
 * @brief Represents a street property in the Monopoly game.
 *
 * The Street class extends the Estate class, adding functionality specific to streets,
 * including upgrading the street by building houses and hotels, and charging rent to visitors.
 * Players who own streets can upgrade them, and visitors must pay rent based on the number of houses/hotel.
 */
class Street : public Estate {
    std::string city;
    int BaseRent;
    bool upgradable=false;              //return if this street upgradable.
    int HouseCount=0;                      //Number of Houses at the street.
    bool Hotel=false;                          //if hotel is built.
    int HouseCost=cost*2;                           // each House built BaseCost multiply 2
    int HotelCost= 4*HouseCost+100;                   //Logic for HotelCost.
    /**
     * Action Performed By owner(Upgrade).
     */
    void OwnerAction(Player &player, sf::RenderWindow &window);
    /**
     * action Performed on Visitor, pay rent, check Bankrupt.
     * @param player
     * @param window
     */
    void VisitorAction(Player &player,sf::RenderWindow &window);

public:
    Street(const std::string& name,std::string  city,int color,int cost,int BaseRent);
    void action(Player &player, sf::RenderWindow &window) override;
    //if upgradable suggest to the player to upgrade.
    void isUpgradable(const std::vector<std::unique_ptr<Square>>& squares);
    //get city the street located in.
    std::string getCity() const;
    /**
     * Draw basic street marker.
     * draw each house(rectangle)
     * at 4 houses draw slightly bigger house, marked as hotel.
     * @param window
     */
    void drawHousesAndHotel(sf::RenderWindow &window) override;
};




#endif //MONOPOLY_STREET_HPP
