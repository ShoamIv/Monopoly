
#ifndef MONOPOLY_STREET_HPP
#define MONOPOLY_STREET_HPP
#include "Estate.hpp"

class Street : public Estate {
    std::string city;
    int BaseRent;
    int color;                          //each city has its own color.
    bool upgradable=false;              //return if this street upgradable.
    int Houses=0;                      //Number of Houses at the street.
    bool Hotel=false;
    void OwnerAction();
    void VisitorAction(Player &player);
public:
    Street(const std::string& name,std::string  city,int color,int cost,int BaseRent);
    void action(Player &player) override;
    [[nodiscard]] int getBaseRent() const;


};




#endif //MONOPOLY_STREET_HPP
