#include "InventoryMenu.h"
#include "Menu.h"
#include "menus/TargetMenu.h"
#include "core/MenuNavigator.h"
#include "items/ItemRegistry.h"
#include "equipment/Equippable.h"
#include "EquipTargetMenu.h"
#include <iostream>

void registerInventoryMenu(MenuRegistry& menuRegistry, GameState& gameState) {
	menuRegistry.addMenuFactory("inventory", [&gameState]() {
		Menu menu("Inventory", "Items you are currently carrying:", MenuType::System);

		const auto& items = gameState.getInventory().getItems();

		for (const auto& entry : items) {
			const auto& item = ItemRegistry::instance().get(entry.itemID);

			auto base = ItemRegistry::instance().get(entry.itemID);
			std::string label = "x" + std::to_string(entry.quantity) + ") " + base->name;
			std::string description = base->description;

			if (base->type == ItemType::Equippable) {

				auto equippable = std::static_pointer_cast<Equippable>(base);

				menu.addOption(MenuOption(
					label,
					description,
					[equippable, &gameState](MenuNavigator& menuNavigator)
					{
						return CommandList{
							makePushMenu(std::make_shared<Menu>(buildEquipTargetMenu(equippable, gameState)))
						};
					}
				));
			}
			else {
				menu.addOption(MenuOption(label, description, [id = entry.itemID, &gameState](MenuNavigator& navigator) {
					TargetSpec spec;

					spec.canSelect = [&](const Character& character) {
						return character.isAlive();
						};

					spec.makeLabel = [&](const Character& character, int) {
						return character.getName();
						};

					spec.makeDescription = [&](const Character& character, int) {
						return std::to_string(character.getHP()) + "/" + std::to_string(character.getMaxHP()) + " HP";
						};

					spec.makeAction = [id](int index) {
						return CommandList{
							makeUseItem(id, index),
							makePause(),
							makePopMenu()
						};
						};

					// create new menu built from the spec
					auto submenu = buildTargetMenu(
						"Use item",
						"Select target for: " + ItemRegistry::instance().get(id)->name,
						spec,
						gameState
					);

					return CommandList{
						makePushMenu(std::make_shared<Menu>(std::move(submenu)))
					};
					}));
			}
		}
		return menu;
	});
}