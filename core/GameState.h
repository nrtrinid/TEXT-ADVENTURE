#pragma once

#include "PlayerInventory.h"
#include "entities/Party.h"
#include <unordered_map>
#include <string>

class GameState
{
public:
	// flags
	bool hasFlag(const std::string& key) const;                // checks if player has flag w/ string lookup
	void setFlag(const std::string& key, bool enabled = true);

	// quitting the game
	void requestQuit();
	bool quitRequested() const;

	// player inventory
	PlayerInventory& getInventory();
	const PlayerInventory& getInventory() const;

	// party
	Party::Ptr& getParty();
	const Party::Ptr& getParty() const;

	// equips
	bool equipItem(const std::string& itemID, int characterIndex);
	void unequipSlot(int charIndex, Slot slot);

private:
	std::unordered_map<std::string, bool> flags;
	bool quitRequested_ = false;
	PlayerInventory inventory;
	Party::Ptr party;
};

