#pragma once

#include <unordered_map>
#include <string>

class Character
{
public:
	Character(std::string id, std::string name, int maxHp, bool isMercenary = false);

	const std::string& getID() const;
	const std::string& getName() const;
	int getLevel() const;
	int getStat(std::string_view name) const;
	int getSkillBonus(int baseMagnitude, std::string_view stat) const;
	int getHP() const;
	int getMaxHP() const;
	bool isMercenary() const;

	void setHP(int newHp);
	void setLevel(int newLevel);
	void setStat(std::string_view name, int value);
	void setName(const std::string& newName);
	void setIsMercenary(bool enabled);

	bool isAlive() const;

private:
	std::string id;
	std::string name;
	int level = 1;
	std::unordered_map<std::string, int> baseStats{
		{ "resolve", 5 },
		{ "power", 5 },
		{ "tempo", 5 },
		{ "cognition", 5 },
		{ "clarity", 5 },
		{ "presence", 5 }
	};
	int hp;
	int maxHP;
	bool mercenary;
};

