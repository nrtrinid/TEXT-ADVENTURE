#pragma once

#include <string_view>

enum class Slot {
	Mainhand,
	Offhand,
	Helmet,
	Armor,
	Boots,
	TrinketA,
	TrinketB,
	COUNT
};

inline std::string_view slotToString(Slot slot) {
    switch (slot) {
    case Slot::Helmet:   return "Helmet";
    case Slot::Armor:    return "Armor";
    case Slot::Mainhand: return "Mainhand";
    case Slot::Offhand:  return "Offhand";
    case Slot::Boots:    return "Boots";
    case Slot::TrinketA: return "Trinket A";
    case Slot::TrinketB: return "Trinket B";
    default:             return "Unknown";
    }
}