#pragma once

#include "Skill.h"
#include <unordered_map>
#include <string>

class SkillRegistry
{
public:
	static const SkillRegistry& instance();

	void registerSkill(const Skill& skill);
	const Skill& get(const std::string& id) const;

	void registerDefaults();
private:
	std::unordered_map<std::string, Skill> skillTable;
};

