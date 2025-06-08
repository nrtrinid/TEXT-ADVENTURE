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
		std::size_t slotsRequired,
		std::vector<Slot> allowedSlots,
		std::vector<StatModifier> mods,
		UpgradeInfo upgradeInfo = {});

	// defaults slotsRequired to 1
	Equippable(std::string id,
		std::string name,
		std::vector<Slot> allowedSlots,
		std::vector<StatModifier> mods,
		UpgradeInfo upgradeInfo = {});

	const std::vector<Slot>& allowedSlots() const noexcept;
	std::size_t slotsRequired() const noexcept;
	const std::vector<Slot>& occupiedSlots() const noexcept;

	std::string getDescription() const;
	const std::vector<StatModifier>& modifiers() const noexcept;
	const UpgradeInfo& getUpgradeInfo() const noexcept;
	void applyUpgrade();

	std::shared_ptr<Item> clone() const override;

private:
	std::vector<Slot> allowedSlots_;
	std::size_t slotsRequired_;
	std::vector<Slot> occupiedSlots_; // defined at runtime by character, starts empty
	std::vector<StatModifier> modifiers_;
	UpgradeInfo upgradeInfo_;

	friend class Character;
};

