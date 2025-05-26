#include "SkillRegistry.h"

SkillRegistry::SkillRegistry() {
	skillTable.emplace("heal spell", Skill{ "heal spell", 30, 5, true, "clarity", {"heal"}});
}

const Skill& SkillRegistry::get(const std::string& id) const {
	return skillTable.at(id);
}

const SkillRegistry& SkillRegistry::instance() {
	static SkillRegistry instance;
	return instance;
}