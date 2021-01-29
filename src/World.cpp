#include "World.h"
#include "Util.h"
void World::Create(WorldInfo& worldInfo)
{
	this->mWorldInfo = worldInfo;
	this->mChunkController = ChunkController(worldInfo.Size, worldInfo.Seed);
	this->mChunkController.BuildWorld();
}

void World::Save()
{
	FILE* file = fopen((this->mWorldInfo.WorldPath + this->mWorldInfo.Name + ".wrld").c_str(), "wb");
	auto& Chunks = this->mChunkController.getAllBlocks();
	
	uint32_t size = this->mWorldInfo.Size;
	uint32_t seed = this->mWorldInfo.Seed;

	fwrite(&size, 1, 4, file); // write world size
	fwrite(&seed, 1, 4, file); // write seed 

	fwrite(&CHUNK_SIZE, 1, 12, file); // write chunk size

	// S  I  Z  E  S  E  E  D
	// xx xx xx xx zz zz zz zz 


	uint32_t buffer[CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z];
	for (uint32_t z = 0; z < Chunks.size(); z++)
	{
		for (uint32_t x = 0; x < Chunks[z].size(); x++)
		{
			auto& currentChunk = Chunks[z][x];
			for (uint32_t i = 0; i < CHUNK_SIZE_X* CHUNK_SIZE_Y* CHUNK_SIZE_Z; i++)
			{
				buffer[i] = currentChunk.blockData[i];
			}
			fwrite(&buffer[0], 4, sizeof(buffer) / sizeof(uint32_t), file);
			fwrite("=END",1, 4, file); // Write ==END at the end of every chunk
		}
	}
	fclose(file);
}

void World::Save(std::string_view Path)
{
	
}

World& World::Load(std::string_view Path)
{
	
	FILE* file = fopen(Path.data(), "rb");

	uint32_t worldSize = 0,seed = 0;

	fread(&worldSize, 1, 4, file); // get world size
	fread(&seed, 1, 4, file); // get seed

	uint32_t chunkSize[3];
	fread(&chunkSize[0], 1, 12, file); // get chunk size
	
	this->mWorldInfo.Size = worldSize;
	this->mWorldInfo.Seed = seed;

	this->mChunkController = ChunkController(worldSize, seed);

	uint32_t currentChunkData[CHUNK_SIZE[0]* CHUNK_SIZE[1] * CHUNK_SIZE[2]];

	for (uint32_t z = 0; z < worldSize; z++)
	{
		for (uint32_t x = 0; x < worldSize; x++)
		{
			fread(&currentChunkData[0], 4, CHUNK_SIZE[0] * CHUNK_SIZE[1] * CHUNK_SIZE[2], file);
			
			Chunk& chunk = this->mChunkController.getChunk(x, z);

			std::memcpy(&chunk.blockData[0], currentChunkData, sizeof(currentChunkData));
			chunk.x = x;
			chunk.z = z;

			char endChunk[4];

			fread(&endChunk[0], 1, 4, file);
		}
	}
	this->mChunkController.BuildChunkMeshes();


	return *this;
}
