#include "Character.h"
#include <algorithm>
#include <unordered_set>

Character::Character(std::string id, std::string name, bool isMercenary)
	: id_(std::move(id)), name_(std::move(name)), mercenary_(isMercenary) {
	hp_ = getMaxHP();
}

const std::string& Character::getID() const {
	return id_;
}

const std::string& Character::getName() const {
	return name_;
}

int Character::getLevel() const {
	return level_;
}

int Character::getBaseStat(std::string_view name) const {
	auto it = baseStats_.find(std::string(name));
	return it != baseStats_.end() ? it->second : 0;
}

int Character::getStat(std::string_view name) const {
	int total = getBaseStat(name);

	for (const auto& equipped : getAllEquipped()) {
		for (const auto& modifier : equipped->modifiers()) {
			if (modifier.stat == name) {
				total += modifier.flat;
			}
		}
	}

	return total;
}

// TODO: update this later to change based on stat types and change scaling
int Character::getSkillBonus(std::string_view stat) const {
	int scalingStat = getStat(stat);
	float multiplier =
		(stat == "power") ? 0.4f :    // less effective for brute strength
		(stat == "tempo") ? 0.7f :    // better scaling for finesse
		0.5f;                         // default fallback
	return static_cast<int>(scalingStat * multiplier);
}

int Character::getHP() const {
	return hp_;
}

int Character::getMaxHP() const {
	return getStat("resolve") * 2;
}

bool Character::isMercenary() const {
	return mercenary_;
}

void Character::setHP(int newHP) {
    hp_ = std::max(0, std::min(newHP, getMaxHP())); // clamp between 0 and maxHP
}

void Character::setLevel(int newLevel) {
	level_ = newLevel;
}

void Character::setStat(std::string_view name, int value) {
	int oldMax = getMaxHP();
	baseStats_[std::string(name)] = value;
	if (name == "resolve") {
		rescaleHP(oldMax);
	}
}
void Character::setName(const std::string& newName) {
	name_ = newName;
}

void Character::setIsMercenary(bool value) {
	mercenary_ = value;
}

bool Character::isAlive() const {
	return hp_ > 0;
}

void Character::rescaleHP(int oldMax) {
	if (oldMax <= 0) {
		setHP(getMaxHP()); // fallback if oldMax is zero (avoid divide-by-zero)
		return;
	}

	float ratio = static_cast<float>(hp_) / static_cast<float>(oldMax);
	int newMax = getMaxHP();
	int newHP = static_cast<int>(std::round(ratio * newMax));

	setHP(newHP); // this will auto-clamp if needed
}


std::vector<std::shared_ptr<Equippable>> Character::equip(const std::shared_ptr<Equippable>& item) {
	if (!item) return {};

	int oldMax = getMaxHP();

	const auto& requiredSlots = item->getRequiredSlots();
	std::unordered_set<std::shared_ptr<Equippable>> toUnequip;

	// gather all conflicting items
	for (Slot slot : requiredSlots) {
		std::size_t index = static_cast<std::size_t>(slot);
		if (equipment_[index]) {
			toUnequip.insert(equipment_[index]);
		}
	}

	// unequip them
	for (const auto& equipped : toUnequip) {
		for (Slot slot : equipped->getRequiredSlots()) {
			std::size_t index = static_cast<std::size_t>(slot);
			if (equipment_[index] == equipped) {
				equipment_[index] = nullptr;
			}
		}
	}

	// equip new item
	for (Slot slot : requiredSlots) {
		std::size_t index = static_cast<std::size_t>(slot);
		equipment_[index] = item;
	}
	rescaleHP(oldMax);

	return std::vector<std::shared_ptr<Equippable>>(toUnequip.begin(), toUnequip.end());
}

std::shared_ptr<Equippable> Character::unequip(Slot slot) {
	int oldMax = getMaxHP();

	std::size_t index = static_cast<std::size_t>(slot);
	std::shared_ptr<Equippable> removed = equipment_[index];
	if (!removed) return nullptr;

	for (Slot slot : removed->getRequiredSlots()) {
		std::size_t index = static_cast<std::size_t>(slot);
		if (equipment_[index] == removed) {
			equipment_[index] = nullptr;
		}
	}
	
	rescaleHP(oldMax);

	return removed;
}

bool Character::hasEquipped(Slot slot) const {
	std::size_t index = static_cast<std::size_t>(slot);
	return equipment_[index] != nullptr;
}

bool Character::isEquipped(std::string_view itemID) const {
	for (const auto& equipped : equipment_) {
		if (equipped && equipped->id == itemID) {
			return true;
		}
	}
	return false;
}


std::shared_ptr<Equippable> Character::getEquipped(Slot slot) const {
	std::size_t index = static_cast<std::size_t>(slot);
	return equipment_[index];
}

const std::array<std::shared_ptr<Equippable>, Character::SlotCount>& Character::getEquipment() const noexcept {
	return equipment_;
}

std::vector<std::shared_ptr<Equippable>> Character::getAllEquipped() const {
	std::vector<std::shared_ptr<Equippable>> equipped;

	for (const auto& item : equipment_) {
		if (item && std::find(equipped.begin(), equipped.end(), item) == equipped.end()) {
			equipped.push_back(item); // avoids duplicates from multi-slot gear
		}
	}

	return equipped;
}