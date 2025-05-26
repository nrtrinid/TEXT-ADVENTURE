#pragma once
#include <string>

enum class ItemType {
	Consumable,
	Key,
	Equipment
};

class Item {
public:
	// constructor where name = id
	Item(std::string name, std::string description, int quantity = 1, ItemType type = ItemType::Consumable)
		: id(name), name(std::move(name)), description(std::move(description)), quantity(quantity), type(type) {
	}
	// constructor with unique id
	Item(std::string id, std::string name, std::string description, int quantity = 1, ItemType type = ItemType::Consumable)
		: name(std::move(name)), description(std::move(description)), quantity(quantity), type(type) {
	}

	// accessors
	const std::string& getName() const { return name; }
	const std::string& getDescription() const { return description; }
	int getQuantity() const { return quantity; }
	ItemType getType() const { return type; }

	void increment(int amount = 1) { quantity += amount; }
	void decrement(int amount = 1) { quantity = (quantity > amount) ? quantity - amount : 0; }

private:
	std::string id;
	std::string name;
	std::string description;
	int quantity;
	ItemType type;
};
