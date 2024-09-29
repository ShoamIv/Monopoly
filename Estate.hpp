
#ifndef MONOPOLY_ESTATE_HPP
#define MONOPOLY_ESTATE_HPP
#include "Square.hpp"

class Estate : public Square{

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


};


#endif //MONOPOLY_ESTATE_HPP
