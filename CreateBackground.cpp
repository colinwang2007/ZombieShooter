#include "ZombieArena.h"
#include <iostream>
int createBackground(VertexArray& rVA, IntRect arena){
    const int TILE_SIZE (50);  // in pixels
    const int TILE_TYPES (3);
    const int VERTS_IN_QUAD (4);  // number of vertices in a quad
    int worldWidth=arena.width/TILE_SIZE;
    int worldHeight=arena.height/TILE_SIZE;
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
    int currentVertex = 0;
    srand(time(NULL));
    for (int w = 0; w < worldWidth; w++) {
        for (int h = 0; h < worldHeight; h++) {
            rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 1].position = Vector2f(w * TILE_SIZE+TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 2].position = Vector2f(w * TILE_SIZE+TILE_SIZE, h * TILE_SIZE+TILE_SIZE);
            rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE+TILE_SIZE);
            int tile_idx = rand()%3;
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
                tile_idx=TILE_TYPES;
            }
            int verticalOffset = tile_idx*TILE_SIZE;
            rVA[currentVertex + 0].texCoords = Vector2f(0, verticalOffset);
            rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
            rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, verticalOffset+TILE_SIZE);
            rVA[currentVertex + 3].texCoords = Vector2f(0, verticalOffset+TILE_SIZE);
            currentVertex+=VERTS_IN_QUAD;
        }
    }
    return TILE_SIZE;
}
