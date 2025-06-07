#include "EquipTargetMenu.h"
#include "entities/Character.h"
#include "core/MenuNavigator.h"
#include <memory>
#include <string>

Menu buildEquipTargetMenu(std::shared_ptr<Equippable> item, GameState& gameState) {
	Menu menu("Choose Character", "Select who should equip: " + item->name, MenuType::System);

	const auto& party = gameState.getParty()->getMembers();
    for (size_t i = 0; i < party.size(); ++i) {
        const auto& member = party[i];
        int memberIndex = static_cast<int>(i);

        std::string label = member->getName();
        std::string desc = "HP: "
            + std::to_string(member->getHP())
            + "/"
            + std::to_string(member->getMaxHP());

        menu.addOption(MenuOption(
            label,
            desc,
            [item, memberIndex](MenuNavigator& nav) {
                return CommandList{
                    makeEquipItem(item->id, memberIndex),
                    makePause(),
                    makePopMenu()
                };
            }
        ));
    }

	return menu;
}