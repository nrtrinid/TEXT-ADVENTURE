#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "Effect.h"
class EffectRegistry
{
public:
	static const EffectRegistry& instance(); // global accessor

	void registerEffect(const std::string& id, std::unique_ptr<Effect> effect);
	const Effect& get(const std::string& id) const;

	void registerDefaults();

private:
	std::unordered_map<std::string, std::unique_ptr<Effect>> effectTable;
};

