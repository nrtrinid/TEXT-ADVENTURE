#pragma once

#include "skills/SkillRegistry.h"
#include "systems/SkillSystem.h"
#include "effects/EffectRegistry.h"
#include "core/GameState.h"
#include "entities/Character.h"

namespace SkillSystem {

	inline int computeSkillMagnitude(const Character& character, int baseMagnitude, std::string_view scalingStat) {
		return baseMagnitude + character.getSkillBonus(baseMagnitude, scalingStat);
	}

	inline void execute(const Skill& skill, Character& caster, Character& target, GameState& gameState) {
		int magnitude = skill.baseMagnitude;
		if (!skill.scalingStat.empty() && skill.usesSkillBonus)
			magnitude = SkillSystem::computeSkillMagnitude(caster, magnitude, skill.scalingStat);

		for (const auto& id : skill.effectIDs)
			EffectRegistry::instance().get(id).apply(gameState, caster, target, magnitude);
	}
}