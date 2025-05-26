#pragma once

#include <string>
#include <vector>

struct Skill {
	std::string id;
	int baseMagnitude = 0;
	int mpCost = 0;
	bool usesSkillBonus = false;
	std::string scalingStat;
	std::vector<std::string> effectIDs;
};