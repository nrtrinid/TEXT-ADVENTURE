#include "MenuController.h"
#include "skills/SkillRegistry.h"
#include "systems/SkillSystem.h"
#include "commands/ItemCommands.h"
#include "commands/ItemCommands.h"
#include "commands/SkillCommands.h"

#include <iostream>
#include <stdexcept>

// constructor to initialize the menu controller with a reference to the menu registry
MenuController::MenuController(MenuRegistry& menuRegistry, GameState& gameState)
	: menuRegistry_(menuRegistry), gameState_(gameState), commandProcessor_(gameState, *this) {}


// display the current menu
void MenuController::displayCurrentMenu(size_t selectedIndex) const {
	Menu menu = activeMenu();

	const auto& menuOptions = menu.getMenuOptions();
	MenuType type = menu.getType();

	if (type == MenuType::System) {
		std::cout << "\x1B[2K";
		std::cout << "\033[32m"; // green

		std::string name = menu.getName();
		std::size_t totalWidth = 29;
		std::size_t padding = (totalWidth - name.length()) / 2;
		std::size_t extra = (totalWidth - name.length()) % 2;

		std::cout << "+";
		std::cout << std::string(totalWidth, '=') << "+\n"; // top border

		std::cout << "|"
			<< std::string(padding, ' ')
			<< name
			<< std::string(padding + extra, ' ')
			<< "|\n";

		std::cout << "+" << std::string(totalWidth, '=') << "+\n\n"; // bottom border

		std::cout << "\033[0m"; // reset color

		if (!menu.getDescription().empty()) {
			std::cout << menu.getDescription() << "\n\n";
		}
	}
	else {
		std::cout << "\x1B[2K";
		std::cout << menu.getName() << "\n";
		std::cout << menu.getDescription() << "\n\n";
	}

	// display the menu items
	for (size_t i = 0; i < menuOptions.size(); ++i) {
		const auto& option = menuOptions[i];
		std::string color;

		// Special case for "Quit"
		if (option.name == "Quit" && i == selectedIndex) {
			color = MenuOption::COLOR_RED;
		}
		else if (i == selectedIndex) {
			color = MenuOption::COLOR_DIM;
		}
		else {
			color = option.colorCode;
		}

		if (i == selectedIndex) {
			std::cout << color << "> " << option.name << MenuOption::COLOR_RESET << "\n";
		}
		else {
			std::cout << "  " << option.colorCode << option.name << MenuOption::COLOR_RESET << "\n";
		}
	}

	std::cout << "\n";

	if (!menuOptions.empty() && selectedIndex < menuOptions.size()) {
		std::cout << "\x1B[2K"; // erase the entire line
		std::cout << ">> " << menuOptions[selectedIndex].description << "\n";
	}
}

// process the user's input
void MenuController::processInput(size_t choice) {
	Menu menu = activeMenu(); // read-only reference to the menu
	const auto& menuOptions = menu.getMenuOptions(); // read-only reference to the menu items

	// check if the choice is valid
	if (choice == 0 || choice > menuOptions.size()) {
		std::cout << "Invalid choice. Please try again." << std::endl;
		return;
	}
	executeCommands(menuOptions[choice - 1].action(*this)); // execute the action associated with the chosen menu item
}

const std::string& MenuController::getCurrentMenuID() const {
	return currentMenuID_;
}

void MenuController::executeCommands(const std::vector<Command>& commands) {
	commandProcessor_.executeCommands(commands);
}

// menuNavigator implementation
void MenuController::pushMenu(std::shared_ptr<Menu> menu) {
	dynamicStack_.push_back(std::move(menu));
}

void MenuController::popMenu() {
	if (!dynamicStack_.empty()) dynamicStack_.pop_back();
	else returnToPreviousMenu();
}

void MenuController::gotoMenu(const std::string& id, bool remember) {
	if (remember) idStack_.push_back(currentMenuID_);
	currentMenuID_ = id;
}

// helper to fetch active menu
Menu MenuController::activeMenu() const {
	return dynamicStack_.empty()
		? menuRegistry_.getMenu(currentMenuID_)
		: *dynamicStack_.back();
}

void MenuController::returnToPreviousMenu() {
	if (!idStack_.empty()) {
		currentMenuID_ = idStack_.back();
		idStack_.pop_back();
	}
}