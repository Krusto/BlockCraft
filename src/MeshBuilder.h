#pragma once
#include "Chunk.h"
#include "Mesh.h"

Mesh BuildChunkMesh(Chunk& chunk, std::vector<Chunk*>& neighbourChunks);
void addFace(std::vector<float>& vertices, const float* face, const std::vector<uint32_t>& chunkPos, uint32_t* blockPos, const std::vector<float>& textureCoords);
