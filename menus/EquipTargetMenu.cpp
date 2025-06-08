#include "EquipTargetMenu.h"
#include "entities/Character.h"
#include "core/MenuNavigator.h"
#include <memory>
#include <string>
#include <unordered_set>

Menu buildEquipTargetMenu(std::shared_ptr<Equippable> item, GameState& gameState) {
	Menu menu("Choose Character", "Select who should equip: " + item->name, MenuType::System);

	const auto& party = gameState.getParty()->getMembers();
    for (size_t i = 0; i < party.size(); ++i) {
        const auto& member = party[i];
        int memberIndex = static_cast<int>(i);

        std::string label = member->getName();
		std::string desc = item->getDescription();

		std::optional<Slot> usableSlot;
		for (Slot slot : item->allowedSlots()) {
			if (!member->hasEquipped(slot)) {
				usableSlot = slot;
				break;
			}
		}

		if (usableSlot) {
			// normal case: found a free slot
			menu.addOption(MenuOption(
				label,
				desc,
				[item, memberIndex, usableSlot = *usableSlot](MenuNavigator&) {
					return CommandList{
						makeEquipItem(item->id, memberIndex, usableSlot),
						makePause(),
						makePopMenu()
					};
				}));
		}
		else {
			// Collect what will be replaced
			std::unordered_set<std::shared_ptr<Equippable>> toReplace;

			// Pick a default anchor slot
			Slot anchor = item->allowedSlots().front();

			// Compute the slots that will be consumed
			std::vector<Slot> toConsume{ anchor };
			if (item->slotsRequired() == 2) {
				Slot second = (anchor == Slot::Mainhand) ? Slot::Offhand : Slot::Mainhand;
				toConsume.push_back(second);
			}

			for (Slot s : toConsume) {
				auto eq = member->getEquipped(s);
				if (eq) toReplace.insert(eq);
			}

			// Build a string like "(Life Gem, Iron Sword)"
			std::string replaceNote;
			if (!toReplace.empty()) {
				replaceNote = " (";
				bool first = true;
				for (const auto& eq : toReplace) {
					if (!first) replaceNote += ", ";
					replaceNote += eq->name;
					first = false;
				}
				replaceNote += ")";
			}

			menu.addOption(MenuOption(
				label + replaceNote,
				desc,
				[item, memberIndex, anchor](MenuNavigator&) {
					return CommandList{
						makeEquipItem(item->id, memberIndex, anchor),
						makePause(),
						makePopMenu()
					};
				}));
		}

    }

	return menu;
}