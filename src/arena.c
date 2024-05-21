#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

void waitForSnakeGame(char* gameType, char* gameName, int* sizeX, int* sizeY, int* nbWalls);
int getSnakeArena(int* walls);



Arena* createArena(char* gameType, int* x) {
    char gameName[50];
    int sizeX;
    int sizeY;
    int nbWalls;

    waitForSnakeGame(gameType, gameName, &sizeX, &sizeY, &nbWalls);

    Arena* arena = (Arena*)malloc(sizeof(Arena));

    arena->nbWalls = nbWalls;
    arena->sizeX = sizeX;
    arena->sizeY = sizeY;
    arena->walls = (Wall*)malloc(nbWalls*sizeof(Wall));

    *x=getSnakeArena((int*)arena->walls);

    return arena;
}

void freeArena(Arena* arena) {
    if (arena) {
        if (arena->walls) {
            free(arena->walls);
        }
        free(arena);
    }
}


void printArenax(Arena* arena) {
    for (int x = 0; x < arena->sizeX; ++x) {
        for (int y = 0; y < arena->sizeY; ++y) {
            int wall = 0;
            for (int i = 0; i < arena->nbWalls; ++i) {
                if ((x == arena->walls[i].x1 && y == arena->walls[i].y1) ||
                    (x == arena->walls[i].x2 && y == arena->walls[i].y2)) {
                    wall = 1;
                    break;
                }
            }

            if (wall) {
                printf("#"); 
            } else {
                printf("."); 
            }
        }
        printf("\n"); 
    }
}
