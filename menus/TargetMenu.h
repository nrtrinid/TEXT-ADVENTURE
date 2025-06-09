#pragma once

#include <functional>
#include <string>
#include "Menu.h"
#include "commands/Command.h"

class Character;
class GameState;

struct TargetSpec {
	using Predicate = std::function<bool(const Character&)>;
	using LabelFunction = std::function<std::string(const Character&, int)>;
	using DescriptionFunction = std::function<std::string(const Character&, int)>;
	using ActionFunction = std::function<CommandList(int)>;

	Predicate canSelect;
	LabelFunction makeLabel;
	DescriptionFunction makeDescription;
	ActionFunction makeAction;
	bool allowEmpty = false;
};

Menu buildTargetMenu(const std::string& name, const std::string& description, const TargetSpec& spec, GameState& gameState);
