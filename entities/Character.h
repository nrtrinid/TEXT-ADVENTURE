#pragma once

#include "equipment/Slot.h"
#include "equipment/Equippable.h"
#include <unordered_map>
#include <string>
#include <array>
#include <vector>
#include <memory>


class Character
{
public:
	Character(std::string id, std::string name, bool isMercenary = false);

	static constexpr std::size_t SlotCount = static_cast<std::size_t>(Slot::COUNT);

	const std::string& getID() const;
	const std::string& getName() const;
	int getLevel() const;
	int getBaseStat(std::string_view name) const;
	int getStat(std::string_view name) const;
	int getSkillBonus(std::string_view stat) const;
	int getHP() const;
	int getMaxHP() const;
	bool isMercenary() const;

	void setHP(int newHp);
	void setLevel(int newLevel);
	void setStat(std::string_view name, int value);
	void setName(const std::string& newName);
	void setIsMercenary(bool enabled);

	bool isAlive() const;

	void rescaleHP(int oldMax);

	std::vector<std::shared_ptr<Equippable>> equip(const std::shared_ptr<Equippable>& item);
	std::vector<std::shared_ptr<Equippable>> equip(const std::shared_ptr<Equippable>& item, Slot preferred);
	std::shared_ptr<Equippable> unequip(Slot slot);
	bool hasEquipped(Slot slot) const;
	bool isEquipped(std::string_view itemID) const;
	std::shared_ptr<Equippable> getEquipped(Slot slot) const;                                // returns equipment in slot
	const std::array<std::shared_ptr<Equippable>, SlotCount>& getEquipment() const noexcept; // returns private array equipment_
	std::vector < std::shared_ptr<Equippable>> getAllEquipped() const;                      // returns vector of filtered equipment (no duplicates/nullptr)

private:
	std::string id_;
	std::string name_;
	int level_ = 1;
	std::unordered_map<std::string, int> baseStats_{
		{ "resolve", 5 },
		{ "power", 5 },
		{ "tempo", 5 },
		{ "cognition", 5 },
		{ "clarity", 5 },
		{ "presence", 5 }
	};
	int hp_;
	bool mercenary_;
	std::array<std::shared_ptr<Equippable>, SlotCount> equipment_;
};

