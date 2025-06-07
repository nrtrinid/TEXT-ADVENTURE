#pragma once

#include <memory>
class Menu;
class GameState;
enum class Slot;

Menu buildEquipSlotMenu(int characterIndex, Slot slot, GameState& gameState);
