#include "InventoryMenu.h"
#include "Menu.h"
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
			std::string label = base->name + " (x" + std::to_string(entry.quantity) + ")";
			std::string description = base->description;

			if (base->type == ItemType::Equippable) {

				auto equippable = std::static_pointer_cast<Equippable>(base);

				menu.addOption(MenuOption(
					label,
					description,
					[equippable, &gameState](MenuNavigator& menuNavigator)
					{
						Menu sub = buildEquipTargetMenu(equippable, gameState);
						menuNavigator.pushMenu(std::make_shared<Menu>(std::move(sub)));
						return CommandList{};          // nothing else for now
					}
				));
			}
			else {
				menu.addOption(MenuOption(label, description, [id = entry.itemID](MenuNavigator&) {
					return CommandList{
						makeUseItem(id),
						makePause()
					};
				}));
			}
		}
		return menu;
	});
}