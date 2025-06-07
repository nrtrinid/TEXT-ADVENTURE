#pragma once

#include "Item.h"
#include <memory>
#include <string>
#include <unordered_map>

class Equippable;

class ItemRegistry
{
public:
	static ItemRegistry& instance();

	void registerItem(std::shared_ptr<Item> item);
	std::shared_ptr<Item> get(const std::string& id) const;
	std::shared_ptr<Item> tryGet(const std::string& id) const;
	std::shared_ptr<Equippable> getEquippable(const std::string& id) const;

	void registerDefaults();

private:
	std::unordered_map<std::string, std::shared_ptr<Item>> itemTable_;
};
