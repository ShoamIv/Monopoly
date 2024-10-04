
#ifndef MONOPOLY_ESTATE_HPP
#define MONOPOLY_ESTATE_HPP
#include "Square.hpp"
#include "button.hpp"
/**
 * Estates Header, Virtual class Implemented by Street,Infrastructure.
 * Contain all types of Square that are can be bought.
 */
class Estate : public Square{
    Button yesButton;
    Button noButton;
protected:
    int cost;                       //cost to acquire the street.
    Player * owner{};             // owner this estate.
public:
    Estate(const std::string &name, int cost);
    //setters
    void set_owner(Player *_owner);
    //getters
    Player * get_owner();
    /**
     * Buy Estate buy player.
     * handle GUI and cash.
     */
    void BuyEstate(Player & player,sf::RenderWindow& window);
    virtual void drawHousesAndHotel(sf::RenderWindow &window)=0;

};


#endif //MONOPOLY_ESTATE_HPP
