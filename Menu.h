#pragma once

#include <string>
#include <vector>
#include <functional>

struct MenuOption
{
	std::string id; // unique identifier for the option
	std::string name; // name displayed to user
	std::string description; // optional descritpion of the option
	std::function<void()> action; // lambda function to be executed when the option is selected

	// constructor defaulting id to name
	MenuOption(const std::string& name, const std::string& description, std::function<void()> action)
		: id(name), name(name), description(description), action(std::move(action)) {}

	// constructor allowing custom id
	MenuOption(const std::string& id, const std::string& name, const std::string& description, std::function<void()> action)
		: id(id), name(name), description(description), action(std::move(action)) {
	}
};

class Menu
{
public:

	// default constructor
	Menu();

	// construct a menu where id == name and a description
	Menu(const std::string& name, const std::string& description);

	// construct a menu with a custom id, name and description
	Menu(const std::string& id, const std::string& name, const std::string& description);

	// TODO: maybe change to addOptionById to match the remove one
	// add an option to this menu
	void addOption(const MenuOption& menuOption);

	// remove an option from this menu
	void removeOptionById(const std::string& optionId);

	// getters
	const std::string& getId() const;
	const std::string& getName() const;
	const std::string& getDescription() const;
	const std::vector<MenuOption>& getMenuOptions() const;

	// setters
	void setName(const std::string& newName);
	void setDescription(const std::string& newDescription);

private:
	std::string id;
	std::string name;
	std::string description;
	std::vector<MenuOption> menuOptions;
};