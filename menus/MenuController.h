#pragma once

#include "MenuRegistry.h"
#include "core/GameState.h"
#include "commands/Command.h"
#include <string>
#include <vector>

class MenuController
{
public:
	MenuController(MenuRegistry& menuRegistry, GameState& gameState);

	void returnToPreviousMenu();                                            // pops the menu stack and returns to the previous menu

	void setCurrentMenu(const std::string& menuId, bool remember = false);  // set the current menu by name
	
	void displayCurrentMenu(size_t selectedIndex) const;                    // display the current menu

	void processInput(size_t choice);                                       // process the user's input

	const std::string& getCurrentMenuName() const;                          // getter for menu name

	bool wantsToQuit() const;

private:
	bool shouldExit = false;                                    // exit flag to be passed to game loop
	void executeCommands(const std::vector<Command>& commands); // executes a list of commands generated by MenuOption

	MenuRegistry& menuRegistry;                                 // reference to the menu registry
	GameState& gameState;                                       // reference to the game state
	std::string currentMenuName;
	std::vector <std::string> menuStack;                        // stack of previous menu IDs
};