#include "EffectRegistry.h"
#include "HealEffect.h"

EffectRegistry::EffectRegistry() {
	effectTable.emplace("heal", std::make_unique<HealEffect>());
}

const Effect& EffectRegistry::get(const std::string& id) const {
	return *effectTable.at(id);
}

const EffectRegistry& EffectRegistry::instance() {
	static EffectRegistry instance;
	return instance;
}
