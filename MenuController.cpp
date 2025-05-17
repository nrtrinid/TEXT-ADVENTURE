#include "MenuController.h"
#include <iostream>
#include <stdexcept>

// constructor to initialize the menu controller with a reference to the menu registry
MenuController::MenuController(MenuRegistry& menuRegistry, GameState& gameState)
	: menuRegistry(menuRegistry), gameState(gameState), currentMenuName("???") {}


void MenuController::returnToPreviousMenu() {
	if (!menuStack.empty()) {
		currentMenuName = menuStack.back();
		menuStack.pop_back();
	}
}

// set the current menu by ID (not display name)
void MenuController::setCurrentMenu(const std::string& menuId, bool remember) {
	if (menuRegistry.hasMenu(menuId)) {
		if (remember) {
			menuStack.push_back(currentMenuName);
		}
		currentMenuName = menuId;
	}
	else {
		throw std::invalid_argument("Menu not found: " + menuId);
	}
}

// display the current menu
void MenuController::displayCurrentMenu(size_t selectedIndex) const {
	const Menu& menu = menuRegistry.getMenu(currentMenuName);
	const auto& menuOptions = menu.getMenuOptions();
	MenuType type = menu.getType();

	if (type == MenuType::System) {
		std::cout << "\033[32m"; // green

		std::string name = menu.getName();
		int totalWidth = 29;
		int padding = (totalWidth - name.length()) / 2;
		int extra = (totalWidth - name.length()) % 2;

		std::cout << "+";
		std::cout << std::string(totalWidth, '=') << "+\n"; // top border

		std::cout << "|"
			<< std::string(padding, ' ')
			<< name
			<< std::string(padding + extra, ' ')
			<< "|\n";

		std::cout << "+" << std::string(totalWidth, '=') << "+\n\n"; // bottom border

		std::cout << "\033[0m"; // reset color
	}
	else {
		std::cout << "\x1B[2K";
		std::cout << menu.getName() << "\n";
		std::cout << menu.getDescription() << "\n";
	}

	// display the menu items
	for (size_t i = 0; i < menuOptions.size(); ++i) {
		std::cout << (i == selectedIndex ? "> " : "  ");
		std::cout << menuOptions[i].name << "\n";
	}

	std::cout << "\n";

	if (!menuOptions.empty() && selectedIndex < menuOptions.size()) {
		std::cout << "\x1B[2K"; // erase the entire line
		std::cout << ">> " << menuOptions[selectedIndex].description << "\n";
	}
}

// process the user's input
void MenuController::processInput(size_t choice) {
	const Menu& menu = menuRegistry.getMenu(currentMenuName); // read-only reference to the current menu
	const auto& menuItems = menu.getMenuOptions(); // read-only reference to the menu items

	// check if the choice is valid
	if (choice > 0 && choice <= menuItems.size()) {
		executeCommands(menuItems[choice - 1].action()); // execute the action associated with the chosen menu item
	}
	else {
		std::cout << "Invalid choice. Please try again." << std::endl;
	}
}

const std::string& MenuController::getCurrentMenuName() const {
	return currentMenuName;
}

void MenuController::executeCommands(const std::vector<Command>& commands) {
	for (const auto& command : commands) {
		switch (command.type) {
		case Command::Type::Print: std::cout << command.text; break;
		case Command::Type::Pause: std::cin.get(); break;
		case Command::Type::SetFlag: gameState.setFlag(command.flag, command.enabled); break;
		case Command::Type::GotoMenu: setCurrentMenu(command.target, command.enabled); break;
		case Command::Type::PopMenu: returnToPreviousMenu(); break;
		}
	}
}