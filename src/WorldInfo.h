#pragma once
#include <string>
enum WorldType {
	Void = 0,
	Flat = 1,
	Normal = 2,
	Custom = 3
};
struct WorldInfo {
	std::string Name;
	std::string WorldPath;
	WorldType Type;
	uint32_t Seed;
	uint32_t Size;
};
