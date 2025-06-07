#pragma once

#include <memory>

class MenuRegistry;
class GameState;
class Character;

void registerCharacterMenu(MenuRegistry& menuRegistry, GameState& gameState, const std::shared_ptr<Character>&);
