# Text Adventure RPG Engine

A modular, terminal-based RPG engine built in modern C++. Inspired by classic games like *Zork* and *Wizardry*, this project serves as both a learning playground and a foundation for building a full-featured text-based RPG.

---

## 🚀 Features

### 🧱 Core Architecture
- **Modular Command System**: Flexible runtime behavior using `Command` objects like `UseItem`, `SetFlag`, and `GotoMenu`, with separate handlers for skills and items.
- **Dynamic Menu System**: Supports stacked menus, navigable via keyboard, with hoverable descriptions and submenu transitions.
- **Central Game State**: `GameState` manages inventory, parties, flags, and world context.

### 🧙 Characters & Parties
- `Character` class with dynamic stats, HP, level, and mercenary flag
- `Party` management system (player vs. mercenaries)

### 🧪 Items & Effects
- `ItemRegistry` for template-based item definitions
- `EffectRegistry` system to decouple item logic (healing, restoration, etc.)
- Inline item creation and command integration

### 🧠 Skills & Stat Scaling
- `SkillSystem` that scales skill magnitude based on configured character stats
- Polymorphic commands for activating skills through character attributes

### ⚔️ Equipment System (In Progress)
- Planned gear slots: weapon, helmet, chest, boots, and 2 trinkets
- Future support for stat bonuses, gear leveling, and enchantments

---

## 🛠️ Building

This project uses **CMake** and is tested with **Visual Studio** on Windows.

### Requirements
- CMake 3.15+
- Visual Studio 2019+ (or any C++17-compatible compiler)

### Build Steps

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
```

Or open the `.sln` in Visual Studio and build from there.

---

## 📂 Project Structure

```
core/        - GameState, Input handling, Inventory
menus/       - Menu engine, controllers, InventoryMenu
commands/    - Command types and behavior executors
items/       - Item definitions, registry, and item types
effects/     - Modular effect logic (e.g., healing)
entities/    - Character and party classes
main/        - Entry point and game loop
docs/        - Changelog and future planning
```

---

## 🧭 Roadmap

- [ ] Equipment system with gear slots and UI integration
- [ ] Combat loop and skill targeting
- [ ] Procedural dungeon exploration (mercenary auto-play)
- [ ] Relationship and personality system for mercenaries
- [ ] Save/load system
- [ ] Scripted scenarios using commands and flags

---

## 💬 License & Contribution

Currently a personal learning project in early development and undergoing frequent refactors.
