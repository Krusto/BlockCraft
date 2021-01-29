#pragma once
#include <cstdint>
#include <unordered_map>
#include <array>
#include "Chunk.h"
#include "Log.h"
struct Position2Di {
public:
	Position2Di() = default;
	Position2Di(uint32_t x, uint32_t z) {
		this->x = x;
		this->z = z;
	}
	uint32_t x;
	uint32_t z;
};
class ChunkController {
public:
	ChunkController() = default;
	ChunkController(uint32_t worldSize,uint32_t seed = 0) {
		this->seed = seed;
		this->worldSize = worldSize;
		this->mChunks.resize(worldSize);
		std::for_each(this->mChunks.begin(), this->mChunks.end(), [this](std::vector<Chunk>& n) {
			n.resize(this->worldSize);
			});
		this->mChunkMeshes.resize(worldSize);
		std::for_each(this->mChunkMeshes.begin(), this->mChunkMeshes.end(), [this](std::vector<ChunkMesh>& n) {
			n.resize(this->worldSize);
			});
	}
	
	static ChunkController& Create(uint32_t worldSize, uint32_t seed = 0) {
		return ChunkController(worldSize, seed);
	}
	
	void BuildWorld() {
		for (uint32_t x = 0; x < worldSize; x++)
		{
			for (uint32_t z = 0; z < worldSize; z++)
			{
				this->GenerateChunkBlocks(x,z);
			}
		}
		BuildChunkMeshes();
	}
	void BuildChunkMeshes() {
		for (uint32_t z = 0; z < worldSize; z++)
		{
			for (uint32_t x = 0; x < worldSize; x++)
			{
				std::vector<Chunk*> neighbourChunks(4);
				if (x + 1 < worldSize)
					neighbourChunks[0] = &this->mChunks[x + 1][z];
				if (x != 0)
					neighbourChunks[1] = &this->mChunks[x - 1][z];

				if (z + 1 < worldSize)
					neighbourChunks[2] = &this->mChunks[x][z + 1];
				if (z != 0)
					neighbourChunks[3] = &this->mChunks[x][z - 1];

				this->GenerateChunkMesh(x, z, neighbourChunks);
			}
		}
	}
	void GenerateChunkBlocks(uint32_t x, uint32_t z) {
		this->mChunks[x][z].Generate(x,z,worldSize,10,seed);
	}
	void GenerateChunkMesh(uint32_t x, uint32_t z,std::vector<Chunk*>& neighbourChunks) {
		this->mChunkMeshes[x][z].Build(this->mChunks[x][z], neighbourChunks);
	}

	const auto& getChunkMeshes() const { return this->mChunkMeshes; }
	auto& getChunkMeshes() { 
		auto& meshes = this->mChunkMeshes;
		return this->mChunkMeshes; 
	}

	const auto& getAllBlocks() const { return this->mChunks; }
	auto& getAllBlocks() { return this->mChunks; }

	const uint32_t GetSizeX() const { return this->worldSize; }
	uint32_t GetSizeX(){ return this->worldSize; }
	const uint32_t GetSizeZ() const { return this->worldSize; }
	uint32_t GetSizeZ(){ return this->worldSize; }

	Chunk& getChunk(uint32_t x, uint32_t z) { return mChunks[x][z]; }
	const Chunk& getChunk(uint32_t x, uint32_t z) const { return mChunks[x][z]; }
private:
	uint32_t seed{};
	uint32_t worldSize{};
	std::vector<std::vector<Chunk>> mChunks;
	std::vector<std::vector<ChunkMesh>> mChunkMeshes;
};