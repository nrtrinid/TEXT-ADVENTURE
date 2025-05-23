#include "PartyMenu.h"
#include "Menu.h"
#include "entities/Party.h"
#include "entities/Character.h"

void registerPartyMenu(MenuRegistry& menuRegistry, GameState& gameState) {
	menuRegistry.addMenuFactory("party", [&gameState]() {
		Menu menu("Party", "Characters currently in your party:", MenuType::System);

		const auto& members = gameState.getParty()->getMembers();

		for (const auto& member : members) {
			std::string label = member->getName();
			std::string description = "HP: " + std::to_string(member->getHP()) + "/" + std::to_string(member->getMaxHP());

			if (member->isMercenary()) {
				description += " (Mercenary)";
			}

			menu.addOption(MenuOption(label, description, [] {
				return CommandList{
					makePrint("Placehholder for future interaction"),
					makePause() 
				};
			}));
		}
			return menu;
	});
}