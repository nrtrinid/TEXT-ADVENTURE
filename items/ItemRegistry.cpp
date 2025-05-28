#include "ItemRegistry.h"
#include <stdexcept>

ItemRegistry& ItemRegistry::instance() {
	static ItemRegistry instance;
	instance.registerDefaults();
	return instance;
}

void ItemRegistry::registerItem(const Item& item) {
	itemTable[item.id] = item;
}

const Item& ItemRegistry::get(const std::string& id) const {
	auto it = itemTable.find(id);
	if (it == itemTable.end()) {
		throw std::runtime_error("Item not found: " + id);
	}
	return it->second;
}

void ItemRegistry::registerDefaults() {
	registerItem({
		"potion",
		"Potion",
		"Heals 10 HP",
		ItemType::Consumable,
		"heal",
		10
		});

	registerItem({
		"elixir",
		"Elixir",
		"Restores all HP",
		ItemType::Consumable,
		"heal",
		9999
		});

	// key items

	registerItem({
		"attic_key",
		"Attic Key",
		"Looks useful...",
		ItemType::Key,
		"noop",
		std::nullopt
		});

	registerItem({
		"crystal",
		"Crystal",
		"Emits a low hum",
		ItemType::Key,
		"noop",
		std::nullopt
		});
}