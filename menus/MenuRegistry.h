#pragma once

#include "Menu.h"
#include <string>
#include <functional>
#include <unordered_map>

class MenuRegistry
{
public:
	// add a static menu to the registry
	void addStaticMenu(const Menu& menu);

	// stores instructions for building a menu
	void addMenuFactory(const std::string& id, std::function<Menu()> factory);

	// get a menu from the registry
	Menu getMenu(const std::string& menuName) const;

	// check if a menu exists in the registry
	bool hasMenu(const std::string& menuName) const;

private:
	std::unordered_map<std::string, Menu> staticMenus;                // map of menu names to menus, will not include factory-generated menus
	std::unordered_map<std::string, std::function<Menu()>> factories; // map of ids to menu factories
};