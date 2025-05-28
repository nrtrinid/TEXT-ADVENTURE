# Changelog

All notable changes to this project will be documented here.

## [Unreleased]

### Planned
- ASCII dungeon layout system
- QTE-style combat
- Character progression with experience and leveling
- Refactor Skill command system

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
