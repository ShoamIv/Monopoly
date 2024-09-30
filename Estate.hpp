
#ifndef MONOPOLY_ESTATE_HPP
#define MONOPOLY_ESTATE_HPP
#include "Square.hpp"
#include "button.hpp"
class Estate : public Square{
    Button yesButton;
    Button noButton;
protected:
    int cost;                       //cost to acquire the street.
    Player * owner{};             // owner this estate.
public:
    Estate(const std::string &name, int cost);
    //setters
    void set_cost(int _cost);
    void set_owner(Player *_owner);
    //getters
    [[nodiscard]] int get_cost() const;
    Player * get_owner();
    void BuyEstate(Player & player,sf::RenderWindow& window);
    virtual void drawHousesAndHotel(sf::RenderWindow &window)=0;

};


#endif //MONOPOLY_ESTATE_HPP
