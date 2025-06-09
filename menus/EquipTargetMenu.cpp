#include "EquipTargetMenu.h"
#include "entities/Character.h"
#include "core/MenuNavigator.h"
#include "TargetMenu.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <cassert>

Menu buildEquipTargetMenu(std::shared_ptr<Equippable> item, GameState& gameState) {
	
	// small helper to pick which slot to use on a given character
	// if there's a free slot, return that, otherwise pick first allowed
	auto chooseSlot = [item](const Character& character) -> Slot {
		for (Slot slot : item->allowedSlots())
			if (!character.hasEquipped(slot))
				return slot;
		return item->allowedSlots().front();
	};

	// fill out TargetSpec
	TargetSpec spec;

	spec.canSelect = [&](const Character& character) {
		return character.isAlive();
	};

	spec.makeLabel = [&](const Character& character, int index) {
		std::string label = character.getName();

		// figure out which slot (anchor) we'd use, then build toConsume list
		Slot anchor = chooseSlot(character);
		std::vector<Slot> toConsume{ anchor };

		if (item->slotsRequired() == 2) {
			Slot other = (anchor == Slot::Mainhand)
				? Slot::Offhand
				: Slot::Mainhand;
			toConsume.push_back(other);
		}

		// gather names of items in those slots
		std::vector<std::string> replaced;
		for (Slot slot : toConsume) {
			if (auto equipped = character.getEquipped(slot))
				replaced.push_back(equipped->name);
		}

		// if there's anything in replaced, append those names to the lable
		if (!replaced.empty()) {
			label += " (";
			for (size_t i = 0; i < replaced.size(); ++i) {
				if (i) label += ", ";
				label += replaced[i];
			}
			label += ")";
		}
		
		return label;
	};

	spec.makeDescription = [item](const Character&, int) {
		return item->getDescription();
	};

	spec.makeAction = [item, chooseSlot, &gameState](int index) {
		auto& member = *gameState.getParty()->getMembers()[index];
		Slot slot = chooseSlot(member);
		return CommandList{
			makeEquipItem(item->id, index, slot),
			makePause(),
			makePopMenu()
		};
	};


	spec.allowEmpty = false;

	return buildTargetMenu(
		"Choose Character",
		"Select who should equip: " + item->name,
		spec,
		gameState
	);
}
