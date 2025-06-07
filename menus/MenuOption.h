#pragma once

#include "commands/Command.h"
#include <string>
#include <vector>
#include <functional>

struct MenuNavigator;

struct MenuOption {
	// color constants
	static constexpr const char* COLOR_RESET = "\033[0m";
	static constexpr const char* COLOR_BOLD = "\033[1m";
	static constexpr const char* COLOR_DIM = "\033[2m";
	static constexpr const char* COLOR_RED = "\033[31m";
	static constexpr const char* COLOR_GREEN = "\033[32m";
	static constexpr const char* COLOR_YELLOW = "\033[33m";
	static constexpr const char* COLOR_CYAN = "\033[36m";

	// fields
	std::string id;                               // unique identifier for the option
	std::string name;                             // name displayed to user
	std::string description;                      // short text shown in the hover box for this option
	std::function<std::vector<Command>(MenuNavigator&)> action; // function that returns commands representing the effects of selecting this option
	std::string colorCode;                        // color duh (empty means default)

	// constructor defaulting id to name
	MenuOption(const std::string& name, const std::string& description, 
		std::function<std::vector<Command>(MenuNavigator&)> action,
		const std::string& colorCode = "")
		: id(name), name(name), description(description), action(std::move(action)), colorCode(colorCode) {}

	// constructor allowing custom id
	MenuOption(const std::string& id, const std::string& name, const std::string& description,
		std::function<std::vector<Command>(MenuNavigator&)> action,
		const std::string& colorCode = "")
		: id(id), name(name), description(description), action(std::move(action)), colorCode(colorCode) {}
};
