#include "EffectRegistry.h"
#include "HealEffect.h"
#include "NoopEffect.h"
#include <stdexcept>

const EffectRegistry& EffectRegistry::instance() {
	static EffectRegistry instance;
	instance.registerDefaults();
	return instance;
}

void EffectRegistry::registerEffect(const std::string& id, std::unique_ptr<Effect> effect) {
	effectTable[id] = std::move(effect);
}

const Effect& EffectRegistry::get(const std::string& id) const {
	auto it = effectTable.find(id);
	if (it == effectTable.end()) {
		throw std::runtime_error("Effect not found: " + id);
	}
	return *(it->second);
}

void EffectRegistry::registerDefaults() {
	registerEffect("heal", std::make_unique<HealEffect>());
	registerEffect("noop", std::make_unique<NoopEffect>());
}
