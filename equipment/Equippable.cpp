#include "Equippable.h"

Equippable::Equippable(std::string id, std::string name, std::vector<Slot> requiredSlots, std::vector<StatModifier> mods, UpgradeInfo upgrade)
	: requiredSlots_(std::move(requiredSlots)),
	modifiers_(std::move(mods)),
	upgradeInfo_(std::move(upgrade)) 
{
	this->id = std::move(id);
	this->name = std::move(name);
	this->type = ItemType::Equippable;

	// might delete later?
	this->description = "Equippable item.";
	this->effectID = "noop";
}

const std::vector<Slot>& Equippable::getRequiredSlots() const noexcept {
	return requiredSlots_;
}

const std::vector<StatModifier>& Equippable::modifiers() const noexcept {
	return modifiers_;
}

const UpgradeInfo& Equippable::getUpgradeInfo() const noexcept {
	return upgradeInfo_;
}

void Equippable::applyUpgrade() {
	if (upgradeInfo_.level < upgradeInfo_.maxLevel) {
		upgradeInfo_.level++;
	}
}