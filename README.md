# TEXT ADVENTURE

A C++ text-based RPG built with a modular engine, supporting cross-platform builds using CMake and a terminal-based interface for Windows and Linux.

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

### Windows (Visual Studio Code)
- Make sure CMake and a C++ compiler (MSVC or MinGW) are installed
- Open the folder in VS Code
- Run `CMake: Configure` and `CMake: Build` from the Command Palette
- Run the executable from the `build/` directory

### Linux / WSL
```bash
git clone https://github.com/nrtrinid/TEXT-ADVENTURE.git
cd TEXT-ADVENTURE
cmake -B build
cmake --build build
./build/text-adventure
```
---

## 🧠 About This Project

> 🎯 This project is a personal exploration of clean C++ architecture in game design — a focus on modularity, separation of concerns, and extensibility in a terminal-based RPG environment.
