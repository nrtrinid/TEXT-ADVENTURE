#include "MenuSetup.h"
#include "InventoryMenu.h"
#include <iostream>
#include <string>

void registerMenus(MenuRegistry& menuRegistry, MenuController& menuController, GameState& gameState) {
	menuRegistry.addMenuFactory("old mansion", [&menuController, &gameState]() {
		Menu menu("Old Mansion", "the decaying wood of the mansion creaks as you step in, the dark roof looming several stories above you");

		menu.addOption(MenuOption("Creepy Library", "the dust gathered from the ancient books and secrets surrounds you", [] {
			return CommandList{
				makePrint("You tiptoe into the dark library. the shelves creak.\n"),
				makePause()
			};
		}));

		menu.addOption(MenuOption("Dusty Basement", "A chill runs down your spine as you descend.", [] {
			return CommandList{
				makeGotoMenu("dusty basement")
			};
		}));

		// Staircase logic: 3 possible versions
		if (!gameState.hasFlag("hasAtticKey") && !gameState.hasFlag("atticUnlocked")) {
			menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [] {
				return CommandList{
					makePrint("The door is locked.\n"),
					makePause()
				};
			}));
		}
		else if (!gameState.hasFlag("atticUnlocked")) {
			menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [] {
				return CommandList{
					makePrint("The door unlocks!\n"),
					makePause(),
					makeSetFlag("atticUnlocked"),
					makeSetFlag("hasAtticKey", false),
					makeRemoveItem("Attic Key"),
					makeGotoMenu("attic")
				};
			}));
		}
		else {
			menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [] {
				return CommandList{
					makeGotoMenu("attic")
				};
			}));
		}

		return menu;
		});

	menuRegistry.addMenuFactory("dusty basement", [&menuController, &gameState]() {
		Menu menu("Dusty Basement", "The air is cold and damp. Cobwebs cling to a cracked shelf, and something moves just beyond the light.");

		if (!gameState.hasFlag("foundAtticKey")) {
			menu.addOption(MenuOption("Clear the shelf of cobwebs", "That looks promising...", []() {
				return CommandList{
					makeSetFlag("foundAtticKey"),
					makePrint("Brushing away the thick cobwebs leaves you with webs all over your hands, but also reveals a key.\n"),
					makePause()
				};
			}));
		}
		else if (!gameState.hasFlag("hasAtticKey")) {
			menu.setDescription("The air is cold and damp. A key now reveals itself on the shelf, and something moves just beyond the light.");
			menu.addOption(MenuOption("Pick up key", "The key glows faintly, almost reassuringly", []() {
				return CommandList{
					makeSetFlag("hasAtticKey"),
					makeAddItem("Attic Key", "Slightly warm.", 1, ItemType::Key),
					makePrint("You pick up the key, it feels warm.\n"),
					makePause()
				};
			}));
		}
		else {
			menu.setDescription("The shelf now sits empty, the key long gone.");
		}

		menu.addOption(MenuOption("Return upstairs", "You peer up into what little light there is.", []() {
			return CommandList{
				makeGotoMenu("old mansion")
			};
		}));

		return menu;
	});

	menuRegistry.addMenuFactory("attic", [&menuController, &gameState]() {
		Menu menu("Attic", "Dust hangs thick in the air. An old trunk sits in the corner.");

		if (!gameState.hasFlag("hasAtticCrystal")) {
			menu.addOption(MenuOption("Open the trunk", "It might contain something valuable.", []() {
				return CommandList{
					makeSetFlag("hasAtticCrystal"),
					makeAddItem("Crystal", "A pulsating gem, warm to the touch.", ItemType::Key),
					makePrint("Inside the trunk, you find a strange, humming crystal.\n"),
					makePause()
				};
			}));
		}

		menu.addOption(MenuOption("Return downstairs", "You head back to the staircase.", []() {
			return CommandList{
				makeGotoMenu("old mansion")
			};
		}));

		return menu;
	});

	Menu pause("pause menu", "Menu", "System Options", MenuType::System);
	
	pause.addOption(MenuOption("Party", "View party", [] {
		return CommandList{
			makePrint("Party would go here"),
			makePause()
		};
	}));

	pause.addOption(MenuOption("Inventory", "View items", [] {
		return CommandList{
			makeGotoMenu("inventory", true)
		};
	}));

	pause.addOption(MenuOption("Back", "Return to World", [] {
		return CommandList{ makePopMenu() };
	}));

	menuRegistry.addStaticMenu(pause);

	registerInventoryMenu(menuRegistry, menuController, gameState);
}