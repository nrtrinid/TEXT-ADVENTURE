#include "MenuSetup.h"
#include <iostream>
#include <string>

void registerMenus(MenuRegistry& menuRegistry, MenuController& menuController, GameState& gameState) {
	menuRegistry.addMenuFactory("old mansion", [&menuController, &gameState]() {
		Menu menu("Old Mansion", "the decaying wood of the mansion creaks as you step in, the dark roof looming several stories above you");

		menu.addOption(MenuOption("Creepy Library", "the dust gathered from the ancient books and secrets surrounds you", []() {
			std::cout << "You tiptoe into the dark library. the shelves creak.\n";
			std::cin.get();
		}));

		menu.addOption(MenuOption("Dusty Basement", "A chill runs down your spine as you descend.", [&menuController]() {
			menuController.setCurrentMenu("dusty basement");
		}));

		menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [&menuController, &gameState]() {
			if (!gameState.hasFlag("hasAtticKey")) {
				std::cout << "The door is locked.\n";
				std::cin.get();
				return;
			}

			if (!gameState.hasFlag("atticUnlocked")) {
					std::cout << "The door unlocks!\n";
					std::cin.get();
					gameState.setFlag("atticUnlocked");
			}

			menuController.setCurrentMenu("attic");
				
		}));

		return menu;
	});

	menuRegistry.addMenuFactory("dusty basement", [&menuController, &gameState]() {
		Menu menu("Dusty Basement", "The air is cold and damp. Cobwebs cling to a cracked shelf, and something moves just beyond the light.");

		if (!gameState.hasFlag("foundAtticKey")) {
			menu.addOption(MenuOption("Clear the shelf of cobwebs", "That looks promising...", [&gameState]() {
				gameState.setFlag("foundAtticKey");
				std::cout << "Brushing away the thick cobwebs leaves you with webs all over your hands, but also reveals a key.\n";
				std::cin.get();
			}));
		}
		else if (!gameState.hasFlag("hasAtticKey")) {
			menu.setDescription("The air is cold and damp. A key now reveals itself on the shelf, and something moves just beyond the light.");
			menu.addOption(MenuOption("Pick up key", "The key glows faintly, almost reassuringly", [&gameState]() {
				gameState.setFlag("hasAtticKey");
				std::cout << "You pick up the key, it feels warm.\n";
				std::cin.get();
			}));
		}
		else {
			menu.setDescription("The shelf now sits empty, the key long gone.");
		}

		menu.addOption(MenuOption("Return upstairs", "You peer up into what little light there is.", [&menuController]() {
			menuController.setCurrentMenu("old mansion");
			}));

		return menu;
	});

	menuRegistry.addMenuFactory("attic", [&menuController, &gameState]() {
		Menu menu("Attic", "Dust hangs thick in the air. An old trunk sits in the corner.");

		if (!gameState.hasFlag("hasAtticCrystal")) {
			menu.addOption(MenuOption("Open the trunk", "It might contain something valuable.", [&gameState]() {
				gameState.setFlag("hasAtticCrystal");
				std::cout << "Inside the trunk, you find a strange, humming crystal.\n";
				std::cin.get();
			}));
		}

		menu.addOption(MenuOption("Return downstairs", "You head back to the staircase.", [&menuController]() {
			menuController.setCurrentMenu("old mansion");
		}));

		return menu;
	});
}