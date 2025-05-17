#pragma once

#include "core/Command.h"
#include <string>
#include <vector>
#include <functional>

struct MenuOption
{
	std::string id;                               // unique identifier for the option
	std::string name;                             // name displayed to user
	std::string description;                      // short text shown in the hover box for this option
	std::function<std::vector<Command>()> action; // function that returns commands representing the effects of selecting this option

	// constructor defaulting id to name
	MenuOption(const std::string& name, const std::string& description, std::function<std::vector<Command>()> action)
		: id(name), name(name), description(description), action(std::move(action)) {}

	// constructor allowing custom id
	MenuOption(const std::string& id, const std::string& name, const std::string& description, std::function<std::vector<Command>()> action)
		: id(id), name(name), description(description), action(std::move(action)) {
	}
};

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
	void removeOptionById(const std::string& optionId);

	// getters
	MenuType getType() const;
	const std::string& getId() const;
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