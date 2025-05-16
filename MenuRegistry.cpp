#include "MenuRegistry.h"
#include <iostream>

void MenuRegistry::addStaticMenu(const Menu& newStaticMenu) {
	// check if the menu already exists
	if (staticMenus.find(newStaticMenu.getId()) != staticMenus.end()) {
		std::cerr << "Menu \"" << newStaticMenu.getId() << "\" is being replaced!\n";
	}
	staticMenus[newStaticMenu.getId()] = newStaticMenu;
}

void MenuRegistry::addMenuFactory(const std::string& id, std::function<Menu()> factory) {
	if (factories.find(id) != factories.end()) {
		std::cerr << "Factory \"" << id << "\" is being replaced!\n";
	}
	
	factories[id] = factory;
}

bool MenuRegistry::hasMenu(const std::string& id) const {
	return staticMenus.find(id) != staticMenus.end() || factories.find(id) != factories.end();
}

Menu MenuRegistry::getMenu(const std::string& id) const {
	// check for static menu first
	if (staticMenus.find(id) != staticMenus.end()) {
		return staticMenus.at(id);
	}
	// if no static menu found, check for a menu factory
	else if (factories.find(id) != factories.end()) {
		return factories.at(id)();
	}
	else {
		std::cerr << "Menu \"" << id << "\" does not exist!\n";
		return Menu();
	}
}