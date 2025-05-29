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

			menu.addOption(MenuOption(label, description, [member] {
				std::string details = member->getName() + "\n";
				details += "HP: " + std::to_string(member->getHP()) + "/" + std::to_string(member->getMaxHP()) + "\n";
				details += "POW: " + std::to_string(member->getStat("power")) + "\n";
				details += "CLAR: " + std::to_string(member->getStat("clarity")) + "\n";
				// Add more stats if desired

				if (member->isMercenary()) {
					details += "(Mercenary)\n";
				}

				return CommandList{
					makePrint(details),
					makePause(),
					makePrint("\033[2J\033[H"), // Clear entire screen after showing stats

				};
				}));
		}
			return menu;
	});
}