#include "Block.h"

std::vector<float> Block::getTextureCoordinates(uint32_t blockID,uint32_t face)
{
    blockID = Block::blockFaceIndices[blockID][face];
    float y = (float)(blockID / TEXTURE_ATLAS_SIZE_Y) / (float)TEXTURE_ATLAS_SIZE_Y;
    float x = (float)(blockID % TEXTURE_ATLAS_SIZE_Y) / (float)TEXTURE_ATLAS_SIZE_Y;

    float textureSize = 1.0f / (float)TEXTURE_ATLAS_SIZE_Y;

    return {
                                            x              , y + textureSize,   //top left     "    "
                                            x + textureSize, y + textureSize,  //top right    "    "
                                            x + textureSize, y,  //bottom right "    "
                                            x              , y,  //bottom left of texture
    };
}
