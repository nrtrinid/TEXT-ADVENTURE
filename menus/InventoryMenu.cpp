#include "InventoryMenu.h"
#include "Menu.h"
#include "items/ItemRegistry.h"
#include <iostream>

void registerInventoryMenu(MenuRegistry& menuRegistry, GameState& gameState) {
	menuRegistry.addMenuFactory("inventory", [&gameState]() {
		Menu menu("Inventory", "Items you are currently carrying:", MenuType::System);

		const auto& items = gameState.getInventory().getItems();

		for (const auto& entry : items) {
			const auto& item = ItemRegistry::instance().get(entry.itemID);

			std::string label = item.name + " (x" + std::to_string(entry.quantity) + ")";
			std::string description = item.description;

			menu.addOption(MenuOption(label, description, [id = entry.itemID] {
				return CommandList{
					makeUseItem(id),
					makePause()
				};
			}));
		}
		return menu;
	});
}