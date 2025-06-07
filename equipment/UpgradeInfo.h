#pragma once

struct UpgradeInfo {
	int level = 0;
	int maxLevel = 10;
	float flatPerLevel = 1.f; // +1 resolve each level
};