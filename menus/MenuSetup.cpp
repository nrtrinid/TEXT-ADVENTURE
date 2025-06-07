#include "MenuSetup.h"
#include "InventoryMenu.h"
#include "PartyMenu.h"

#include "skills/Skill.h" // del later
#include "skills/SkillRegistry.h"// and this too 

#include <iostream>
#include <string>

void registerMenus(MenuRegistry& menuRegistry, MenuNavigator& menuController, GameState& gameState) {
	menuRegistry.addMenuFactory("old mansion", [&menuController, &gameState]() {
		Menu menu("Old Mansion", "The decaying wood of the mansion creaks as you step in, the dark roof looming several stories above you");

		menu.addOption(MenuOption("Creepy Library", "The dust gathered from the ancient books and secrets surrounds you", [](MenuNavigator&) {
			return CommandList{
				makePrint("You tiptoe into the dark library. The shelves creak.\n"),
				makePause()
			};
		}));

		menu.addOption(MenuOption("Dusty Basement", "A chill runs down your spine as you descend.", [](MenuNavigator&) {
			return CommandList{
				makeGotoMenu("dusty basement")
			};
		}));

		// Staircase logic: 3 possible versions
		if (!gameState.hasFlag("hasAtticKey") && !gameState.hasFlag("atticUnlocked")) {
			menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [](MenuNavigator&) {
				return CommandList{
					makePrint("The door is locked.\n"),
					makePause()
				};
			}));
		}
		else if (!gameState.hasFlag("atticUnlocked")) {
			menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [](MenuNavigator&) {
				return CommandList{
					makePrint("The door unlocks!\n"),
					makeSetFlag("atticUnlocked"),
					makeSetFlag("hasAtticKey", false),
					makeRemoveItem("attic_key"),
					makePause(),
					makeGotoMenu("attic")
				};
			}));
		}
		else {
			menu.addOption(MenuOption("Crumbling Staircase", "It looks like it leads to a door", [](MenuNavigator&) {
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
			menu.addOption(MenuOption("Clear the shelf of cobwebs", "That looks promising...", [](MenuNavigator&) {
				return CommandList{
					makeSetFlag("foundAtticKey"),
					makePrint("Brushing away the thick cobwebs leaves you with webs all over your hands, but also reveals a key.\n"),
					makePause()
				};
			}));
		}
		else if (!gameState.hasFlag("hasAtticKey")) {
			menu.setDescription("The air is cold and damp. A key now reveals itself on the shelf, and something moves just beyond the light.");
			menu.addOption(MenuOption("Pick up key", "The key glows faintly, almost reassuringly", [](MenuNavigator&) {
				return CommandList{
					makeSetFlag("hasAtticKey"),
					makePrint("You pick up the key, it feels warm.\n"),
					makeAddItem("attic_key"),
					makePause()
				};
			}));
		}
		else {
			menu.setDescription("The shelf now sits empty, the key long gone.");
		}

		menu.addOption(MenuOption("Return upstairs", "You peer up into what little light there is.", [](MenuNavigator&) {
			return CommandList{
				makeGotoMenu("old mansion")
			};
		}));

		return menu;
	});

	menuRegistry.addMenuFactory("attic", [&menuController, &gameState]() {
		Menu menu("Attic", "Dust hangs thick in the air. An old trunk sits in the corner.");

		if (!gameState.hasFlag("hasAtticCrystal")) {
			menu.addOption(MenuOption("Open the trunk", "It might contain something valuable.", [](MenuNavigator&) {
				return CommandList{
					makeSetFlag("hasAtticCrystal"),
					makePrint("Inside the trunk, you find a strange, humming crystal.\n"),
					makeAddItem("crystal"),
					makePause()
				};
			}));
		}

		menu.addOption(MenuOption("Practice magic", "Kaela channels a healing spell on herself.", [&gameState](MenuNavigator&) {
			const auto& party = gameState.getParty();
			auto target = party->getMemberByIndex(2); // Kaela
			const Skill& heal = SkillRegistry::instance().get("heal_spell");

			int beforeHP = target->getHP();
			int base = heal.baseMagnitude;
			int bonus = target->getSkillBonus(heal.scalingStat);
			int totalHeal = base + bonus;
			int maxHP = target->getMaxHP();
			int afterHP = std::min(beforeHP + totalHeal, maxHP); // simulate result

			std::string details = "Kaela focuses her thoughts...\n";
			details += "Heal Spell: base " + std::to_string(base) +
				" + bonus " + std::to_string(bonus) +
				" = " + std::to_string(totalHeal) + "\n";
			details += "HP: " + std::to_string(beforeHP) +
				" -> " + std::to_string(afterHP) + "\n";

			return CommandList{
				makePrint(details),
				makeUseSkill("heal_spell", 2), // still actually applies the effect
				makePause(),
				makePrint("\033[2J\033[H"), // Clear entire screen after showing stats
			};
		}));



		menu.addOption(MenuOption("Return downstairs", "You head back to the staircase.", [](MenuNavigator&) {
			return CommandList{
				makeGotoMenu("old mansion")
			};
		}));

		return menu;
	});

	Menu pause("pause_menu", "Menu", "System Options", MenuType::System);
	
	pause.addOption(MenuOption("Party", "View party", [](MenuNavigator&) {
		return CommandList{	makeGotoMenu("party", true) };
	}));

	pause.addOption(MenuOption("Inventory", "View items", [](MenuNavigator&) {
		return CommandList{ makeGotoMenu("inventory", true) };
	}));

	pause.addOption(MenuOption("Back", "Return to World", [](MenuNavigator&) {
		return CommandList{ makePopMenu() };
	}));

	pause.addOption(MenuOption("Quit", "Exit the game", [](MenuNavigator&) {
		return CommandList{ makeGotoMenu("confirm_quit", true) };
		}));

	Menu confirm("confirm_quit", "Are you sure?", "Are you sure you want to quit?", MenuType::System);

	confirm.addOption(MenuOption("Yes", "Exit the game", [](MenuNavigator&) {
		return CommandList{ makeQuitGame() };
	}));

	confirm.addOption(MenuOption("No", "Return to previous menu", [](MenuNavigator&) {
		return CommandList{ makePopMenu() };
	}));

	menuRegistry.addStaticMenu(pause);
	menuRegistry.addStaticMenu(confirm);

	registerInventoryMenu(menuRegistry, gameState);
	registerPartyMenu(menuRegistry, gameState);
}