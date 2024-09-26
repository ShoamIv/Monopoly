
#include "ChanceCard.hpp"

ChanceCard::ChanceCard(ChanceCard::Effect effect,int amount) : effect(effect) , amount(amount){}

ChanceCard ChanceCard::DrawCard(Player &player) {
    return {ChanceCard::Effect::AdvanceToStCharlesPlace, 0};
}

