#include "CharacterMenu.h"
#include "EquipSlotMenu.h"
#include "Menu.h"
#include "MenuRegistry.h"
#include "core/MenuNavigator.h"
#include "core/GameState.h"
#include "entities/Character.h"
#include "equipment/Slot.h"
#include <sstream>
#include <iomanip>

void registerCharacterMenu(MenuRegistry& menuRegistry, GameState& gameState, const std::shared_ptr<Character>& character) {
	const std::string menuID = "char_" + character->getID();

	menuRegistry.addMenuFactory(menuID, [character, &gameState]() {
		// description block
		std::ostringstream description;
		description << "HP: " << character->getHP() << "/" << character->getMaxHP() << '\n';

		description << "RES " << character->getStat("resolve") << " | "
			<< "POW " << character->getStat("power") << " | "
			<< "TMP " << character->getStat("tempo") << '\n';

		description << "COG " << character->getStat("cognition") << " | "
			<< "CLR " << character->getStat("clarity") << " | "
			<< "PRE " << character->getStat("presence");

		if (character->isMercenary()) description << "(Mercenary)\n";

		Menu menu("char_" + character->getID(), character->getName(), description.str(), MenuType::System);

		const auto& equipment = character->getEquipment();

		// alignment buffer
		size_t maxSlotWidth = 0;
		for (int i = 0; i < Character::SlotCount; ++i) {
			Slot s = static_cast<Slot>(i);
			maxSlotWidth = std::max(maxSlotWidth, std::string(slotToString(s)).length());
		}

		for (int i = 0; i < Character::SlotCount; ++i) {
			Slot slot = static_cast<Slot>(i);
			std::string itemName = equipment[i] ? equipment[i]->name : "None";
			std::string itemDescription = equipment[i] ? equipment[i]->getDescription() : "Nothing is equipped here.";

			std::ostringstream labelStream;
			labelStream << std::left << std::setw(static_cast<int>(maxSlotWidth + 1))
				<< slotToString(slot) << ": " << itemName;

			std::string label = labelStream.str();

			menu.addOption(MenuOption(label,
				equipment[i] ? equipment[i]->getDescription()
				: "Equip an item to this slot",
				[character, slot, &gameState](MenuNavigator& nav) {
					int index = gameState.getParty()->getIndexOf(character);
					if (index < 0) {
						return CommandList{ makePrint("Error: Character not found.") };
					}

					nav.pushMenu(std::make_shared<Menu>(
						buildEquipSlotMenu(index, slot, gameState)
					));
					return CommandList{};
				}
			));
		}
		return menu;
				});
}