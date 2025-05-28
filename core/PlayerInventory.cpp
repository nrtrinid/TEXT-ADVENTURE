#include "PlayerInventory.h"

void PlayerInventory::addItem(const std::string& itemID, int quantity) {
	for (auto& entry : items) {
		if (entry.itemID == itemID) {
			entry.quantity += quantity;
			return;
		}
	}
	items.push_back({ itemID, quantity });
}

void PlayerInventory::removeItem(const std::string& itemID, int quantity) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		if (it->itemID == itemID) {
			if (it->quantity > quantity) {
				it->quantity -= quantity;
			}
			else {
				items.erase(it); // remove if quantity drops to 0 or below
			}
			return;
		}
	}
}

int PlayerInventory::getItemCount(const std::string& itemID) const {
	for (const auto& entry : items) {
		if (entry.itemID == itemID) {
			return entry.quantity;
		}
	}
	return 0; // not found
}

const std::vector<InventoryEntry>& PlayerInventory::getItems() const {
	return items;
}