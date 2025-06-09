#include <iostream>

#include "menus/Menu.h"
#include "menus/MenuRegistry.h"
#include "menus/MenuController.h"
#include "menus/MenuSetup.h"

#include "core/Input.h"
#include "core/GameState.h"
#include "core/PlayerInventory.h"

#include "skills/SkillRegistry.h"
#include "systems/SkillSystem.h"
#include "effects/EffectRegistry.h"
#include "items/Item.h"

int main()
{
	try {
		GameState gameState;

		MenuRegistry menuRegistry;
		MenuController menuController(menuRegistry, gameState);

		bool running = true;
		size_t selectedIndex = 0;

		// initialize the party
		gameState.getParty() = std::make_shared<Party>();

		auto& party = gameState.getParty();
		party->addMember(std::make_shared<Character>("c001", "Wren the Clever"));        // Rogue-ish intellect
		party->addMember(std::make_shared<Character>("c002", "Bastion of Elrock"));     // Tanky knight
		party->addMember(std::make_shared<Character>("c003", "Kaela the Ashwind"));      // Elemental mage
		party->addMember(std::make_shared<Character>("c004", "Thorn Gristlefang", true)); // Mercenary bruiser

		party->getMemberByIndex(0)->setStat("resolve", 20);
		party->getMemberByIndex(2)->setStat("resolve", 20);
		party->getMemberByIndex(2)->setHP(10);
		party->getMemberByIndex(0)->setHP(10);

		gameState.getInventory().addItem("potion", 2);
		gameState.getInventory().addItem("elixir");
		gameState.getInventory().addItem("potion"); // should stack

		gameState.getInventory().addItem("iron_sword");
		gameState.getInventory().addItem("leather_jerkin");
		gameState.getInventory().addItem("life_gem", 2);
		gameState.getInventory().addItem("greatsword");

		registerMenus(menuRegistry, menuController, gameState);

		if (!menuRegistry.hasMenu("old mansion")) {
			std::cerr << "[ERROR] Menu 'old mansion' not found! Exiting...\n";
			std::cin.get();
			return 1;
		}

		menuController.gotoMenu("old mansion");

		while (running) {
			std::cout << "\033[H"; // reset cursor to redraw arrow

			menuController.displayCurrentMenu(selectedIndex);

			// Handle input
			InputKey key = getInput();
			const size_t optionCount = menuController.activeMenu().getMenuOptions().size();

			switch (key) {
			case InputKey::Up:
				if (selectedIndex == 0)
					selectedIndex = optionCount - 1;
				else
					--selectedIndex;
				break;
			case InputKey::Down:
				selectedIndex = (selectedIndex + 1) % optionCount;
				break;
			case InputKey::Enter:
				system("cls");
				menuController.processInput(selectedIndex + 1);
				selectedIndex = 0;
				if (gameState.quitRequested()) running = false;
				break;

			default:
				break;
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
		std::cin.get(); // optional pause
		return 1;
	}
}
