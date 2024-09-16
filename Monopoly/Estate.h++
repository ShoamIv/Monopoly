
#ifndef MONOPOLY_ESTATE_H
#define MONOPOLY_ESTATE_H
#include "Square.h++"

class Estate : public Square{

    std::string city;
    int cost;                       //cost to acquire the street.
    int rent;                       // cost of rent.
    std::string owner;             // owner this estate.
    bool upgradable{};              //return if this estate upgradable.


public:
    Estate(const std::string &name, int cost, int rent);

    //setters
    void set_cost(int _cost);
    void set_rent(int _rent);
    void set_owner(std::string _owner);

    //getters
    [[nodiscard]] int get_cost() const;
    [[nodiscard]] int get_rent() const;
    std::string get_owner();

};


#endif //MONOPOLY_ESTATE_H
