#pragma once

#include "MenuOption.h"
#include <string>
#include <vector>
#include <functional>

enum class MenuType {
	World,
	System
};

class Menu
{
public:

	// default constructor
	Menu();

	// construct a menu where id = name, with a description and optional type (default is World)
	Menu(const std::string& name, const std::string& description, MenuType type = MenuType::World);

	// construct a menu with a custom id, name, description, and optional type (default is World)
	Menu(const std::string& id, const std::string& name, const std::string& description, MenuType type = MenuType::World);

	// TODO: maybe change to addOptionById to match the remove one
	// add an option to this menu
	void addOption(const MenuOption& menuOption);

	// remove an option from this menu (maybe removable)
	void removeOptionByID(const std::string& optionId);

	// getters
	MenuType getType() const;
	const std::string& getID() const;
	const std::string& getName() const;
	const std::string& getDescription() const;
	const std::vector<MenuOption>& getMenuOptions() const;

	// setters
	void setName(const std::string& newName);
	void setDescription(const std::string& newDescription);

private:
	MenuType menuType = MenuType::World; // default to world menu type

	std::string id;
	std::string name;
	std::string description;
	std::vector<MenuOption> menuOptions;
};