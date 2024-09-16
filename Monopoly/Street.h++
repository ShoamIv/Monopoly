//
// Created by Shoham on 14/09/2024.
//

#ifndef MONOPOLY_STREET_H
#define MONOPOLY_STREET_H
#include "Estate.h++"

class Street : public Estate {
    std::string city;
    int color;
public:
    Street(const std::string& name,std::string city,int color,int cost,int rent);
    void action(Player &player) override;
};




#endif //MONOPOLY_STREET_H
