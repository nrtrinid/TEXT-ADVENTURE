# TEXT ADVENTURE

A C++ text-based RPG engine built in Visual Studio, featuring a modular menu system, stack-based UI transitions, and foundational systems for building interactive world states, character parties, and command parsing.

## ✅ Working Features

- 📦 **Modular Menu System**  
  Menus are dynamically registered and stackable, supporting flexible navigation and decoupled display/input logic.

- 🎮 **Party System**  
  Supports both static (player) and dynamic (mercenary) parties, with full character rendering and type classification.

- 🧠 **Early `GameState` System**  
  Tracks persistent world flags and conditional logic across menus and commands.

- 🎨 **ANSI Terminal Rendering**  
  Clean, color-coded output with smooth screen redraws using ANSI escape sequences.

- ⌨️ **Command Parser (WIP)**  
  Basic infrastructure for handling typed commands and input validation.

## 🚧 Planned Features

- 🧱 ASCII dungeon layouts with directional movement
- ⏱️ QTE-style timing-based combat system
- 🎒 Inventory and item usage system
- ⚔️ Mercenary dungeon mode with permadeath + randomized loot
- 🔄 Save/load functionality and serialization of game state

## 🛠️ Tools Used

- C++17  
- Visual Studio 2022  
- Git version control  

## 🧪 How to Build

Open `TEXT-ADVENTURE.sln` in Visual Studio 2022 and press **Build** (or `Ctrl+Shift+B`).  
This project uses the default Visual Studio configuration for compilation.

---

> 🎯 This project is a personal exploration of clean C++ architecture in game design — a focus on modularity, separation of concerns, and extensibility in a terminal-based RPG environment.
