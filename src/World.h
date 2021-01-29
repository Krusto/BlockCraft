#pragma once
#include "WorldInfo.h"
#include "ChunkController.h"

class World {
public:
	World() = default;
	void Create(WorldInfo& worldInfo);
	void Save();
	void Save(std::string_view Path);
	World& Load(std::string_view Path);

	auto& getChunkController() { return this->mChunkController; }
	const auto getChunkController() const { return this->mChunkController; }

private:

	ChunkController mChunkController;
	WorldInfo mWorldInfo;
};