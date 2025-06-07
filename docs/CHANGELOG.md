# Changelog

All notable changes to this project will be documented here.

## [Unreleased]

### Planned
- ASCII dungeon layout system
- QTE-style combat
- Character progression with experience and leveling
- Skill usage outside combat
- Equippable item upgrades and enhancements
- Generalized targeting menu

---

## [v0.6.0] - 2025-06-07

### Added
- **Dynamic equipment system** with full gear slot integration
- `EquipSlotMenu` for intuitive slot-specific equipping
- `EquipTargetMenu` for selecting who equips gear from the inventory
- `GameState::equipItem` and `GameState::unequipSlot` manage inventory sync
- Commands: `EquipItem`, `UnequipItem` with proper handling in `CommandProcessor`
- Hover descriptions for gear showing stat modifiers (e.g., "+3 power")
- Consistent navigation using stacked `pushMenu()` and registered `gotoMenu(...)`

### Changed
- `CharacterMenu` redesigned to show gear clearly aligned by slot with inline descriptions
- Improved menu cursor behavior to prevent overflow errors
- Cleaned up menu factories and character-menu registration to avoid redundant rebuilds
- Refactored `ItemRegistry` with `tryGet()` and safe `getEquippable()` casts
- Improved stability and safety checks for dynamic menus

### Fixed
- Crash and softlock issues when equipping incompatible gear
- Inventory sync issues causing item duplication or loss upon equipping
- Temporary UI bugs affecting hover descriptions and stat displays

---

## [v0.5.0] - 2025-05-30

### Added
- Fully implemented equipment system with defined gear slots (`Mainhand`, `Offhand`, `Helmet`, `Armor`, etc.)
- `Character::equip()` and `unequip()` with automatic slot conflict resolution
- Stat modifiers now dynamically affect characters (e.g., `resolve` -> max HP scaling)
- Supports multi-slot items like greatswords (Mainhand + Offhand)
- Added proportional HP adjustment on stat-based max HP changes
- Created `equipment_test.cpp` for verifying edge cases like:
  - Slot replacement
  - Multi-slot conflicts
  - Negative stat modifiers
  - Scaling HP from full or damaged states

### Changed
- Updated `CMakeLists.txt` to include `equipment/` directory and build a test harness (`equipment_test`)
- Refined equip/unequip logic for stability and clean state management

---

## [v0.4.0] - 2025-05-27

### Added
- Implemented item system using `ItemRegistry` for reusable item definitions
- Introduced `EffectRegistry` to handle item effects, including:
  - `HealEffect` and full HP restoration logic
  - `NoopEffect` for key items with no active behavior
- Integrated item usage with `Command::UseItem` and `makeUseItem()`
- Updated `PartyMenu` to show character HP and support item selection

### Changed
- Refactored `Command` structure for cleaner item-related fields
- Improved debug output for healing skills to show base + bonus
- Cleaned up `MenuController` logic for switching menus
- Updated CMakeLists.txt to include `systems/`, `effects/`, `items/`, `skills/`, and `commands/`


---

## [v0.3.0] - 2025-05-26

### Added
- Stat-scaled skill system and `SkillRegistry`
- `SkillSystem::execute()` with flexible scaling
- `HealEffect` integrated with `EffectRegistry`
- Command type `UseSkill` with test support
- Helpers like `makeUseSkill()` for command creation

### Changed
- `getSkillBonus()` now uses only stat scaling (removed level)
- Clarified `Command` structure for skill/item use

---

## [v0.2.0] - 2025-05-23
### Added
- Cross-platform input system with support for arrow key handling on Windows and Linux
- CMake build system for Linux, VS Code, and command-line compatibility
- ANSI escape-based dynamic screen redraw system

### Changed
- Renamed `TEXT ADVENTURE.cpp` to `main.cpp` for compatibility and clarity
- Updated README with full build instructions and project vision
