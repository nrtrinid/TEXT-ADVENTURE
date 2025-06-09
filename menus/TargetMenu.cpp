#include "TargetMenu.h"
#include "entities/Party.h"
#include "core/GameState.h"

Menu buildTargetMenu(const std::string& name, const std::string& description, const TargetSpec& spec, GameState& gameState) {
	Menu menu(name, description, MenuType::System);

	const auto& party = gameState.getParty()->getMembers();

	for (int index = 0; index < static_cast<int>(party.size()); ++index) {
		const auto& character = *party[index];
		if (!spec.canSelect(character)) continue;

		auto actionFunction = spec.makeAction;

		menu.addOption(MenuOption{ spec.makeLabel(character, index), spec.makeDescription(character,index), [actionFunction, index](MenuNavigator&) {
			return actionFunction(index);
		}
		});
	}

	if (menu.getMenuOptions().empty() && !spec.allowEmpty) {
		menu.addOption(MenuOption("-- no valid targets --", "", [](MenuNavigator&) { return CommandList{ makePopMenu() };  }));
	}

	return menu;
}
