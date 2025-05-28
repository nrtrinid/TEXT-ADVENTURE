#pragma once

#include "ItemType.h"
#include <string>
#include <optional>

struct Item {
	std::string id;
	std::string name;
	std::string description;
	ItemType type = ItemType::Consumable;
	std::string effectID;
	std::optional<int> magnitudeOverride;
};