#pragma once

#include <memory>

class GameState;
class Character;

class Effect {
public:
	virtual ~Effect() = default;

    // ‘magnitude’ lets us reuse the same class for Potion-30, Potion-60, etc.
    virtual void apply(GameState& world,
        Character& user,
        Character& target,
        int magnitude) const = 0;

    virtual std::unique_ptr<Effect> clone() const = 0;
};