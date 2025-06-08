#include "Equippable.h"
#include <sstream>

Equippable::Equippable(
	std::string id,
	std::string name,
	std::size_t slotsRequired,
	std::vector<Slot> allowedSlots,
	std::vector<StatModifier> modifiers,
	UpgradeInfo upgrade)
	: Item{ std::move(id), std::move(name), "Equippable item.", ItemType::Equippable, "noop", std::nullopt },
	allowedSlots_(std::move(allowedSlots)),
	slotsRequired_(slotsRequired),
	occupiedSlots_(),
	modifiers_(std::move(modifiers)),
	upgradeInfo_(std::move(upgrade)) {}

Equippable::Equippable(
	std::string id,
	std::string name,
	std::vector<Slot> allowedSlots,
	std::vector<StatModifier> modifiers,
	UpgradeInfo upgradeInfo)
	: Equippable(std::move(id),
		std::move(name),
		1,
		std::move(allowedSlots),
		std::move(modifiers),
		std::move(upgradeInfo)) {}

const std::vector<Slot>& Equippable::allowedSlots() const noexcept {
	return allowedSlots_;
}

std::size_t Equippable::slotsRequired() const noexcept {
	return slotsRequired_;
}

const std::vector<Slot>& Equippable::occupiedSlots() const noexcept {
	return occupiedSlots_;
}

std::string Equippable::getDescription() const {
	std::ostringstream out;

	if (!modifiers_.empty()) {
		for (size_t i = 0; i < modifiers_.size(); ++i) {
			const auto& mod = modifiers_[i];

			// add sign and value
			out << (mod.flat >= 0 ? "+" : "") << mod.flat << " " << mod.stat;

			// add comma only if not last
			if (i != modifiers_.size() - 1) {
				out << ", ";
			}
		}
	}
	else {
		out << "No stat bonuses";
	}

	return out.str();
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

std::shared_ptr<Item> Equippable::clone() const {
	return std::make_shared<Equippable>(*this);
}