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

		// initalize the party
		gameState.getParty() = std::make_shared<Party>();

		auto& party = gameState.getParty();
		party->addMember(std::make_shared<Character>("c001", "Wren the Clever", 88));        // Rogue-ish intellect
		party->addMember(std::make_shared<Character>("c002", "Bastion of Elrock", 120));     // Tanky knight
		party->addMember(std::make_shared<Character>("c003", "Kaela the Ashwind", 95));      // Elemental mage
		party->addMember(std::make_shared<Character>("c004", "Thorn Gristlefang", 100, true)); // Mercenary bruiser

		party->getMemberByIndex(2)->setHP(50);
		party->getMemberByIndex(0)->setHP(25);

		gameState.getInventory().addItem("potion", 2);
		gameState.getInventory().addItem("elixir");
		gameState.getInventory().addItem("potion"); // should stack

		registerMenus(menuRegistry, menuController, gameState);

		menuController.setCurrentMenu("old mansion");

		while (running) {
			std::cout << "\033[H"; // reset cursor to redraw arrow

			menuController.displayCurrentMenu(selectedIndex);

			// Handle input
			InputKey key = getInput();
			const size_t optionCount = menuRegistry.getMenu(menuController.getCurrentMenuName()).getMenuOptions().size();

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
