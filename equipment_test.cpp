#include <iostream>
#include <memory>
#include "entities/Character.h"
#include "equipment/Equippable.h"
#include "equipment/Slot.h"

void testSlotReplacement() {
	std::cout << "\n== Slot Replacement ==\n";
	Character c("id", "TestChar");
	c.setStat("resolve", 10);

	auto helm1 = std::make_shared<Equippable>(
		"helm1", "Helmet +5",
		std::vector<Slot>{Slot::Helmet},
		std::vector<StatModifier>{{"resolve", 5}},
		UpgradeInfo{}
	);

	auto helm2 = std::make_shared<Equippable>(
		"helm2", "Helmet +10",
		std::vector<Slot>{Slot::Helmet},
		std::vector<StatModifier>{{"resolve", 10}},
		UpgradeInfo{}
	);

	c.equip(helm1);
	std::cout << "Equipped +5 helmet. Resolve: " << c.getStat("resolve") << "\n";

	auto replaced = c.equip(helm2);
	std::cout << "Equipped +10 helmet. Resolve: " << c.getStat("resolve") << "\n";
	std::cout << "Replaced " << replaced.size() << " item(s):\n";
	for (const auto& item : replaced)
		std::cout << "- " << item->name << "\n";
}


void testMultiSlotEquip() {
	std::cout << "\n== Multi-slot Equip ==\n";
	Character c("id", "DualWielder");
	c.setStat("resolve", 10);

	auto greatsword = std::make_shared<Equippable>(
		"gsword", "Greatsword",
		std::vector<Slot>{Slot::Mainhand, Slot::Offhand},
		std::vector<StatModifier>{{"resolve", 8}},
		UpgradeInfo{}
	);

	auto replaced = c.equip(greatsword);
	std::cout << "Resolve after equipping greatsword: " << c.getStat("resolve") << "\n";
	std::cout << "Replaced " << replaced.size() << " item(s).\n";

	// Try equipping dagger to Mainhand again
	auto dagger = std::make_shared<Equippable>(
		"dagger", "Dagger",
		std::vector<Slot>{Slot::Mainhand},
		std::vector<StatModifier>{{"resolve", 2}},
		UpgradeInfo{}
	);

	auto replaced2 = c.equip(dagger);
	std::cout << "After attempting dagger equip:\n";
	std::cout << "Resolve: " << c.getStat("resolve") << "\n";
	std::cout << "Replaced " << replaced2.size() << " item(s):\n";
	for (const auto& item : replaced2)
		std::cout << "- " << item->name << "\n";
}

void testNegativeStat() {
	std::cout << "\n== Negative Modifier ==\n";
	Character c("id", "CursedOne");
	c.setStat("resolve", 10);
	c.setHP(20); // half health

	auto cursedHelm = std::make_shared<Equippable>(
		"curse", "Cursed Helmet",
		std::vector<Slot>{Slot::Helmet},
		std::vector<StatModifier>{{"resolve", -5}},
		UpgradeInfo{}
	);

	c.equip(cursedHelm);
	std::cout << "Resolve after curse: " << c.getStat("resolve") << "\n";
	std::cout << "MaxHP after curse: " << c.getMaxHP() << "\n";
	std::cout << "HP after curse: " << c.getHP() << "\n";
}

void testFullHPScaling() {
	std::cout << "\n== Full HP Scaling ==\n";
	Character c("id", "Tanky");
	c.setStat("resolve", 10);
	c.setHP(c.getMaxHP()); // full health

	auto armor = std::make_shared<Equippable>(
		"resolve_armor", "Resolve Armor",
		std::vector<Slot>{Slot::Armor},
		std::vector<StatModifier>{{"resolve", 10}},
		UpgradeInfo{}
	);

	c.equip(armor);
	std::cout << "MaxHP after equip: " << c.getMaxHP() << "\n";
	std::cout << "HP after equip (should still be full): " << c.getHP() << "\n";
}