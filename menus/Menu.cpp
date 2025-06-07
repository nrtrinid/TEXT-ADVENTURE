#include "Menu.h"

#include <iostream>

Menu::Menu() : id_("???"), name_("???"), description_("???"), menuType(MenuType::World) {}

Menu::Menu(const std::string& name, const std::string& description, MenuType type)
	: id_(name), name_(name), description_(description), menuType(type) {}

Menu::Menu(const std::string& id, const std::string& name, const std::string& description, MenuType type)
	: id_(id), name_(name), description_(description), menuType(type) {}

void Menu::addOption(const MenuOption& menuOption) {
	menuOptions_.push_back(menuOption);
}

void Menu::removeOptionByID(const std::string& optionId) {
	auto iterator = std::find_if(menuOptions_.begin(), menuOptions_.end(),
		[&](const MenuOption& option) {
			return option.id == optionId;
		});

	if (iterator != menuOptions_.end()) {
		menuOptions_.erase(iterator);
	}
	else {
		std::cerr << "warning: option \"" << optionId << "\" not found in menu \"" << name_ << "\"." << std::endl;
	}
}

// getters

MenuType Menu::getType() const {
	return menuType;
}

const std::string& Menu::getID() const {
	return id_;
}

const std::string& Menu::getName() const {
	return name_;
}

const std::string& Menu::getDescription() const {
	return description_;
}

const std::vector<MenuOption>& Menu::getMenuOptions() const {
	return menuOptions_;
}

// setters

void Menu::setName(const std::string& newName) {
	name_ = newName;
}

void Menu::setDescription(const std::string& newDescription) {
	description_ = newDescription;
}