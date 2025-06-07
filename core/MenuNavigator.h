#pragma once

#include <memory>
#include <string>
class Menu;

struct MenuNavigator {
	virtual void pushMenu(std::shared_ptr<Menu>) = 0;
	virtual void popMenu() = 0;
	virtual void gotoMenu(const std::string& id, bool remember = false) = 0;
	virtual ~MenuNavigator() = default;
};