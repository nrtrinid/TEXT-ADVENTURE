#pragma once

#include "commands/Command.h"

class GameState;
struct MenuNavigator;

class CommandProcessor
{
public:
	CommandProcessor(GameState& gameState, MenuNavigator& menuNavigator)
		: gameState_(gameState), menuNavigator_(menuNavigator) {}
	void executeCommands(const CommandList&);

private:
	GameState& gameState_;
	MenuNavigator& menuNavigator_;
};

