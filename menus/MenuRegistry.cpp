#include "MenuRegistry.h"
#include <iostream>

void MenuRegistry::addStaticMenu(const Menu& newStaticMenu) {
	// check if the menu already exists
	if (staticMenus.find(newStaticMenu.getID()) != staticMenus.end()) {
		std::cerr << "Menu \"" << newStaticMenu.getID() << "\" is being replaced!\n";
	}
	staticMenus[newStaticMenu.getID()] = newStaticMenu;
}

void MenuRegistry::addMenuFactory(const std::string& id, std::function<Menu()> factory) {
	if (factories.find(id) != factories.end()) {
		std::cerr << "Factory \"" << id << "\" is being replaced!\n";
	}
	
	factories[id] = [factory]() {
		Menu menu = factory();

		if (menu.getType() == MenuType::World) {
			menu.addOption(MenuOption("pause-menu", "Menu", "View party, inventory, etc.", [] {
				return CommandList{ makeGotoMenu("pause menu", true) };
				}));
		}
		else if (menu.getType() == MenuType::System) {
			menu.addOption(MenuOption("Back", "Return to the previous menu.", [] {
				return CommandList{ makePopMenu() };
			}));
		}
		return menu;
	};
}

bool MenuRegistry::hasMenu(const std::string& id) const {
	return staticMenus.find(id) != staticMenus.end() || factories.find(id) != factories.end();
}

Menu MenuRegistry::getMenu(const std::string& id) const {
	// check for static menu first
	auto staticIt = staticMenus.find(id);
	if (staticIt != staticMenus.end()) {
		return staticIt->second;
	}
	// if no static menu found, check for a menu factory
	auto factoryIt = factories.find(id);
	if (factoryIt != factories.end()) {
		return factoryIt->second();
	}
	else {
		std::cerr << "Menu \"" << id << "\" does not exist!\n";
		return Menu();
	}
}