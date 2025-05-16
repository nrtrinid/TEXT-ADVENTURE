#include "MenuController.h"
#include <iostream>
#include <stdexcept>

// constructor to initialize the menu controller with a reference to the menu registry
MenuController::MenuController(MenuRegistry& menuRegistry)
	: menuRegistry(menuRegistry), currentMenuName("???") {}

// set the current menu by name
void MenuController::setCurrentMenu(const std::string& menuName) {
	if (menuRegistry.hasMenu(menuName)) {
		currentMenuName = menuName;
	}
	else {
		throw std::invalid_argument("Menu not found: " + menuName);
	}
}

// display the current menu
void MenuController::displayCurrentMenu(size_t selectedIndex) const {
	const Menu& menu = menuRegistry.getMenu(currentMenuName);
	const auto& menuOptions = menu.getMenuOptions();

	// display the menu name and description
	std::cout << "\x1B[2K"; // erase the entire line
	std::cout << menu.getName() << std::endl;
	std::cout << menu.getDescription() << std::endl;

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
		menuItems[choice - 1].action(); // execute the action associated with the chosen menu item
	}
	else {
		std::cout << "Invalid choice. Please try again." << std::endl;
	}
}

const std::string& MenuController::getCurrentMenuName() const {
	return currentMenuName;
}