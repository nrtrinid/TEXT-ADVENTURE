#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "Effect.h"
class EffectRegistry
{
public:
	static const EffectRegistry& instance(); // global accessor
	const Effect& get(const std::string& id) const;

private:
	EffectRegistry(); // fills table once
	std::unordered_map<std::string, std::unique_ptr<Effect>> effectTable;
};

