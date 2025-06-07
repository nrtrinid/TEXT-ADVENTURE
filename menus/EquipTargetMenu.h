#pragma once

#include "menus/Menu.h"
#include "equipment/Equippable.h"
#include "core/GameState.h"

Menu buildEquipTargetMenu(std::shared_ptr<Equippable> item, GameState& gameState);
