#pragma once

#include "items/Item.h"
#include "equipment/Equippable.h"
#include <string>
#include <vector>

class Menu;

struct Command {
    enum class Type {
        Print,
        Pause,
        SetFlag,
        GotoMenu,
        PushMenu,
        PopMenu,
        QuitGame,
        AddItem,
        RemoveItem,
        EquipItem,
        UnequipItem,
        UseItem,
        UseSkill
    };

    Type type;

    // UI / Narrative
    std::string text;       // print uses this
    std::string target;     // gotoMenu uses this (menu ID)
    std::string flag;       // setFlag uses this
    bool enabled{};         // used by setFlag (true = set, false = unset)

    // inventory
    int itemQuantity = 1;         // affects addItem / removeItem

    // game action (skill/item use)
    std::string id;               // item or skill ID (for useItem / useSkill)
    int magnitudeOverride = 0;    // optional override for item effects
    int targetIndex = 0;          // target party index (useItem / useSkill)

    std::optional<Slot> slot;     // only used by equipItem/ unequipItem
    
    std::shared_ptr<Menu> menu;   // only used by pushmenu
};

using CommandList = std::vector<Command>; // alias for vector of commands

// helper constructors for common commands

inline Command makePrint(const std::string& text) {
	return { Command::Type::Print, text };
}

inline Command makePause() {
	return { Command::Type::Pause };
}

inline Command makeGotoMenu(const std::string& targetMenu, bool remember = false) {
	Command command{ Command::Type::GotoMenu };
	command.target = targetMenu;
	command.enabled = remember;
	return command;
}

inline Command makeSetFlag(const std::string& flagName, bool enabled = true) {
	return { Command::Type::SetFlag, "", "", flagName, enabled };
}

inline Command makePushMenu(std::shared_ptr<Menu> menu) {
    Command command{ Command::Type::PushMenu };
    command.menu = std::move(menu);
    return command;
}

inline Command makePopMenu() {
	return Command{ Command::Type::PopMenu };
}

inline Command makeQuitGame() {
    return { Command::Type::QuitGame };
}

inline Command makeAddItem(const std::string& itemID, int quantity = 1) {
    Command command{ Command::Type::AddItem };
    command.id = itemID;
    command.itemQuantity = quantity;
    return command;
}

inline Command makeRemoveItem(const std::string& itemID, int quantity = 1) {
	Command command{ Command::Type::RemoveItem };
	command.id = itemID;
	command.itemQuantity = quantity;
	return command;
}

inline Command makeEquipItem(const std::string& itemID, int characterIndex, Slot slot) {
    Command command{ Command::Type::EquipItem };
    command.id = itemID;
    command.targetIndex = characterIndex;
    command.slot = slot;
    return command;
}

inline Command makeUnequipItem(int characterIndex, Slot slot) {
    Command command{ Command::Type::UnequipItem };
    command.targetIndex = characterIndex;
    command.slot = slot;
    return command;
}

inline Command makeUseItem(const std::string& itemId, int targetIndex = 0, int quantity = 1, int magnitudeOverride = 0) {
    Command command{ Command::Type::UseItem };
    command.id = itemId;
    command.targetIndex = targetIndex;
    command.itemQuantity = quantity;
    command.magnitudeOverride = magnitudeOverride;
    return command;
}

inline Command makeUseSkill(const std::string& skillId, int targetIndex) {
    Command command{ Command::Type::UseSkill };
    command.id = skillId;
    command.targetIndex = targetIndex;
    return command;
}
