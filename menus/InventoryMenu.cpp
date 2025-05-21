#include "InventoryMenu.h"
#include "Menu.h"
#include <iostream>

void registerInventoryMenu(MenuRegistry& menuRegistry, GameState& gameState) {
	menuRegistry.addMenuFactory("inventory", [&gameState]() {
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
		return menu;
	});
}