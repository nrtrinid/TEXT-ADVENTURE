#pragma once

#include "Skill.h"
#include <unordered_map>
#include <string>

class SkillRegistry
{
public:
	static const SkillRegistry& instance();
	const Skill& get(const std::string& id) const;
private:
	SkillRegistry();
	std::unordered_map<std::string, Skill> skillTable;
};

