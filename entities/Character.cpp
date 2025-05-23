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

void Character::setName(const std::string& newName) {
	name = newName;
}

void Character::setIsMercenary(bool value) {
	mercenary = value;
}

bool Character::isAlive() const {
	return hp > 0;
}