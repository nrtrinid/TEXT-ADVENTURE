#include "SkillRegistry.h"
#include <stdexcept>

const SkillRegistry& SkillRegistry::instance() {
	static SkillRegistry instance;
	instance.registerDefaults();
	return instance;
}

void SkillRegistry::registerSkill(const Skill& skill) {
	skillTable[skill.id] = skill;
}

const Skill& SkillRegistry::get(const std::string& id) const {
	auto it = skillTable.find(id);
	if (it == skillTable.end()) {
		throw std::runtime_error("Skill not found:" + id);
	}
	return it->second;
}

void SkillRegistry::registerDefaults() {
	registerSkill({ "heal_spell", 30, 5, true, "clarity", { "heal" } });
}