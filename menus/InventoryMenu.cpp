#include "InventoryMenu.h"
#include <iostream>

void registerInventoryMenu(MenuRegistry& menuRegistry, MenuController& menuController, GameState& gameState) {
	menuRegistry.addMenuFactory("inventory", [&menuController, &gameState]() {
		Menu menu("Inventory", "Items you are currently carrying:", MenuType::System);

		const auto& items = gameState.getInventory().getItems();

		for (const auto& item : items) {
			std::string label = item.getName() + " (x" + std::to_string(item.getQuantity()) + ")";
			std::string desc = item.getDescription();

			std::string itemName = item.getName();

			menu.addOption(MenuOption(label, desc, [itemName] {
				return CommandList{
					makeUseItem(itemName),
					makePause()
				};
			}));
		}

		menu.addOption(MenuOption("Back", "Return to the previous menu.", [] {
			return CommandList{ makePopMenu() };
		}));

		return menu;
	});
}