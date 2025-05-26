#pragma once
#include "Effect.h"

class HealEffect : public Effect {
public:
	void apply(GameState& gameState,
		Character& user,
		Character& target,
		int magnitude) const override;
	
	std::unique_ptr<Effect> clone() const override;
};