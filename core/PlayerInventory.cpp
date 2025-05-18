#include "PlayerInventory.h"

void PlayerInventory::addItem(const std::string& name, const std::string& description, int quantity, ItemType type) {
	for (auto& i : items) {
		if (i.getName() == name) {
			i.increment(quantity);
			return;
		}
	}
	items.emplace_back(name, description, quantity, type);
}

void PlayerInventory::removeItem(const std::string& name, int quantity) {
	for (auto it = items.begin(); it != items.end(); ++it) {
		if (it->getName() == name) {
			if (it->getQuantity() > quantity) {
				it->decrement(quantity);
			}
			else {
				items.erase(it); // remove if quantity drops to 0 or below
			}
			return;
		}
	}
}

const std::vector<Item>& PlayerInventory::getItems() const {
	return items;
}

int PlayerInventory::getItemCount(const std::string& name) const {
	for (const auto& item : items) {
		if (item.getName() == name) {
			return item.getQuantity();
		}
	}
	return 0; // not found
}