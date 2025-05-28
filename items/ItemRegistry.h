#pragma once

#include "Item.h"
#include <string>
#include <unordered_map>

class ItemRegistry
{
public:
	static ItemRegistry& instance();

	void registerItem(const Item& item);
	const Item& get(const std::string& id) const;

	void registerDefaults();

private:
	std::unordered_map<std::string, Item> itemTable;
};
