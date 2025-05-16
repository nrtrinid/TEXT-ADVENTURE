#include "Menu.h"

#include <iostream>

Menu::Menu() : id("???"), name("???"), description("???") {}

Menu::Menu(const std::string& name, const std::string& description) 
	: id(name), name(name), description(description) {}

Menu::Menu(const std::string& id, const std::string& name, const std::string& description)
	: id(id), name(name), description(description) {}

void Menu::addOption(const MenuOption& menuOption) {
	menuOptions.push_back(menuOption);
}

void Menu::removeOptionById(const std::string& optionId) {
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

const std::string& Menu::getId() const {
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