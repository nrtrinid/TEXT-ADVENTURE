#pragma once

#include "commands/Command.h"
#include <string>
#include <vector>
#include <functional>

struct MenuOption {
	std::string id;                               // unique identifier for the option
	std::string name;                             // name displayed to user
	std::string description;                      // short text shown in the hover box for this option
	std::function<std::vector<Command>()> action; // function that returns commands representing the effects of selecting this option

	// constructor defaulting id to name
	MenuOption(const std::string& name, const std::string& description, std::function<std::vector<Command>()> action)
		: id(name), name(name), description(description), action(std::move(action)) {}

	// constructor allowing custom id
	MenuOption(const std::string& id, const std::string& name, const std::string& description, std::function<std::vector<Command>()> action)
		: id(id), name(name), description(description), action(std::move(action)) {}
};
