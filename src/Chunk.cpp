#include "Chunk.h"
#include <algorithm>
#include <glad/glad.h>
#include "Noise.h"
#include "Log.h"
#include <glm/common.hpp>
#include "MeshBuilder.h"
void ChunkMesh::Build(Chunk& chunk, std::vector<Chunk*>& neighbourChunks)
{
	glCreateVertexArrays(1, &va);

	this->x = chunk.x * 16;
	this->z = chunk.z * 16;

	vertexLayout = {
		{{ glcore::shader_data_type::type::vec3, "position" }},
		{{ glcore::shader_data_type::type::vec2, "uv" }},
	};

	auto& [indices,vertices] = BuildChunkMesh(chunk, neighbourChunks);

	glBindVertexArray(va);

	glCreateBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	int attrib_index{};
	for (const auto& [data, offset] : this->vertexLayout)
	{
		glEnableVertexAttribArray(attrib_index);
		glVertexAttribPointer(
			attrib_index++,
			glcore::shader_data_type::component_count(data.type),
			glcore::shader_data_type::underlying_type(data.type),
			GL_FALSE,
			this->vertexLayout.stride(),
			reinterpret_cast<const void*>(offset)
		);
	}
	glBindVertexArray(va);
	glCreateBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

	this->indexCount = indices.size();
}

void Chunk::Generate(uint32_t x, uint32_t z, uint32_t worldSize, uint32_t scale, uint32_t seed)
{
	this->x = x;
	this->z = z;
	for (uint32_t z1 = 0; z1 < CHUNK_SIZE_Z; z1++)
	{
		for (uint32_t x1 = 0; x1 < CHUNK_SIZE_X; x1++)
		{
			PerlinNoise noise(seed);
			float newX, newZ;
			newX = (float)((this->x * CHUNK_SIZE_X) + x1) / ((float)worldSize * (float)CHUNK_SIZE_X);
			newZ = (float)((this->z * CHUNK_SIZE_Z) + z1) / ((float)worldSize * (float)CHUNK_SIZE_Z);

			auto height = glm::ceil(
				(float)CHUNK_SIZE_Y * (float)noise.noise(newX * scale, 0, newZ * scale));
			SetBlock(z1, height, x1, BlockName::Grass);
			for (uint32_t y = 0; y < height; y++)
			{
				SetBlock(z1, y, x1, BlockName::Dirt);
			}
		}
	}
}

uint32_t Chunk::GetBlock(uint32_t x, uint32_t y, uint32_t z) const
{
	return this->blockData[x + CHUNK_SIZE_X * (y + CHUNK_SIZE_Y * z)];
}

uint32_t Chunk::GetBlock(uint32_t* pos) const
{
	return this->blockData[pos[0] + pos[1] * CHUNK_SIZE_X + pos[2] * CHUNK_SIZE_X * CHUNK_SIZE_Z];
}

void Chunk::SetBlock(uint32_t x, uint32_t y, uint32_t z, uint32_t block)
{
	this->blockData[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y] = block;
}
