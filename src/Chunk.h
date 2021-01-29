#pragma once
#include <cstdint>
#include <glcore/glcore.h>
#include "Block.h"
#include "ChunkInfo.h"
#include <SFML/OpenGL.hpp>

struct Chunk {
public:
	uint32_t x{};
	uint32_t z{};
	uint32_t blockData[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z]{};
	void Generate(uint32_t x, uint32_t z, uint32_t worldSize,uint32_t scale = 10, uint32_t seed = 0);
	uint32_t GetBlock(uint32_t x, uint32_t y, uint32_t z) const;
	uint32_t GetBlock(uint32_t* pos) const;

	void SetBlock(uint32_t x, uint32_t y, uint32_t z,uint32_t block);
	Chunk& operator = (const Chunk& a) {
		x = a.x;
		z = a.z;
		std::memcpy(blockData, a.blockData, CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * sizeof(uint32_t));
		return *this;
	}
};
struct ChunkMesh {
public:
	ChunkMesh() = default;

	uint32_t x{};
	uint32_t z{};
	uint32_t va{};
	uint32_t ibo{};
	uint32_t vbo{};
	uint32_t indexCount{};

	glcore::vertex_buffer_layout vertexLayout{};

	void Build(Chunk& chunk,std::vector<Chunk*>& neighbourChunks);

	ChunkMesh& operator =(const ChunkMesh& a)
	{
		va = a.va;
		indexCount = a.indexCount;
		vertexLayout = a.vertexLayout;
		return *this;
	}

private:
};
