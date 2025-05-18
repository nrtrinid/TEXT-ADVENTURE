#pragma once
#include <vector>
#include "Item.h"

class PlayerInventory {
public:
	void addItem(const std::string& name, const std::string& desc, int quantity = 1, ItemType type = ItemType::Consumable);
	void removeItem(const std::string& name, int quantity = 1);
	const std::vector<Item>& getItems() const;
	int getItemCount(const std::string& name) const;

private:
	std::vector<Item> items;
};
