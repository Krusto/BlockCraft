#pragma once
#include <vector>

enum BlockName {
	Air = 0,
	Dirt = 1,
	Grass =2,
	Stone =3,
	CobbleStone=4,
	Sand=5,
	Light=6,
    GoldBlock=7
};

#define BLOCK_AIR 0
#define BLOCK_DIRT 1
#define BLOCK_GRASS 2
#define BLOCK_STONE 3
#define BLOCK_COBBLESTONE 4
#define BLOCK_SAND 5
#define BLOCK_LIGHT 6
#define BLOCK_GOLDBLOCK 7

#define BLOCK_FACE_TOP 0
#define BLOCK_FACE_BOTTOM 1
#define BLOCK_FACE_FRONT 2
#define BLOCK_FACE_BACK 3
#define BLOCK_FACE_RIGHT 4
#define BLOCK_FACE_LEFT 5

#define BLOCK_SIZE 1
#define TEXTURE_ATLAS_SIZE_X 8
#define TEXTURE_ATLAS_SIZE_Y 8

#define DEFINED_NUM_BLOCKS 8

namespace Block {
    std::vector<float> getTextureCoordinates(uint32_t blockID,uint32_t face);
    
    constexpr uint32_t blockFaceIndices[DEFINED_NUM_BLOCKS][6]{
       //T,B,F,B,R,L
        {0,0,0,0,0,0}, // AIR
        {1,1,1,1,1,1}, // DIRT
        {2,1,10,10,10,10}, // GRASS
        {3,3,3,3,3,3}, // STONE
        {4,4,4,4,4,4}, // COBBLE
        {5,5,5,5,5,5}, // SAND
        {6,6,6,6,6,6}, // LIGHT
        {7,7,7,7,7,7}  // GOLD
    };
}
namespace BlockFace {

    constexpr float faces[6][12] =
    {
    //TOP FACE
    {
        0,          BLOCK_SIZE, BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, 0,
        0,          BLOCK_SIZE, 0
    },
    //BOTTOM FACE
    {
        0,          0, 0,
        BLOCK_SIZE, 0, 0,
        BLOCK_SIZE, 0, BLOCK_SIZE,
        0,          0, BLOCK_SIZE
    },
    //FRONT FACE
    {
        0,          0,          BLOCK_SIZE,
        BLOCK_SIZE, 0,          BLOCK_SIZE,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
        0,          BLOCK_SIZE, BLOCK_SIZE
    },
    //BACK FACE
    {
        BLOCK_SIZE, 0,          0,
        0,          0,          0,
        0,          BLOCK_SIZE, 0,
        BLOCK_SIZE, BLOCK_SIZE, 0
    },
    //RIGHT FACE
    {
        BLOCK_SIZE, 0,          BLOCK_SIZE,
        BLOCK_SIZE, 0,          0,
        BLOCK_SIZE, BLOCK_SIZE, 0,
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE
    },
    // LEFT FACE
    {
        0, 0,           0,
        0, 0,           BLOCK_SIZE,
        0, BLOCK_SIZE,  BLOCK_SIZE,
        0, BLOCK_SIZE,  0
    }

    };
}