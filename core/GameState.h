#pragma once

#include "PlayerInventory.h"
#include <unordered_map>
#include <string>

class GameState
{
public:
	// flags
	std::unordered_map<std::string, bool> flags;               // progression flags

	bool hasFlag(const std::string& key) const;                // checks if player has flag w/ string lookup
	void setFlag(const std::string& key, bool enabled = true); // sets a flag's value to true

	// player inventory
	PlayerInventory& getInventory();
	const PlayerInventory& getInventory() const;

private:
	PlayerInventory inventory;
};

