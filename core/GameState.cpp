#include "GameState.h"

bool GameState::hasFlag(const std::string& key) const {
	auto iterator = flags.find(key);
	return iterator != flags.end() && iterator->second; // iterator->second = 'the bool value mapped to the key'
}

void GameState::setFlag(const std::string& key, bool enabled) {
	flags[key] = enabled;
}

PlayerInventory& GameState::getInventory() {
	return inventory;
}

const PlayerInventory& GameState::getInventory() const {
	return inventory;
}

Party::Ptr& GameState::getParty() {
	return party;
}

const Party::Ptr& GameState::getParty() const {
	return party;
}