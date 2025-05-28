#pragma once

#include "Command.h"
#include "core/GameState.h"

void executeAddItem(const Command& command, GameState& gameState);
void executeRemoveItem(const Command& command, GameState& gameState);
void executeUseItem(const Command& command, GameState& gameState);
