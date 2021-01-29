#include "MeshBuilder.h"

Mesh BuildChunkMesh(Chunk& chunk, std::vector<Chunk*>& neighbourChunks)
{
	std::vector<uint32_t> indices;
	std::vector<float> vertices;

	uint32_t IndicesIndex = 0;

	for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++)
	{
		for (uint32_t x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++)
			{
				uint32_t current = chunk.GetBlock(x, y, z);
				uint32_t currentBlockPos[3]{ x,y,z };
				if (current != BlockName::Air) {

					uint32_t insertedBlockFaces = 0;

					int neighbourBlocksLookup[6][3]{
						{0,1,0},{0,-1,0},{1,0,0},{-1,0,0},{0,0,1},{0,0,-1}
					};
					uint32_t neighbourBlocks[6]{ 1,1,1,1,1,1 };
					for (uint32_t face = 0; face < 6; face++)
					{
						for (uint32_t axis = 0; axis < 3; axis++)
						{

							switch (neighbourBlocksLookup[face][axis]) {
							case 1:
								if (currentBlockPos[axis] + 1 < CHUNK_SIZE[axis]) {
									uint32_t adjPos[]{ currentBlockPos[0],currentBlockPos[1],currentBlockPos[2] };
									adjPos[axis] += 1;
									neighbourBlocks[face] = chunk.GetBlock(adjPos[0], adjPos[1], adjPos[2]);
								}
								else if (currentBlockPos[axis] + 1 >= CHUNK_SIZE[axis]) {
									neighbourBlocks[face] = BlockName::Air;
								}
								break;
							case -1:
								if (currentBlockPos[axis] != 0) {
									uint32_t adjPos[]{ currentBlockPos[0],currentBlockPos[1],currentBlockPos[2] };
									adjPos[axis] -= 1;
									neighbourBlocks[face] = chunk.GetBlock(adjPos[0], adjPos[1], adjPos[2]);
								}
								else {
									neighbourBlocks[face] = BlockName::Air;

								}
								break;

							}
						}
					}
					for (uint32_t i = 0; i < 6; i++)
					{
						if (neighbourBlocks[i] == BlockName::Air) {
							addFace(vertices, BlockFace::faces[i], { chunk.x*CHUNK_SIZE[0],chunk.z*CHUNK_SIZE[2] }, &currentBlockPos[0], Block::getTextureCoordinates(current, i));
							insertedBlockFaces++;
						}
					}
					for (size_t i = 0; i < insertedBlockFaces; i++)
					{

						indices.insert(indices.end(),
							{
								IndicesIndex,
								IndicesIndex + 1,
								IndicesIndex + 2,
								IndicesIndex,
								IndicesIndex + 2,
								IndicesIndex + 3,
							});
						IndicesIndex += 4;
					}
				}
			}
		}
	}

    return Mesh(indices,vertices);
}

void addFace(std::vector<float>& vertices, const float* face, const std::vector<uint32_t>& chunkPos, uint32_t* blockPos, const std::vector<float>& textureCoords)
{
	for (unsigned int i = 0, vertIndex = 0, texIndex = 0; i < 4; i++)
	{
		vertices.emplace_back(face[vertIndex] + chunkPos[0] + blockPos[2]);
		vertices.emplace_back(face[vertIndex + (uint32_t)1] + blockPos[1]);
		vertices.emplace_back(face[vertIndex + (uint32_t)2] + chunkPos[1] + blockPos[0]);
		vertices.emplace_back(textureCoords[texIndex]);
		vertices.emplace_back(textureCoords[texIndex + (uint32_t)1]);
		vertIndex += 3;
		texIndex += 2;
	}

}
