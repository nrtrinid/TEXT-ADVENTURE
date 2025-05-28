#include "SkillCommands.h"
#include "skills/SkillRegistry.h"
#include "systems/SkillSystem.h"
#include "entities/Party.h"

void executeUseSkill(const Command& command, GameState& gameState) {
	const Skill& skill = SkillRegistry::instance().get(command.id);

	auto& party = gameState.getParty();
	auto user = party->getMemberByIndex(0);
	auto target = party->getMemberByIndex(command.targetIndex);

	if (!user || !target) return;

	SkillSystem::execute(skill, *user, *target, gameState);
}
