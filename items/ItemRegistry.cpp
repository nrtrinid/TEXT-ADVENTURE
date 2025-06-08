#include "ItemRegistry.h"
#include "equipment/Equippable.h"
#include <stdexcept>

ItemRegistry& ItemRegistry::instance() {
	static ItemRegistry instance;
	instance.registerDefaults();
	return instance;
}

void ItemRegistry::registerItem(std::shared_ptr<Item> item) {
	itemTable_[item->id] = std::move(item);
}

std::shared_ptr<Item> ItemRegistry::get(const std::string& id) const {
	auto it = itemTable_.find(id);
	if (it == itemTable_.end()) {
		throw std::runtime_error("Item not found: " + id);
	}
	return it->second;
}

std::shared_ptr<Item> ItemRegistry::tryGet(const std::string& id) const {
    auto it = itemTable_.find(id);
    return it == itemTable_.end() ? nullptr : it->second;
}

std::shared_ptr<Equippable> ItemRegistry::getEquippable(const std::string& id) const {
    auto base = tryGet(id);
    return std::dynamic_pointer_cast<Equippable>(base);
}



void ItemRegistry::registerDefaults() {

    //--------------------------------------
    //  Consumables
    //--------------------------------------
    registerItem(std::make_shared<Item>(
        "potion", "Potion", "Heals 10 HP",
        ItemType::Consumable, "heal", 10
    ));

    registerItem(std::make_shared<Item>(
        "elixir", "Elixir", "Restores all HP",
        ItemType::Consumable, "heal", 9999
    ));

    //--------------------------------------
    //  Key items
    //--------------------------------------
    registerItem(std::make_shared<Item>(
        "attic_key", "Attic Key", "Looks useful...",
        ItemType::Key, "noop", std::nullopt
    ));
    registerItem(std::make_shared<Item>(
        "crystal", "Crystal", "Emits a low hum",
        ItemType::Key, "noop", std::nullopt
    ));

    //--------------------------------------
    //  Equippables  (full prototypes)
    //--------------------------------------
    registerItem(std::make_shared<Equippable>(
        "leather_jerkin",
        "Leather Jerkin",
        std::vector<Slot>{ Slot::Armor },
        std::vector<StatModifier>{ { "resolve", +2 } },
        UpgradeInfo{ 0, 3 }
    ));
    
    registerItem(std::make_shared<Equippable>(
        "iron_sword",
        "Iron Sword",
        std::vector<Slot>{ Slot::Mainhand, Slot::Offhand },
        std::vector<StatModifier>{ { "power", +3 } },
        UpgradeInfo{ 0, 5 }
    ));

    registerItem(std::make_shared<Equippable>(
        "life_gem",
        "Life Gem",
        std::vector<Slot>{ Slot::Mainhand, Slot::Offhand },
        std::vector<StatModifier>{ { "clarity", +2 } },
        UpgradeInfo{ 0, 3 }
    ));

    registerItem(std::make_shared<Equippable>(
        "greatsword",
        "Greatsword",
        2,
        std::vector<Slot> { Slot::Mainhand },
        std::vector<StatModifier>{ { "power", +6 }, {"resolve", +2} },
        UpgradeInfo{ 0, 5 }
    ));
}