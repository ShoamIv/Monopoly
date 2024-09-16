

#include <utility>

#include "Street.h++"
Street::Street(const std::string& name, std::string city, int color, int cost, int rent) :
        Estate(name,cost,rent), city(std::move(city)),color(color) {}

void Street::action(Player &player) {

}
