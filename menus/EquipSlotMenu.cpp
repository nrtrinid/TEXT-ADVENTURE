#include "EquipSlotMenu.h"
#include "Menu.h"
#include "core/MenuNavigator.h"
#include "core/GameState.h"
#include "items/ItemRegistry.h"
#include "entities/Character.h"
#include "equipment/Equippable.h"
#include <iostream>

Menu buildEquipSlotMenu(int characterIndex, Slot slot, GameState& gameState) {
	const auto& party = gameState.getParty()->getMembers();
	const auto& character = party.at(characterIndex);

	Menu menu("Equip " + std::string(slotToString(slot)),
		"Choose " + std::string(slotToString(slot)) + " for " + character->getName() + ":", MenuType::System);

	const auto& inventory = gameState.getInventory().getItems();
	for (const auto& item : inventory) {
		auto equipment = ItemRegistry::instance().getEquippable(item.itemID);
		if (!equipment) continue;

		const auto& slots = equipment->getRequiredSlots();
		if (std::find(slots.begin(), slots.end(), slot) == slots.end())
			continue;

		menu.addOption(MenuOption(
			equipment->name,
			equipment->getDescription(),
			[equipment, characterIndex](MenuNavigator&) {
				return CommandList{
					makeEquipItem(equipment->id, characterIndex),
					makePause(),
					makePopMenu()
				};
			}));
	}

	// Add unequip option if something is equipped
	if (character->hasEquipped(slot)) {
		menu.addOption(MenuOption(
			"Unequip",
			"Remove currently equipped item from this slot.",
			[characterIndex, slot](MenuNavigator&) {
				return CommandList{
					makeUnequipItem(characterIndex, slot),
					makePause(),
					makePopMenu()
				};
			}));
	}


	if (menu.getMenuOptions().empty()) {
		menu.setDescription("No compatible items in your inventory.");
		menu.addOption(MenuOption("Back", "Return to previous menu.", [](MenuNavigator&) {
			return CommandList{ makePopMenu() };
			}));
	}
	return menu;
}