#pragma once

#include "MenuRegistry.h"
#include <string>

class MenuController
{
public:
	MenuController(MenuRegistry& menuRegistry);

	// set the current menu by name
	void setCurrentMenu(const std::string& menuName);

	// display the current menu
	void displayCurrentMenu(size_t selectedIndex) const;

	// process the user's input
	void processInput(size_t choice);

	// getter for menu name
	const std::string& getCurrentMenuName() const;

private:
	const MenuRegistry& menuRegistry; // read-only reference to the menu registry
	std::string currentMenuName;
};