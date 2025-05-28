#pragma once
#include <vector>
#include "items/Item.h"

struct InventoryEntry {
	std::string itemID;
	int quantity;
};

class PlayerInventory {
public:
	void addItem(const std::string& itemID, int quantity = 1);
	void removeItem(const std::string& itemID, int quantity = 1);
	int getItemCount(const std::string& itemID) const;
	const std::vector<InventoryEntry>& getItems() const;

private:
	std::vector<InventoryEntry> items;
};
