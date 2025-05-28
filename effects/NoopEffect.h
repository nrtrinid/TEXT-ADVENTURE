#pragma once
#include "Effect.h"

class NoopEffect : public Effect {
public:
	void apply(GameState&, Character&, Character&, int) const override {
		// intentionally does nothing
	}

	std::unique_ptr<Effect> clone() const override {
		return std::make_unique<NoopEffect>();
	}
};
