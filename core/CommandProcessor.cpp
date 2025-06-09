#include "CommandProcessor.h"
#include "GameState.h"
#include "MenuNavigator.h"
#include "commands/ItemCommands.h"
#include "commands/SkillCommands.h"
#include <iostream>

void CommandProcessor::executeCommands(const CommandList& commands) {
	for (const auto& command : commands) {
		switch (command.type) {
		case Command::Type::Print: std::cout << command.text; break;
		case Command::Type::Pause: std::cin.get(); break;
		case Command::Type::SetFlag: gameState_.setFlag(command.flag, command.enabled); break;
		case Command::Type::GotoMenu: menuNavigator_.gotoMenu(command.target, command.enabled);  break;
		case Command::Type::PopMenu: menuNavigator_.popMenu(); break;
		case Command::Type::PushMenu: menuNavigator_.pushMenu(command.menu); break;
		case Command::Type::QuitGame: gameState_.requestQuit(); break;
		case Command::Type::AddItem: executeAddItem(command, gameState_); break;
		case Command::Type::RemoveItem: executeRemoveItem(command, gameState_); break;
		case Command::Type::EquipItem: gameState_.equipItem(command.id, command.targetIndex, *command.slot); break;
		case Command::Type::UnequipItem: gameState_.unequipSlot(command.targetIndex, *command.slot); break;
		case Command::Type::UseItem: executeUseItem(command, gameState_); break;
		case Command::Type::UseSkill: executeUseSkill(command, gameState_); break;
		}
	}
}