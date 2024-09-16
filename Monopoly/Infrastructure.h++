//
// Created by Shoham on 14/09/2024.
//

#ifndef MONOPOLY_INFRASTRUCTURE_H
#define MONOPOLY_INFRASTRUCTURE_H
#include "Estate.h++"

class Infrastructure : public Estate {

public:
    Infrastructure(const std::string& name,int cost,int rent);
    void action(Player &player) override;
};


#endif //MONOPOLY_INFRASTRUCTURE_H
