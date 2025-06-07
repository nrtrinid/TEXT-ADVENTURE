#include "Equippable.h"
#include <sstream>

Equippable::Equippable(std::string id, std::string name, std::vector<Slot> requiredSlots,
	std::vector<StatModifier> mods, UpgradeInfo upgrade)
	: Item{ std::move(id), std::move(name), "Equippable item.", ItemType::Equippable, "noop", std::nullopt },
	requiredSlots_(std::move(requiredSlots)),
	modifiers_(std::move(mods)),
	upgradeInfo_(std::move(upgrade)) {}


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