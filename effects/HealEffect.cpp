#include "HealEffect.h"
#include "core/GameState.h"
#include "entities/Character.h"

void HealEffect::apply(GameState& gameState, Character& user, Character& target, int magnitude) const {
	int amount = std::min(magnitude, target.getMaxHP() - target.getHP());
	target.setHP(target.getHP() + amount);
}

std::unique_ptr<Effect> HealEffect::clone() const {
	return std::make_unique<HealEffect>(*this);
}

