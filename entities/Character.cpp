#include "Character.h"
#include <algorithm>

Character::Character(std::string id, std::string name, int maxHp, bool isMercenary)
	: id(std::move(id)), name(std::move(name)), hp(maxHp), maxHP(maxHp), mercenary(isMercenary) {}

const std::string& Character::getID() const {
	return id;
}

const std::string& Character::getName() const {
	return name;
}

int Character::getLevel() const {
	return level;
}

int Character::getStat(std::string_view name) const {
	auto it = baseStats.find(std::string(name));
	return it != baseStats.end() ? it->second : 0;
}

// TODO: update this later to change based on stat types and change scaling
int Character::getSkillBonus(int baseMagnitude, std::string_view stat) const {
	return getStat(stat) / 2;
}

int Character::getHP() const {
	return hp;
}

int Character::getMaxHP() const {
	return maxHP;
}

bool Character::isMercenary() const {
	return mercenary;
}

void Character::setHP(int newHP) {
    hp = std::max(0, std::min(newHP, maxHP)); // clamp between 0 and maxHP
}

void Character::setLevel(int newLevel) {
	level = newLevel;
}

void Character::setStat(std::string_view name, int value) {
	baseStats[std::string(name)] = value;
}
void Character::setName(const std::string& newName) {
	name = newName;
}

void Character::setIsMercenary(bool value) {
	mercenary = value;
}

bool Character::isAlive() const {
	return hp > 0;
}