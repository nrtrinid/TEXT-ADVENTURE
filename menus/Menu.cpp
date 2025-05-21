#include "Menu.h"

#include <iostream>

Menu::Menu() : id("???"), name("???"), description("???"), menuType(MenuType::World) {}

Menu::Menu(const std::string& name, const std::string& description, MenuType type)
	: id(name), name(name), description(description), menuType(type) {}

Menu::Menu(const std::string& id, const std::string& name, const std::string& description, MenuType type)
	: id(id), name(name), description(description), menuType(type) {}

void Menu::addOption(const MenuOption& menuOption) {
	menuOptions.push_back(menuOption);
}

void Menu::removeOptionByID(const std::string& optionId) {
	auto iterator = std::find_if(menuOptions.begin(), menuOptions.end(),
		[&](const MenuOption& option) {
			return option.id == optionId;
		});

	if (iterator != menuOptions.end()) {
		menuOptions.erase(iterator);
	}
	else {
		std::cerr << "warning: option \"" << optionId << "\" not found in menu \"" << name << "\"." << std::endl;
	}
}

// getters

MenuType Menu::getType() const {
	return menuType;
}

const std::string& Menu::getID() const {
	return id;
}

const std::string& Menu::getName() const {
	return name;
}

const std::string& Menu::getDescription() const {
	return description;
}

const std::vector<MenuOption>& Menu::getMenuOptions() const {
	return menuOptions;
}

// setters

void Menu::setName(const std::string& newName) {
	name = newName;
}

void Menu::setDescription(const std::string& newDescription) {
	description = newDescription;
}