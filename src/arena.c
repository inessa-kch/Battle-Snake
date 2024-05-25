#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

void waitForSnakeGame(char* gameType, char* gameName, int* sizeX, int* sizeY, int* nbWalls);
int getSnakeArena(int* walls);




// Initialize the Arena with walls' data including bordering walls
Arena* initArena(char* gameType, int* x) {
    char gameName[50];
    int sizeX;
    int sizeY;
    int nbWalls;

    waitForSnakeGame(gameType, gameName, &sizeX, &sizeY, &nbWalls);

    

    int* walls = (int*)malloc(nbWalls * 4 * sizeof(int));

    *x = getSnakeArena(walls);
  
    
    // Print the walls' data
    printf("Walls' data:\n");
    for (int i = 0; i < nbWalls * 4; i += 4) {
        printf("Wall %d: (%d, %d) - (%d, %d)\n", i / 4 + 1, walls[i], walls[i + 1], walls[i + 2], walls[i + 3]);
    }
    printf("size X :%d\n",sizeX);
    printf("size Y :%d\n",sizeY);
    printf("nbWalls :%d\n",nbWalls);



    Arena* arena = (Arena*)malloc(sizeof(Arena));
    arena->sizeX = sizeX;
    arena->sizeY = sizeY;
    arena->cells = (Cell**)malloc((sizeY) * sizeof(Cell*));

    for (int i = 0; i < (sizeY); i++) {
        arena->cells[i] = (Cell*)malloc((sizeX) * sizeof(Cell));

    }

    for (int i = 0; i < (sizeY); i++) {
        for (int j = 0; j < (sizeX); j++) {
            arena->cells[i][j].wallTop = 0;
            arena->cells[i][j].wallBottom = 0;
            arena->cells[i][j].wallLeft = 0;
            arena->cells[i][j].wallRight = 0;
        }
    }

    for (int i = 0; i < nbWalls; i++) {
        int x1 = walls[i*4];
        int y1 = walls[i*4+1];
        int x2 = walls[i*4+2];
        int y2 = walls[i*4+3];
        if (x1 == x2) {
            if (y1 < y2) {
                arena->cells[y1][x1].wallBottom = 1;
                arena->cells[y2][x2].wallTop = 1;
            } else {
                arena->cells[y1][x1].wallTop = 1;
                arena->cells[y2][x2].wallBottom = 1;
            }
        } else {
            if (x1 < x2) {
                arena->cells[y1][x1].wallRight = 1;
                arena->cells[y2][x2].wallLeft = 1;
            } else {
                arena->cells[y1][x1].wallLeft = 1;
                arena->cells[y2][x2].wallRight = 1;
            }
        }
    }

    free(walls);

    return arena;
}





// Free memory allocated for the Arena
void freeArena(Arena* arena) {
    for (int i = 0; i < arena->sizeY; i++) {
        free(arena->cells[i]);
    }
    free(arena->cells);
    free(arena);
}

// Print the Arena
void printArenax(Arena* arena) {
    printf(".");
    for (int j = 0; j < arena->sizeX; j++) {
        printf("---.");
    }
    printf("\n");
    for (int i = 0; i < arena->sizeY; i++) {
        for (int j = 0; j < arena->sizeX; j++) {
            if (arena->cells[i][j].wallLeft) {
                printf("|");
            } else {
                printf(" ");
            }
            printf("   ");
        }
        if (arena->cells[i][arena->sizeX - 1].wallRight) {
            printf("|");
        } else {
            printf(" ");
        }
        printf("\n");
        printf(".");
        for (int j = 0; j < arena->sizeX; j++) {
            if (arena->cells[i][j].wallBottom) {
                printf("---.");
            } else {
                printf("   .");
            }
        }
        printf("\n");
    }
}

