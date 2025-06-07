#include "ItemCommands.h"
#include "items/ItemRegistry.h"
#include "effects/EffectRegistry.h"
#include <iostream>

void executeAddItem(const Command& command, GameState& gameState) {
	gameState.getInventory().addItem(command.id, command.itemQuantity);

	auto item = ItemRegistry::instance().get(command.id);
	std::cout << "Added " << command.itemQuantity << " x " << item->name << " to inventory.\n";
}

void executeRemoveItem(const Command& command, GameState& gameState) {
	gameState.getInventory().removeItem(command.id, command.itemQuantity);

	auto item = ItemRegistry::instance().get(command.id);
	std::cout << "Removed " << command.itemQuantity << " x " << item->name << " from inventory.\n";
}

void executeUseItem(const Command& command, GameState& gameState) {
	auto& inventory = gameState.getInventory();
	if (inventory.getItemCount(command.id) < command.itemQuantity) {
		std::cout << "You do not have enough of that item. \n";
		return;
	}

	auto item = ItemRegistry::instance().get(command.id);

	if (item->type == ItemType::Key) {
		std::cout << "You can't use that item here. \n";
		return;
	}

	auto& party = gameState.getParty();
	Character& target = *party->getMemberByIndex(command.targetIndex);
	Character& user = target; // for now, assume self-use

	const auto& effect = EffectRegistry::instance().get(item->effectID);
	int magnitude = item->magnitudeOverride.value_or(command.magnitudeOverride);

	effect.apply(gameState, user, target, magnitude);

	inventory.removeItem(command.id, command.itemQuantity);

	std::cout << "You used " << item->name << ".\n";
}