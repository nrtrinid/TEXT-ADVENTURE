#pragma once

#include "Item.h"
#include <string>
#include <vector>

struct Command {
	enum class Type { Print, Pause, SetFlag, GotoMenu, PopMenu, AddItem, RemoveItem, UseItem};

	Type type;
	std::string text;   // Print uses this
	std::string target; // GotoMenu uses this
	std::string flag;   // SetFlag uses this
	bool enabled{};     // the actual SetFlag

	std::string itemName;
	std::string itemDescription;
	int itemQuantity = 1;
	ItemType itemType = ItemType::Consumable;
};

using CommandList = std::vector<Command>; // alias for vector of commands

// helper constructors for common commands

inline Command makePrint(const std::string& text) {
	return { Command::Type::Print, text };
}

inline Command makePause() {
	return { Command::Type::Pause };
}

inline Command makeGotoMenu(const std::string& targetMenu, bool remember = false) {
	Command command{ Command::Type::GotoMenu };
	command.target = targetMenu;
	command.enabled = remember;
	return command;
}

inline Command makeSetFlag(const std::string& flagName, bool enabled = true) {
	return { Command::Type::SetFlag, "", "", flagName, enabled };
}

inline Command makePopMenu() {
	return Command{ Command::Type::PopMenu };
}

inline Command makeAddItem(const std::string& name, const std::string& description, int quantity = 1, ItemType type = ItemType::Consumable) {
	Command command{ Command::Type::AddItem };
	command.itemName = name;
	command.itemDescription = description;
	command.itemQuantity = quantity;
	command.itemType = type;
	return command;
}

inline Command makeAddItem(const std::string& name, const std::string& description, ItemType type) {
	return makeAddItem(name, description, 1, type);
}

inline Command makeRemoveItem(const std::string& name, int quantity = 1) {
	Command command{ Command::Type::RemoveItem };
	command.itemName = name;
	command.itemQuantity = quantity;
	return command;
}

inline Command makeUseItem(const std::string& itemName) {
	Command command = { Command::Type::UseItem };
	command.itemName = itemName;
	return command;
}
