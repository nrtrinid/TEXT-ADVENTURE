#include "PartyMenu.h"
#include "CharacterMenu.h"
#include "Menu.h"
#include "core/MenuNavigator.h"
#include "entities/Party.h"
#include "entities/Character.h"
#include "equipment/Equippable.h"
#include "equipment/Slot.h"
#include <iostream>

void registerPartyMenu(MenuRegistry& menuRegistry, GameState& gameState) {
    menuRegistry.addMenuFactory("party", [&menuRegistry, &gameState]() {
        Menu menu("Party", "Characters currently in your party:", MenuType::System);

        // grab the vector< shared_ptr<Character> >
        const auto& members = gameState.getParty()->getMembers();

        for (size_t i = 0; i < members.size(); ++i) {
            const auto& member = members[i];
            std::string menuID = "char_" + member->getID();

            if (!menuRegistry.hasMenu(menuID)) {
                registerCharacterMenu(menuRegistry, gameState, member);

            }

            std::string label = member->getName();
            std::string description =
                "HP: " + std::to_string(member->getHP()) +
                "/" + std::to_string(member->getMaxHP());
            if (member->isMercenary()) {
                description += " (Mercenary)";
            }

            menu.addOption(MenuOption(label, description, [member](MenuNavigator& menuNavigator) {
                menuNavigator.gotoMenu("char_" + member->getID(), true);
                return CommandList{};
                }
            ));
        }
			return menu;
	});
}