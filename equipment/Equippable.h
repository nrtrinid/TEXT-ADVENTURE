#pragma once

#include "items/Item.h"
#include "Slot.h"
#include "StatModifier.h"
#include "UpgradeInfo.h"

#include <string>
#include <vector>

class Equippable : public Item {
public:
	Equippable(std::string id,
		std::string name,
		std::vector<Slot> requiredSlots,
		std::vector<StatModifier> mods,
		UpgradeInfo upgradeInfo = {});

	const std::vector<Slot>& getRequiredSlots() const noexcept;
	const std::vector<StatModifier>& modifiers() const noexcept;
	const UpgradeInfo& getUpgradeInfo() const noexcept;
	void applyUpgrade();

private:
	std::vector<Slot> requiredSlots_;
	std::vector<StatModifier> modifiers_;
	UpgradeInfo upgradeInfo_;
};

