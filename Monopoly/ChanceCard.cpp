
#include "ChanceCard.h++"

ChanceCard::ChanceCard(ChanceCard::Effect effect,int amount) : effect(effect) , amount(amount){}

ChanceCard ChanceCard::DrawCard(Player &player) {

    return ChanceCard(ChanceCard::Effect::AdvanceToStCharlesPlace, 0);
}

