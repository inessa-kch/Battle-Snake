#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "arena.h"

void waitForSnakeGame(char* gameType, char* gameName, int* sizeX, int* sizeY, int* nbWalls);
int getSnakeArena(int* walls);


Arena* initArena(char* gameType, int* x) {
    char gameName[50];
    int sizeX;
    int sizeY;
    int nbWalls;

    waitForSnakeGame(gameType, gameName, &sizeX, &sizeY, &nbWalls);

    

    int* walls = (int*)malloc(nbWalls * 4 * sizeof(int));

    *x = getSnakeArena(walls);

    Arena* arena = (Arena*)malloc(sizeof(Arena));
    arena->sizeX = sizeX;
    arena->sizeY = sizeY;
    arena->cells = (Cell**)malloc((sizeY) * sizeof(Cell*));

    for (int i = 0; i < (sizeY); i++) {
        arena->cells[i] = (Cell*)malloc((sizeX) * sizeof(Cell));

    }

    for (int i = 0; i < (sizeY); i++) {
        for (int j = 0; j < (sizeX); j++) {
            if (i == 0) {
                arena->cells[i][j].wallTop = 1;
            } else {
                arena->cells[i][j].wallTop = 0;
            }
            if (i == sizeY - 1) {
                arena->cells[i][j].wallBottom = 1;
            } else {
                arena->cells[i][j].wallBottom = 0;
            }
            if (j == 0) {
                arena->cells[i][j].wallLeft = 1;
            } else {
                arena->cells[i][j].wallLeft = 0;
            }
            if (j == sizeX - 1) {
                arena->cells[i][j].wallRight = 1;
            } else {
                arena->cells[i][j].wallRight = 0;
            }
            arena->cells[i][j].snake = 0;
        }
    }

    for (int i = 0; i < nbWalls*4; i+=4) {
        int x1 = walls[i];
        int y1 = walls[i+1];
        int x2 = walls[i+2];
        int y2 = walls[i+3];
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


Arena* copyArena(Arena* a){
    Arena* arena = (Arena*)malloc(sizeof(Arena));
    arena->sizeX = a->sizeX;
    arena->sizeY = a->sizeY;
    arena->cells = (Cell**)malloc((a->sizeY) * sizeof(Cell*));

    for (int i = 0; i < (a->sizeY); i++) {
        arena->cells[i] = (Cell*)malloc((a->sizeX) * sizeof(Cell));

    }

    for (int i = 0; i < (a->sizeY); i++) {
        for (int j = 0; j < (a->sizeX); j++) {
            arena->cells[i][j].wallTop = a->cells[i][j].wallTop;
            arena->cells[i][j].wallBottom = a->cells[i][j].wallBottom;
            arena->cells[i][j].wallLeft = a->cells[i][j].wallLeft;
            arena->cells[i][j].wallRight = a->cells[i][j].wallRight;
            arena->cells[i][j].snake = a->cells[i][j].snake;
        }
    }
    return arena;
}


void freeArena(Arena* arena) {
    for (int i = 0; i < arena->sizeY; i++) {
        free(arena->cells[i]);
    }
    free(arena->cells);
    free(arena);
}


void myprintArena(Arena* arena) {
    setlocale(LC_CTYPE, "");
    printf(".");
    for (int j = 0; j < arena->sizeX; j++) {
        printf("\u2501\u2501\u2501.");
    }
    printf("\n");
    for (int i = 0; i < arena->sizeY; i++) {
        for (int j = 0; j < arena->sizeX; j++) {
            if (arena->cells[i][j].wallLeft) {
                printf("\u2503");
            } else {
                printf(" ");
            }
            printf("   ");
        }
        if (arena->cells[i][arena->sizeX - 1].wallRight) {
            printf("\u2503");
        } else {
            printf(" ");
        }
        printf("\n");
        printf(".");
        for (int j = 0; j < arena->sizeX; j++) {
            if (arena->cells[i][j].wallBottom) {
                printf("\u2501\u2501\u2501.");
            } else {
                printf("   .");
            }
        }
        printf("\n");
    }
}










