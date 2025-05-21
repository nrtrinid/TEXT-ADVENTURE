#pragma once

#include <string>

class Character
{
public:
	Character(std::string id, std::string name, int maxHp, bool isMercenary = false);

	const std::string& getID() const;
	const std::string& getName() const;
	int getHP() const;
	int getMaxHP() const;
	bool isMercenary() const;

	void setHP(int newHp);
	void setName(const std::string& newName);
	void setIsMercenary(bool enabled);

	bool isAlive() const;

private:
	std::string id;
	std::string name;
	int hp;
	int maxHP;
	bool mercenary;
};

