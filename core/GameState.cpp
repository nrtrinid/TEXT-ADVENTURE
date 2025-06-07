#include "GameState.h"
#include "items/ItemRegistry.h"
#include "equipment/Equippable.h"
#include <iostream>

bool GameState::hasFlag(const std::string& key) const {
	auto iterator = flags.find(key);
	return iterator != flags.end() && iterator->second; // iterator->second = 'the bool value mapped to the key'
}

void GameState::setFlag(const std::string& key, bool enabled) {
	flags[key] = enabled;
}

void GameState::requestQuit() {
	quitRequested_ = true;
}

bool GameState::quitRequested() const {
	return quitRequested_;
}

PlayerInventory& GameState::getInventory() {
	return inventory;
}

const PlayerInventory& GameState::getInventory() const {
	return inventory;
}

Party::Ptr& GameState::getParty() {
	return party;
}

const Party::Ptr& GameState::getParty() const {
	return party;
}

bool GameState::equipItem(const std::string& id, int index)
{
    // validate party pointer and index
    const auto& partyPtr = getParty();
    if (!partyPtr || index < 0 || index >= partyPtr->size())
        return false;

    // get prototype & inventory
    const auto& proto = std::static_pointer_cast<Equippable>(
        ItemRegistry::instance().get(id));
    auto& inv = getInventory();

    // make sure we own at least one copy
    if (inv.getItemCount(id) == 0) {
        std::cout << "You don’t have that item.\n";
        return false;
    }

    // remove one copy from inventory
    inv.removeItem(id);

    // equip and capture anything bumped off
    const auto& member = partyPtr->getMemberByIndex(index);
    const auto& bumped = member->equip(proto);
    for (auto& old : bumped)
        inv.addItem(old->id);        // return displaced gear

    // 5. Feedback
    std::cout << member->getName() << " equipped "
        << proto->name << ".\n";
    return true;
}


void GameState::unequipSlot(int idx, Slot slot)
{
    auto member = getParty()->getMemberByIndex(idx);
    if (auto removed = member->unequip(slot)) {
        getInventory().addItem(removed->id);
        std::cout << member->getName() << " unequipped " << removed->name << ".\n";
    }
}