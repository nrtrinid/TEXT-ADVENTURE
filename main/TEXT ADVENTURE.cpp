// TEXT ADVENTURE 2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "menus/Menu.h"
#include "menus/MenuRegistry.h"
#include "menus/MenuController.h"
#include "menus/MenuSetup.h"
#include "core/GameState.h"

#include <conio.h>  // For _getch()

// forward declarations


int main()
{
	GameState gameState;

	MenuRegistry menuRegistry;
	MenuController menuController(menuRegistry, gameState);

	bool running = true;
	bool clearScreen = true;
	size_t selectedIndex = 0;

	registerMenus(menuRegistry, menuController, gameState);

	menuController.setCurrentMenu("old mansion");

	while (running) {
		if (clearScreen) std::cout << "\x1B[10A"; // clear screen

		menuController.displayCurrentMenu(selectedIndex);

		// Handle input
		int key = _getch();

		if (key == 'q') {
			running = false;
		}
		else if (key == 224) { // arrow keys
			int arrow = _getch();
			if (arrow == 72 && selectedIndex > 0) {
				--selectedIndex;
			}
			else if (arrow == 80 && selectedIndex < menuRegistry.getMenu(menuController.getCurrentMenuName()).getMenuOptions().size() - 1) {
				++selectedIndex;
			}
		}
		else if (key == '\r') {
			system("cls");
			menuController.processInput(selectedIndex + 1);
			selectedIndex = 0; // reset selection after action
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
