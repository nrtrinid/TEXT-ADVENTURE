#include "InventoryMenu.h"
#include <iostream>

void registerInventoryMenu(MenuRegistry& menuRegistry, MenuController& menuController, GameState& gameState) {
	menuRegistry.addMenuFactory("inventory", [&menuController, &gameState]() {
		Menu menu("Inventory", "Items you are currently carrying:", MenuType::System);

		// placeholder item list
		menu.addOption(MenuOption("Mysterious Potion", "You are not sure what this does...", [] {
			return CommandList{
				makePrint("You drink the potion. It tastes like regret.\n"),
				makePause()
			};
			}));

		menu.addOption(MenuOption("Back", "Return to the previous menu.", [] {
			return CommandList{ makePopMenu() };
			}));

		return menu;
		});
}