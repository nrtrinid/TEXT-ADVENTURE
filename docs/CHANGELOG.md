# Changelog

All notable changes to this project will be documented here.

## [Unreleased]

### Planned
- ItemRegistry for consumable behavior
- Effect-driven `UseItem` system
- ASCII dungeon layout system
- QTE-style combat

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
