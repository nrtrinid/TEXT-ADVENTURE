#pragma once

#include <string>

struct StatModifier {
	std::string stat;
	int flat = 0;
	float mult = 0.f; // % bonus expressed as 0.10 = +10%
};