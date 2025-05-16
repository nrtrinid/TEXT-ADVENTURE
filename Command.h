#pragma once
#include <string>
#include <vector>

struct Command {
	enum class Type { Print, Pause, SetFlag, GotoMenu};

	Type type;
	std::string text;   // Print uses this
	std::string target; // GotoMenu uses this
	std::string flag;   // SetFlag uses this
	bool enabled{};     // the actual SetFlag
};

using CommandList = std::vector<Command>; // alias for vector of commands

// helper constructors for common commands

inline Command makePrint(const std::string& text) {
	return { Command::Type::Print, text };
}

inline Command makePause() {
	return { Command::Type::Pause };
}

inline Command makeGotoMenu(const std::string& targetMenu) {
	return { Command::Type::GotoMenu, "", targetMenu };
}

inline Command makeSetFlag(const std::string& flagName, bool enabled = true) {
	return { Command::Type::SetFlag, "", "", flagName, enabled };
}